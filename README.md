# C/C++ SDL2 w/ CMake Project Template
This is an incredibly basic project template for C/C++ with SDL2, SDL2_image, SDL2_ttf, and SDL2_mixer.
It is setup to use CMake to build on Linux and on Windows (with MinGW).

## Setup

### Linux
1. `apt-get install cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev`
2. `mkdir -p config && mkdir -p assets`
3. `cd lib && ./clone_libs.sh`

#### Cross-compile for Windows
Cross-compiling for Windows on Linux requires the same basic setup of MinGW as native Windows builds.
Install MinGW on Linux and either cross-compile all of the SDL2 libs or download and extract the prebuilt MinGW versions.

### Windows
1. Install Git Bash: https://git-scm.com/downloads
2. Install MingGW-w64: http://mingw-w64.org/doku.php
3. Install CMake: https://cmake.org/download/
4. Download and install the SDL2 dev libraries for MinGW and extract them into the MinGW installation folder, e.g. C:/../MinGW/
5. Add the MinGW and the MinGW/bin folders to your PATH.

## Usage

### Linux
Native: `./scripts/build_linux_native.sh`
Cross-compile for Windows: `./scripts/build_windows_cross.sh`

### Windows
Use Git Bash: `./scripts/build_windows_native.sh`

Note: Windows binaries will require a bunch of DLLs alongside in order to run on other machines (i.e. a machine without the dev libraries on the PATH)

## Development
1. Change the project name in the top-level CMakeLists.txt file

## Improvements
1. Visual Studio builds
2. Mac OS support
3. Cross-compiling
4. Automate zipping up binary and DLLs for windows builds