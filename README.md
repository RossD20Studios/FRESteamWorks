# Steamworks API for AIR Games and Applications #

FRESteamWorks allows you to implement SteamWorks API features including achievements, leaderboards, steam input, cloud
storage, workshop support and much more in your games built with Adobe AIR on Windows,
Mac and Linux.

# RossD20Studios :: Steam Input API and Native Linux Support #

A brief history of this project's development:
1. [Ventero](https://github.com/Ventero) initially started this project as a fork of [FRESteamWorks by Oldes/Amanita Design](https://github.com/Oldes/FRESteamWorks/) 
2. [waveofthought](https://github.com/waveofthought-code) forked Ventero's branch [FRESteamWorks by Ventero](https://github.com/Ventero/FRESteamWorks) to create his branch that added 64Bit + expanded API
3. [RossD20Studios](https://github.com/RossD20Studios) forked waveofthought's branch [FRESteamWorks waveofthought](https://github.com/waveofthought-code/FRESteamWorks) to create this branch that adds support for Steam Input API, Native Linux, and newer AIR v50.2.3 thanks to support from Andrew Frost, Jon Dix and Brad Jackson.
4. [Fancy2209](https://github.com/Fancy2209) forked RossD20Studios's branch with his own [FRESteamWorks Fancy2209](https://github.com/Fancy2209/FRESteamWorks) to merge waveOfThought's recent changes and update the ANE for SteamWorks v1.61 and has merged his changes back here to support the ANE's development.

For an example of this ANE in action with a Steam Deck Verified and Native Linux support, you can [download the free demo of my turn-based tactical card game, Abalon, on Steam](https://store.steampowered.com/app/1681840/Abalon/?utm_source=FRESteamWorks).

# Download #

A fully code signed and built ANE for Windows/macOS/Linux can be [downloaded here](https://d20studios.com/FRESteamWorks/). 

This version was built and uploaded on February 21, 2025. 

If you're upgrading from an older version, note that the getAuthSessionTicket now requires an additional parameter of the user's Steam id: Steamworks.getAuthSessionTicket(_authTicket, Steamworks.getUserID()).

# API Documentation #

For a full list of all supported functions,
see [FRESteamWorks.as](https://github.com/RossD20Studios/FRESteamWorks/blob/master/lib/src/com/amanitadesign/steam/FRESteamWorks.as).
In general, the FRESteamWorks API functions try to be a close representation of
the native Steamworks SDK functions.

The Steam API docs can be [found here](https://partner.steamgames.com/doc/api).
Steam Input API Documentation can be [read here](https://partner.steamgames.com/doc/features/steam_controller/getting_started_for_devs)

**Note:** Steam SDK documentation is not always up-to-date with the latest SDK version, so cross-reference the Steam SDK source code in C++.

# Usage #

### Using the ANE Requires: ### 
1. AIR Version 50.2.3 or greater (Last built with AIR 51.1.3.7)
2. SteamWorks SDK v1.61
3. Windows 32-bit/x64, MacOS x64/ARM (M1/M2) or Linux x64

Include the ANE in your project like
any normal SWC, add the extension to your application descriptor and include
`extendedDesktop` in the list of supported profiles. For an example, see
[the application descriptor of the FRESteamWorks test application](https://github.com/Ventero/FRESteamWorks/blob/master/test/bin-debug/FRESteamWorksTest-app.xml#L14-17).

In addition, you will also need to include the corresponding SteamWorks redistributable bin file in your application's root directory. These are found in SteamWorks SDK folder "redistributable_bin"
1. Windows 64-bit requires steam_api64.dll (32-bit requires steam.dll)
2. Mac OS requires libsteam_api.dylib
3. Linux requires libsteam_api.so

For testing the application, I recommend building the AIR application, opening the Steam client, and copying the build you wish to test over the installed version of your Steam client version of your development machine on each respective platform you wish to support.

# Building FRESteamWorks #

Building the ANE from the source files is only necessary if you need to modify source code and/or the ANE package is no longer available for [downloaded here](https://d20studios.com/FRESteamWorks/).

### Building the ANE Requires: ###
1. AIR Version 50.2.3 or greater (Last built with AIR 51.1.3.7)
2. SteamWorks SDK v1.61 (Newer versions might be compatibly, but this is the last working version the ANE was built with)
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
6. In the two drop down menus at the top (just below the Build / Debug menu headers) set the first drop down menu to “Release” and the second drop down menu to “x64”. Then, select Build -> Build Solution (Ctrl + Shift + B). **Note:** The Build will fail here unless java environment variables are configured, but that’s OK. It will still output the FRESteamWorks-64.dll file to FRESteamworks/src/Release/FRESteamWorks-64.dll, and that’s all you need for 64-bit Windows.
7. Change the second drop down selection from x64 to Win32 and select Build -> Build Solution again to compile the 32-bit Windows version. This will output the file FRESteamworks/src/Release/FRESteamWorks.dll.
8. Copy FRESteamworks/src/Release/FRESteamWorks-64.dll and FRESteamworks/src/Release/FRESteamWorks.dll to the FRESteamWorks/lib/bin folder on your Mac OS.
9. **Note:** If you're getting an error about moving/copying the built DLL's, then be sure to manually move them or delete them from the Release folder before you build again. Otherwise, the next time you go to build, it will not re-create a new version of the DLL.

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
5. If you are prompted to enter a password to use the certificate from your keychain, do so. **Important Note:** After doing so, you will need to run the build a second time, even if it succeeded, to ensure that the build is properly code signed. I made this mistake many times thinking the build had worked, only to discover later that the ANE wouldn’t run on Mac because it hand’t actually signed it properly. To avoid requiring password in the future, you can check the “Always allow” option, but still run the build process a second time after doing so. And, always test that your ANE works by running it on your local machine before uploading to Steam.
6. Running the build process will create the completed ANE at Users/userName/FRESteamWorks/lib/bin/FRESteamWorks.ane as well as an unpacked folder called FRESteamWorks.Unpacked.ane where you can see structure of what the ANE looks like. Inside this, you should see a folder for Linux-x86-64 containing your FRESteamWorks.so, a MacOS-x86-64 containing FRESteamWorks.framework, a Windows x86 folder containing FRESteamWorks.dll and a Windows-x86-64 containing FRESteamWorks-64.dll. Each folder also contains a library.swf. **Note:** Ensure that the file size of these files is greater than zero, otherwise, you may have forgotten to copy the files created in the prior steps to your bin folder. The MacOS build process will create placeholders if these files are missing with a 0KB size.

# Contributing to the ANE's Development #
For more details and contributing to the ANE please visit the [air.sdk Discord](https://discord.gg/HVSP4bqJst) and ping @rossd20studios with a pull request.
Also check out the original contribution guide from Ventero: 
[contributing guide](https://github.com/Ventero/FRESteamWorks/tree/master/CONTRIBUTING.md).

---

# License #

See [LICENSE](https://github.com/Ventero/FRESteamWorks/tree/master/LICENSE).
