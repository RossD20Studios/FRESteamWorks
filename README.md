# Steamworks API for AIR applications #

A simple Steamworks API wrapper to be used as native extension for Adobe AIR
applications. This allows you to implement Steam achievements, leaderboards, cloud
storage, workshop support and much more in your AIR application - on Windows,
OS X and Linux.

# RossD20Studios :: Steam Input API #
I forked waveofthought's fork of this project to add Steam Input API (gamepad controller) support to this ANE.

Steam Input API Documentation can be [read here](https://partner.steamgames.com/doc/features/steam_controller/getting_started_for_devs)

A working ANE with Steam Input support for Windows/macOS can be [downloaded here](https://d20studios.com/FRESteamWorks/)

You can try out my game, Summoners Fate, on Steam (free demo) to [see the ANE in action here](https://store.steampowered.com/app/1681840/Summoners_Fate/)

# waveofthought ::  64Bit + expanded API #
I forked this project to both extend available Steamworks API *and* output 64-bit capability for Windows.  All of the Ventero instructions/examples/tests should still work (see below, under "Ventero"), but as of this writing I have not yet updated the Ventero tests to reflect the new API.

A working ANE for Windows/macOS can be [downloaded here](https://waveofthought.com/FRESteamWorks).

Rather than using the Linux SWC and wrapper as a workaround, with support now available for AIR Native Extensions on Linux, the ANE now supports Linux-x86-64. There is a makefile for building the library in the 'src' folder and it can be included in the ANE from a macOS build.

### Additional API ###
The steam API docs can be [found here](https://partner.steamgames.com/doc/api).
Below is just the new Steam stuff. For a full list of the available API, you can view [lib/API.txt](https://github.com/waveofthought-code/FRESteamWorks/blob/master/lib/API.txt).
```
setRichPresence(key:String, value:String):void
clearRichPresence():void

isSteamInBigPictureMode():Boolean

isAchievementEarned(achName:String):Boolean // same as isAchievement(), but clearer to its purpose
getAchievementAchievedPercent(achName:String):Number
getAchievementDisplayAttribute(achName:String, attribute:String):String
getAchievementIcon(achName:String):BitmapData
getAchievementName(achIndex:int):String
getNumAchievements():int

getLargeFriendAvatar(friendID:String):BitmapData

getIPCountry():String

setOverlayNotificationInset(hInset:int, vInset:int):void
overlayNeedsPresent():Boolean
```

### Building ###
Don't worry about this section if you only plan to copy the ANE as-is to your game.  [You can download it here](https://waveofthought.com/FRESteamWorks)

#### Windows ####


Project has been updated to VS2019

A new SDKPaths.props file has been added to help specify your own Air + Steam SDK install directories.  Edit this file directly, or use the VS Properties Manager

*Outputting FRESteamWorks DLLs:*
1) Build > Batch Build... 
2) Check both Win32 + x64 Releases
3) Click Build (or Rebuild)

The original post-build event will continue to copy DLLs to the ../lib/bin folder and attempt to run compileANE.bat as expected, but can/will trigger twice since its building two different DLLs.
As such, compileANE.bat has been updated to check for the existence of both 32+64 bit DLLs before continuing, to prevent potential errors. It is what it is.


#### macOS ####
Ventero instructions should still apply, but the deployment target has been updated to macOS 10.10 due to the latest libsteam_api.dylib from Valve also being built for 10.10.

# Ventero #

This project initially started as a fork of [FRESteamWorks by Oldes/Amanita Design](https://github.com/Oldes/FRESteamWorks/).

If you want to contribute to this project, please take a look at the
[contributing guide](https://github.com/Ventero/FRESteamWorks/tree/master/CONTRIBUTING.md).

For a list of changes, see [the changelog](https://github.com/Ventero/FRESteamWorks/tree/master/CHANGELOG.md).

# Download #

Pre-built cross-platform ANEs (for both Windows and OS X), as well as Linux
SWCs can be found on http://dump.ventero.de/FRESteamWorks/. The Linux wrapper
binary has to be built manually, see [the Linux section](#linux) for more details.

# API Documentation #

For a full list of all supported functions with some accompanying documentation,
see [lib/API.txt](https://github.com/Ventero/FRESteamWorks/blob/master/lib/API.txt).
In general, the FRESteamWorks API functions try to be a close representation of
the native Steamworks SDK functions. Thus, for detailed documentation, see the
Steamworks SDK docs.

The objects returned by certain API functions are plain data structures.
For a list of available properties, see [the corresponding source files](https://github.com/Ventero/FRESteamWorks/tree/master/lib/src/com/amanitadesign/steam).

# Usage #

For Windows/OS X builds, you'll only have to include the ANE in your project like
any normal SWC, add the extension to your application descriptor and include
`extendedDesktop` in the list of supported profiles. For an example, see
[the application descriptor of the FRESteamWorks test application](https://github.com/Ventero/FRESteamWorks/blob/master/test/bin-debug/FRESteamWorksTest-app.xml#L14-17).

Testing your application is a bit more complicated and depends on how your project
is built. For detailed information, see below. For general information regarding
the testing of Steam applications, please refer to the Steamworks SDK documentation.

Since the AIR runtime on Linux doesn't support native extensions, an external
binary is used to communicate with the Steamworks API. For more information
on how to build and include this tool, see [the Linux section](#linux).

# Building FRESteamWorks #

Building the ANE from the source files is only necessary if you need to modify source code and/or the ANE package is no longer available for [downloaded here](https://d20studios.com/FRESteamWorks/)

### Building the ANE Requires: ###
1. AIR Version 50.2.3
2. SteamWorks SDK v1.54
3. Mac OS Catalina+ (To ensure support for latest Xcode)
4. Apple Developer Account (To create the Developer ID Application certificate necessary to sign the ANE to work on Mac)
5. Xcode v14+  (To build the Mac version and ensure support for Apple Silicon M1/M2)
6. Windows 10+
7. Microsoft Visual Studio 2022
8. Linux OS / Virtual Machine - x86/64 Version (AIR will not currently compile/run on ARM versions)

The original Ventero project would have you modify build scripts (indicating the relative and/or direct file paths to the necessary dependent source code, such as the AIRSDK and the SteamSDK). However, in practice, I found that each of the respective projects (Visual Studio, Xcode) still required several direct file path dependencies. To make this process easier and avoid the trouble of finding and replacing all of these dependent file paths, I’ve coded the project to use fixed filepaths.

To build the ANE, you will need to compile the respective native source files for each platform you wish to target (Windows, Mac, Linux) using a machine that includes this native operating system or virtual operating system for that platform. Then, you will need to package the native compiled files into a ZIP file with extension ANE. We will complete this last step on the MacOS.

### Step 1: Setup FRESteamWorks Project on your MacOS ###
1. Ensure FRESteamWorks project folder is located in your username home folder (ex: Users/userName/FRESteamWorks) so that relative file paths in the Xcode project will find dependent source files
2. Create an SDKS folder in your username home folder (ex: Users/userName/SDKS)
3. Inside the SDKS folder, copy your AIRSDK and SteamSDK and ensure the folder names are labeled as this exactly.
4. Inside the root of SDKS\AIRSDK folder, you should see the actual AIRSDK folders (ex: ant, asdoc, aftools, etc.) and not a nested version of the current AIR version.
5. Inside the root of your SDKS\SteamSDK, you should see the actual SteamSDK folders (ex: glmgr, public, redistributable_bin, etc.)
6. Proceed to building Windows DLLs and Linux SO, we’ll need the output files before we build the MacOS files and assemble the ANE

### Step 2: Building the Windows DLLs ###
1. Create an SDKS folder at C:\SDKS
2. Inside the C:\SDKS folder, copy your AIRSDK and SteamSDK and ensure the folder names are labeled as this exactly.
3. Inside the root of your C:\SDKS\AIRSDK folder, you should see the actual AIRSDK folders (ex: ant, asdoc, aftools, etc.) and not a nested version of the current AIR version.
4. Inside the root of your C:\SDKS\SteamSDK, you should see the actual SteamSDK folders (ex: glmgr, public, redistributable_bin, etc.)
5. Navigate to your FRESteamWorks\src folder and open FRESteamWorks.vcxproj with Microsoft Visual Studio 2022
6. In the two drop down menus at the top (just below the Build / Debug menu headers) set the first drop down menu to “Release” and the second drop down menu to “x64”. Then, select Build -> Build Solution (Ctrl + Shift + B). Note: The Build will fail here unless java environment variables are configured, but that’s OK. It will still output the FRESteamWorks-64.dll file to FRESteamworks/src/Release/FRESteamWorks-64.dll, and that’s all you need for 64-bit Windows.
7. Change the second drop down selection from x64 to Win32 and select Build -> Build Solution again to compile the 32-bit Windows version. This will output the file FRESteamworks/src/Release/FRESteamWorks.dll.
8. Copy FRESteamworks/src/Release/FRESteamWorks-64.dll and FRESteamworks/src/Release/FRESteamWorks.dll to the FRESteamWorks/lib/bin folder on your Mac OS.

### Step 3: Building the Linux SO ###
1. Ensure the root of your FRESteamWorks project on Linux is located at Home\FRESteamWorks
2. Create an SDKS folder at Home\SDKS
3. Inside the SDKS folder, copy your AIRSDK and SteamSDK and ensure the folder names are labeled as this exactly.
4. Inside the root of your SDKS\AIRSDK folder, you should see the actual AIRSDK folders (ex: ant, asdoc, aftools, etc.) and not a nested version of the current AIR version.
5. Inside the root of your SDKS\SteamSDK, you should see the actual SteamSDK folders (ex: glmgr, public, redistributable_bin, etc.)
6. Navigate to FRESteamWorks\src where the MakeFile is located and right click to open this location in the terminal
7. Type “make” (no quotes). If this fails, you may need to install g++. To do so, type “Sudo apt install g++” (no quotes)
8. The make command will create a new file in FRESteamWorks\src\FRESteamWorks\ called “FRESteamWorks.so”. Copy this file to the FRESteamWorks/lib/bin folder on your Mac OS.

### Step 4: Building the Mac OS Framework file and Packaging the ANE ###
1. Create a Developer ID Application certificate in your Apple Developer Account under Certificates. This type of certificate is used to code sign your app for distribution outside the Mac App Store. Once you’ve created the certificate, download it, then double click it to add it to your KeyChain.
2. Navigate to FRESteamWorks/src and open the FRESteamWorks.xcodeproj in Xcode
3. In the left navigational menu of Xcode, ensure the “folder” icon is selected and then select the FRESteamWorks project which will have a generic App icon to its left. This will take you to the Build Settings tab. Here, in the “Signing” section, you will need to select Developer ID Application. Select Code Signing Style -> Manual. And also ensure your development team is selected in the third drop down. No provisioning file is required.
4. From the upper task bar menu, select Project -> Build
5. If you are prompted to enter a password to use the certificate from your keychain, do so. Important Note: After doing so, you will need to run the build a second time, even if it succeeded, to ensure that the build is properly code signed. I made this mistake many times thinking the build had worked, only to discover later that the ANE wouldn’t run on Mac because it hand’t actually signed it properly. To avoid requiring password in the future, you can check the “Always allow” option, but still run the build process a second time after doing so. And, always test that your ANE works by running it on your local machine before uploading to Steam.
6. Running the build process will create the completed ANE at Users/userName/FRESteamWorks/lib/bin/FRESteamWorks.ane as well as an unpacked folder called FRESteamWorks.Unpacked.ane where you can see structure of what the ANE looks like. Inside this, you should see a folder for Linux-x86-64 containing your FRESteamWorks.so, a MacOS-x86-64 containing FRESteamWorks.framework, a Windows x86 folder containing FRESteamWorks.dll and a Windows-x86-64 containing FRESteamWorks-64.dll. Each folder also contains a library.swf. Note: Ensure that the file size of these files is greater than zero, otherwise, you may have forgotten to copy the files created in the prior steps to your bin folder. The MacOS build process will create placeholders if these files are missing with a 0KB size.

For more details, please see the
[contributing guide](https://github.com/Ventero/FRESteamWorks/tree/master/CONTRIBUTING.md).

---

# License #

See [LICENSE](https://github.com/Ventero/FRESteamWorks/tree/master/LICENSE).
