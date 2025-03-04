#!/usr/bin/env ruby

def create_lib line, func
	<<-EOD
#{line} {
	return _ExtensionContext.call("#{func[:air_name]}"#{["", *func[:args].keys].join(", ")}) as #{func[:ret]};
}
	EOD
end

@lib_lin_defaults = Hash.new { |h,k| h[k] = ["readResponse() as #{k}", "null"] }
@lib_lin_defaults.merge!({
	"Array" => ["readResponse() as Array", "[]"],
	"Boolean" => ["readBoolResponse()", "false"],
	"Number" => ["readFloatResponse()", "0.0"],
	"int" => ["readIntResponse()", "0"],
	"uint" => ["readIntResponse()", "0"],
	"String" => ["readStringResponse()", "\"\""]
})
def create_lib_linux line, func
	type, default = @lib_lin_defaults[func[:ret]]
	default = func[:default] if func[:default]

	<<-EOD
#{line} {
	if(!callWrapper(#{func[:air_name]}, [#{func[:args].keys.join(", ")}])) return #{default};
	return #{type};
}
	EOD
end

files = [
	{
		:file => "src/com/amanitadesign/steam/ISteamWorks.as",
		:ignore => ["init", "getGlyphSVGForActionOrigin", "getGlyphPNGForActionOrigin"],
		:format => -> line, func { line.sub "public ", "" }
	},
	{
		:file => "src/com/amanitadesign/steam/FRESteamWorks.as",
		:ignore => ["init", "getGlyphSVGForActionOrigin", "getGlyphPNGForActionOrigin"],
		:format => method(:create_lib)
	},
	{
		:file => "../src/functions.h",
		:ignore => [],
		:format => -> line, func { "X(#{func[:air_name]}) /* = #{func[:num]} */" }
	}
]

def parse_prototype line
	match = line.match(/function\s+([^\s(]+)\s*\(([^)]*)\)\s*:\s*(\w+)/)
	raise "Invalid line: #{line}" unless match

	func, args, ret = match.captures

	arg_spec = args.scan(/(\w+):([^,]+)(?:,\s*)?/)
	arg_map = Hash[arg_spec]

	# We assume that insertion order is maintained when converting a hash to an
	# array. This is guaranteed by Ruby 1.9, but better be explicit about it.
	raise "Hash insertion order not maintained" unless arg_spec == arg_map.to_a

	return {
		:name => func,
		:air_name => "AIRSteam_#{func[0].chr.upcase + func[1,func.size]}",
		:args => arg_map,
		:ret => ret
	}
end

def find_markers content, from, to
	start_idx = content.find_index{|line| line.include? from }
	end_idx = content.find_index{|line| line.include? to  }
	raise "Invalid indices: #{start_idx} - #{end_idx}" unless end_idx > start_idx

	indentation = content[start_idx].scan(/^\s*/)[0]

	[start_idx, end_idx, indentation]
end

def generate_api contents, files
	files.each do |options|
		file_content = File.read(options[:file]).split("\n")

		start_marker = options[:start] || "START GENERATED CODE"
		end_marker = options[:end] || "END GENERATED CODE"
		from, to, indentation = find_markers file_content, start_marker, end_marker

		func_num = -1
		default_ret = ""
		skip = false
		replacement = contents.map do |line|
			# try to extract the default return value
			default_match = line.match(/^\/\/ @default (.+)/)
			default_ret = default_match[1] if default_match

			# check if this function should be skipped during code generation
			skip = true if line["// @nogen"]

			# ignore empty lines and documentation comments
			next nil if line.empty? or line[/^\/\//]
			# but copy block comments (used for grouping)
			next "#{indentation}#{line}" if line[/^\/\*/]

			func = parse_prototype line

			# If this function is marked as "nogen", skip it
			(skip = false; next nil) if skip

			func_num += 1
			func[:num] = func_num
			func[:default] = default_ret unless default_ret.empty?

			# Reset for the next function
			default_ret = ""

			next ["#{indentation}// manual implementation", "#{indentation}// #{line}",
				""] if options[:ignore].include? func[:name]

			options[:format].call(line, func).gsub(/^/, indentation)
		end.reject{|a|a.nil?}

		file_content[from + 1 .. to - 1] = replacement

		File.open(options[:file], "w") {|f|
			f.puts file_content.join("\n")
		}
	end
end

def generate_response_types target, types
	content = File.read(target).split("\n")

	from, to, indentation = find_markers content, "START GENERATED CODE", "END GENERATED CODE"
	replacement = types.grep(/RESPONSE_/).map.with_index do |line, idx|
		# remove indentation and trailing comma
		type = line.lstrip.chomp(",")
		"#{indentation}public static const #{type.lstrip}:int = #{idx};"
	end

	content[from + 1 .. to - 1] = replacement

	File.open(target, "w") {|f|
		f.puts content.join("\n")
	}
end

contents = File.read("API.txt").split("\n")
generate_api contents, files

response_types = File.read("../src/CSteam/ResponseTypes.h").split("\n")
generate_response_types "src/com/amanitadesign/steam/SteamConstants.as", response_types
