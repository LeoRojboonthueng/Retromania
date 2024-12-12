# Retromania

A simple SFML-based game with a movable player character and background

## Installation:
   Currently the game is in a pre-release state, bugs may occur.
   You can grab the latest version from: 
   https://github.com/LeoRojboonthueng/Retromania/releases/tag/0.0.1
   Or alternatively, you can build from source (see bellow)

## Building Instructions

1. Clone the repository:
   git clone https://github.com/LeoRojboonthueng/Retromania.git
   cd Retromania
	
2. Run CMake to generate the build files:
   ```bash
   mkdir build
   cd build
   cmake -DCMAKE_BUILD_TYPE=Release ..
   cmake --build . --config Release
   ```

3. Creat an installer:
   ```bash
   cpack
   ```

4. Run the installer!
   Found in build/Retromania-0.0.1-win64.exe (or win32)