# How to build for WinForms - C#?
- Open "HostMonitor\BuildWinforms\BuildWinforms.sln" by Visual studio 2017
- Build `sample`, `HostMonitor`, `BuildWinforms` in turn, then run BuildWinforms.

# How to build for Win MFC?
- Open "HostMonitor\BuildMFC\HostMonitor.sln" by Visual studio 2017
- Click `F5` to build/run `HostMonitor`

# How to build for Win32?
- Open "HostMonitor\BuildWin32\HostMonitor.sln" by Visual studio 2017
- Click `F5` to build/run `HostMonitor`, you will see UI in internet browser.

# How to build for Linux?
## Compile & Run locally:
1. Compile:
    - `cd HostMonitor`
    - `cmake . && make`
    - `cd BuildLinux`
2. Run locally(e.g, Ubuntu):
    - Run with framebuffer: `sudo ./HostMonitor /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.
    - Run inside X Window: `sudo ./xWindow 1024 768 | ./HostMonitor shared-fb`

## Cross compiler & Run on target:
1. install compiler:
    - For ARM32: `sudo apt-get install g++-arm-linux-gnueabi gcc-arm-linux-gnueabi`
    - For ARM64: `sudo apt-get install g++-aarch64-linux-gnu gcc-aarch64-linux-gnu`
2. Cross compile:
    - `cd HostMonitor`
    - For ARM32: `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" . && make`
    - For ARM64: `cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++" . && make`
3. Run on target Linux device:
    - Copy BuildLinux/HostMonitor to target Linux device
    - `sudo ./HostMonitor /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer

# How to build with GoLang?
1. Build UIcode:
- `cd HostMonitor/UIcode`
- If x64/raspberry pi:
    - `cmake .`
    - `make`
    - `cp libUIcode.a ../BuildGo/libs/amd64/`
- If ARM32:
    - `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" .`
    - `make`
    - `cp libUIcode.a ../BuildGo/libs/arm/`
2. Build Golang:
- `cd HostMonitor/BuildGo`
- `go build -o HostMonitor`
3. Run with framebuffer:
- `sudo ./HostMonitor /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.
4. Run inside QT APP(display-xxx is a QT APP for display, skip this if you haven't installed QT):
- `sudo ./xWindow 1024 768 | ./HostMonitor shared-fb`

# How to build for iOS?
### libUIcode.a should be in \BuildIos\BuildIos\libs, rebuild them if meet link error.
- `cd HostMonitor\BuildIos`
- Open `BuildIos.xcodeproj` with Xcode
- Build & Run

# How to build for Mac?
- `cd HostMonitor`
- `cmake -D TARGET_OS="MAC" .`
- `make`

## Run in command mode
- `cd BuildMacCmd`
- `./HostMonitor 1 8`, you will see UI in internet browser(Safari).

## Run in UI mode
### libUIcode.a should be in BuildMacCocoa\GuiLiteDemo\libs, rebuild them if meet link error.
- Open `BuildMacCocoa\GuiLiteDemo.xcodeproj` with Xcode
- Build & Run

# How to build/run for Android?
- Open "BuildAndroid" with Android studio
- Build & Run

# How to build for Windows UWP?
depdency: Windows 10, visul stdio 2015/2017

- Open "UIcode\sample.sln" by Visual studio 2017
- Click `build` 
- `copy UIcode\debug\sample.lib BuildUWP\sample_uwp_cpp\libs\x86(x64)\`
- Open "BuildUWP\HostMonitor.sln" by Visual studio 2017
- Click `build`
- Click `debug/run`

# How to run on VR/MR?
- If VR: run `Mixed Reality Portal`on PC side.
- Take VR/MR device on head, or run simulator.
- press `start`, find the UWP you build and run.

Note: Windows RS3(Build 16299) will be necessary.