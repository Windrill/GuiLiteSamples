# How to build for Win MFC?
1. Open "HelloAnimation\BuildMFC\HelloAnimation.sln" by Visual studio 2017
2. Click `F5` to build/run `HelloAnimation`

# How to build for Linux?
## Compile & Run locally:
1. Compile:
    - `cd HelloAnimation`
    - `cmake . && make`
    - `cd BuildLinux`
2. Run locally(e.g, Ubuntu):
    - Run with framebuffer: `sudo ./HelloAnimation /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.
    - Run inside X Window: `sudo ./xWindow 238 169 | ./HelloAnimation shared-fb`

## Cross compiler & Run on target:
1. install compiler:
    - For ARM32: `sudo apt-get install g++-arm-linux-gnueabi gcc-arm-linux-gnueabi`
    - For ARM64: `sudo apt-get install g++-aarch64-linux-gnu gcc-aarch64-linux-gnu`
2. Cross compile:
    - `cd HelloAnimation`
    - For ARM32: `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" . && make`
    - For ARM64: `cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++" . && make`
3. Run on target Linux device:
    - Copy BuildLinux/HelloAnimation to target Linux device
    - `sudo ./HelloAnimation /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer
