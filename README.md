# Retromania

A simple SFML-based game with a movable player character and background

## Setup Instructions

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