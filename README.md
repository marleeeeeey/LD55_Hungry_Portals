# LD55 Hungry Portals

**LD55 Hungry Portals** - is a platformer game developed for the [Ludum Dare 55 game jam](https://ldjam.com/events/ludum-dare/55/ld55-hungry-portals).

Hungry Portals from the dark realm are out for blood, and they’ve turned their attention to your home, trapping your demonic family within their shadowy depths. You start as a lone survivor with a chance to save your kin and reclaim your home. [More details...](docs/GAME_DESCRIPTION.md)

### Team Members

- [marleeeeeey](https://github.com/marleeeeeey) - programming, game design, and sound.
- [jsCommander](https://github.com/jsCommander) - game design and art.
- [SdCorpse](https://www.artstation.com/secondcorpse) - game design and testing.

### Screenshot

![game screenshot](docs/LD55_Hungry_Portals_screenshot.png)

### Platform Support

- This game has been developed, built, and tested solely on **Windows**. Build also works on **Linux(Ubuntu)** but not tested yet.

### Change Log

```
2024-04-13 0500 Start the jam (I overslept 7 hours since the start of the jam).
2024-04-13 1200 Start thinking about the game idea.
2024-04-13 1353 Complete repository setup.
2024-04-13 1513 Implement dummy portal catching the player.
2024-04-13 1826 Intergrate evil and portal animations.
2024-04-14 0159 Implement StickyTrap.
2024-04-14 0309 Support DestructionPolicy and ZOrdering: Background, Interiors, Terrain.
2024-04-14 0414 Portal sticky to trap.
2024-04-14 0930 I was sleeping since 0414 to 0930.
2024-04-14 1108 Create fast hybrid explosion fragments.
2024-04-14 1308 Implement portal absorbing fragments.
2024-04-14 1407 Randomize portal speed in time.
2024-04-14 1449 Found a bug with release build during the beta testing (SdCorpse).
2024-04-14 1500 Sleep. Play with my kids. Relaxing.
2024-04-14 2000 Back to development.
2024-04-14 2238 Simplify physic to improve CPU time.
2024-04-14 2316 Fix bug in release with undestructible objects.
2024-04-15 0103 Update collision system. Bullet doesn't collide with Particles.
2024-04-15 0212 Scatter portals if they bump each other.
2024-04-15 0230 I was sleeping since 0230 to 0830.
2024-04-15 1142 Inspired with new ideas from SdCorpse.
2024-04-15 1500 Start working on new features.
2024-04-15 1616 Refactor the code. Update documentation with important notes. Start working on new features.
2024-04-15 1751 Portal eats player emmediately if it's close enough.
2024-04-15 1815 Spend time since 1815 to 2300 with my family.
2024-04-15 2300 Back to development.
2024-04-15 2338 Fix bug with different speed for players.
2024-04-15 2353 Fix bug when portal searching players incorrectly.
2024-04-16 0105 Portal burst when eats enought. Family member summoing from the portal. All players moving sinchronized.
2024-04-16 0217 Integrate fire animation for bullet and grenade. Remove other weapons. Jump - Space.
2024-04-16 0245 Draw animation for building block.
2024-04-16 0324 One eating counter for all portals. Decrease portal sleep time.
2024-04-16 0411 Create game intruction on start.

*** Items implemented after the jam ***

2024-04-16 1250 Fix start menu bug.
2024-04-16 1317 Remove background from the game.
2024-04-23 1300 Prepare build for web (WASM Emscripten).
2024-04-23 1400 Remove music fade-in/fade-out.
2024-04-26 0215 Add maps from easy to dificult level.
2024-04-27 0228 Improve sound system. Add several sounds (fire, explosion, eating).
2024-04-29 1300 Add layer with indestructible tiles.
2024-04-29 1400 Fix bug with control buttons sticking when reloading the level.
2024-04-29 1500 Improve player jump. Now it depends on the duration of pressing the key.
2024-04-29 1600 Add debug functions for drawing sensors and bounding boxes.
2024-04-29 1700 Enable VSync.
2024-04-30 1800 Disable bullet collisions with the player.
2024-05-01 1900 Major improvement of debugging tools: added the ability to track objects.
2024-05-01 2000 Fix bugs in the explosion mechanics.
2024-05-01 2100 Expand the building block.
```

### Development Guidelines

#### Efficient Component Access (Entt)

- **Use of Views**: When you need to iterate over entities that share a common set of components, prefer using `view` over `all_of` or `any_of` checks within loop iterations. Views are optimized for fast access and iteration, as they precompute and cache the entities that match the specified component criteria. This approach significantly reduces overhead and improves performance, especially with large entity sets.

```cpp
  // Recommended
  auto view = registry.view<ComponentA, ComponentB>();
  for (auto entity : view) {
      // Process entities that have both ComponentA and ComponentB
  }
  ```

- **Avoid Frequent Component Checks**: Using `registry.all_of` or `registry.any_of` in tight loops for large numbers of entities can be inefficient. These functions check each entity's component makeup at runtime, which can lead to performance degradation if used improperly. (TODO2: check the game code for this).

```cpp
  // Not recommended for large sets or frequent updates
  for (auto entity : registry) {
      if (registry.all_of<ComponentA, ComponentB>(entity)) {
          // Process entity
      }
  }
  ```

- **Entity Processing Recommendations**: If specific conditional checks on entity components are necessary outside of views, consider structuring your logic to minimize the frequency and scope of these checks, or use architectural patterns that naturally segregate entities into manageable sets. (TODO2: thinking about splitting entities into more specific components).

#### Object Factory

- **ObjectsFactory** is the only object that should add new components to the `entt::registry`.
  - Any method that creates a new object must start with `Spawn`.

#### Component Naming Conventions

- Class names for components must end with `Component`.
  - Header files containing components should end with `_components.h`.

#### Coordinate Systems and Object Sizing

- Texture sizes are measured in pixels, while the sizes of objects in the physical world are measured in meters.
- There are three coordinate systems: screen, pixel world, and physical world. Variable names should end with `Screen`, `World` (TODO3: rename to `Pixels`), or `Physics`.

#### C++ Style Guide

- Prefer using `enum class` over boolean variables.
- Favor composition over inheritance.
- Use descriptive and clear naming conventions that reflect the purpose and usage of the variable or function.

#### Configuration Style Guide

- In `config.json`, section names should correspond to the class names that use them.
- Variable naming in `config.json` should be a direct copy of the variable names in the code.
- Debug options should start with `debug` and may be located in every section.

#### Animation Editor and Engine Integration

- The player animation stores the BBox (bounding box) of the object used for collision detection.
- Bullet animations should not consider the dimensions of the BBox for speed calculations.

### Assets Editing Guidelines

#### Aseprite Guidelines

- **Tagging**: Ensure that all frames are tagged, as these tags are referenced in the C++ code for animation handling.
- **Hitbox Frame**: Include a specifically named frame `Hitbox` within your Aseprite files, which will be used to define interaction boundaries in the game.

#### Tiled Map Editor Guidelines

- **Layer Structure**: Your maps should be organized with the following layers from bottom to top:
  - `background`: For non-interactive scenery that appears behind all game entities.
  - `interiors`: For elements like indoor furnishings that players can potentially interact with but are not part of the terrain.
  - `terrain`: For the main walkable and interactive layer of the game environment.
  - `objects`: For movable or interactive objects that players can interact with during the game.

## Windows build

### Clone the Repository

```
git clone --recursive https://github.com/marleeeeeey/LD55_Hungry_Portals.git
```

### Prerequisites for Building the Project (Windows)

- CMake.
- Ninja.
- Clang compiler (other compilers may work, but are not officially supported).
- Git (to load submodules).
- Visual Studio Code (recommended for development).
  - Clangd extension (recommended for code analysis).
- Python and 7zip (for packaging game to achive).

### Build, run and debug via VSCode tasks (Windows)

- Setup user friendly options via editing file [scripts/vscode_tasks_generator.py](scripts/vscode_tasks_generator.py).
- Run the script [scripts/vscode_tasks_generator.py](scripts/vscode_tasks_generator.py) to generate VSCode tasks with your options.
- Open the project folder in VSCode.
- Run task: `003. Install vcpkg as subfolder`.
- Run task: `050. + Run`.
- For debugging press `F5`.

### Build, run and debug manually (Windows)

To build LD55 Hungry Portals on Windows, it's recommended to obtain the dependencies by using vcpkg. The following instructions assume that you will follow the vcpkg recommendations and install vcpkg as a subfolder. If you want to use "classic mode" or install vcpkg somewhere else, you're on your own.

This project define it's dependences:
1. In a `vcpkg.json` file, and you are pulling in vcpkg's cmake toolchain file.
2. As git submodules in the `thirdparty` directory. Because some of the libraries not available in vcpkg or have an error in the vcpkg port file.

First, we bootstrap a project-specific installation of vcpkg ("manifest mode") in the default location, `<project root>/vcpkg`. From the project root, run these commands:

```
cd LD55_Hungry_Portals
git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat
```

Now we ask vcpkg to install of the dependencies for our project, which are described by the file `<project root>/vcpkg.json`.  Note that this step is optional, as cmake will automatically do this.  But here we are doing it in a separate step so that we can isolate any problems, because if problems happen here don't have anything to do with your cmake files.

```
.\vcpkg\vcpkg install --triplet=x64-windows
```

Next build the project files. There are different options for
1. Telling cmake how to integrate with vcpkg: here we use `CMAKE_TOOLCHAIN_FILE` on the command line.
2. Select Ninja project generator.
3. Select Clang compiler.
4. Enable `CMAKE_EXPORT_COMPILE_COMMANDS` to generate a `compile_commands.json` file for clangd.

```
cmake -S . -B build -G "Ninja" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cd build
cmake --build .
```

Finally, we copy the assets and configuration file to the build directory.

```
cmake -E copy ../config.json ./src/config.json
cmake -E copy_directory ../assets ./src/assets
```

Run the game:

```
src\LD55_Hungry_Portals.exe
```

## Linux build

### Clone the Repository

```
git clone --recursive https://github.com/marleeeeeey/LD55_Hungry_Portals.git
```

### Prerequisites for Building the Project (Linux)

```bash
sudo apt update
sudo apt-get install python3 clang ninja-build curl zip unzip tar autoconf automake libtool python3-pip cmake
pip install jinja2
```

### Build, run and debug via VSCode tasks (Linux)

- Setup user friendly options via editing file [scripts/vscode_tasks_generator.py](scripts/vscode_tasks_generator.py).
- Run the script [scripts/vscode_tasks_generator.py](scripts/vscode_tasks_generator.py) to generate VSCode tasks with your options.
- Open the project folder in VSCode.
- Run task: `003. Install vcpkg as subfolder`.
- Run task: `050. + Run`.
- For debugging press `F5`.

### Build, run and debug manually (Linux)

```bash
cd LD55_Hungry_Portals
git clone https://github.com/microsoft/vcpkg && ./vcpkg/bootstrap-vcpkg.sh && ./vcpkg/vcpkg install --triplet=x64-linux
cmake -S . -B build -G "Ninja" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build/debug -- -k 0
cmake -E copy config.json build/debug/src/config.json
cmake -E copy_directory assets build/debug/src/assets
./build/debug/src/LD55_Hungry_Portals
```

## Web build

### Prerequisites for Building the Project (Web)

- Emscripten SDK additionally to Windows/Linux build prerequisites.

### Build, run and debug via VSCode tasks (Web)

- Set `self.build_for_web = BuildForWeb.YES` and other WebRelated options in [scripts/vscode_tasks_generator.py](scripts/vscode_tasks_generator.py). Example below:

```python

class WebBuildSettings:
    def __init__(self):
        self.build_for_web = BuildForWeb.YES
        self.emsdk_path = "C:/dev/emsdk"
        self.compiler = "emcc"
        self.path_to_ninja = "C:/dev/in_system_path/ninja.exe"  # Fix issue: CMake was unable to find a build program corresponding to "Ninja".  CMAKE_MAKE_PROGRAM is not set.

```

- Run the script [scripts/vscode_tasks_generator.py](scripts/vscode_tasks_generator.py) to generate VSCode tasks with your options.
- Open the project folder in VSCode.
- Run task: `003. Install vcpkg as subfolder`.
- Run task: `010. Configure`.
- Run task: `020. Build`.

### Build, run and debug manually (Web)

```bash
cd LD55_Hungry_Portals

git submodule update --init --recursive

C:/dev/emsdk/emsdk_env.bat &&  git clone https://github.com/microsoft/vcpkg && .\\vcpkg\\bootstrap-vcpkg.bat && .\\vcpkg\\vcpkg install --triplet=wasm32-emscripten

C:/dev/emsdk/emsdk_env.bat &&  cmake -S . -B build/debug_web -DCMAKE_BUILD_TYPE=Debug -GNinja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/dev/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_MAKE_PROGRAM=C:/dev/in_system_path/ninja.exe -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

C:/dev/emsdk/emsdk_env.bat &&  cmake --build build/debug_web -- -k 0
```

### Execute the game in the browser

```bash
python -m http.server
```

Open the browser and navigate to `http://localhost:8000/LD55_Hungry_Portals.html`

Press `F12` to open the developer console and see the game output.
