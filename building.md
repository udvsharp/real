### Requirements
- CMake 3.17+
### Instructions
1. Clone project from github: `git clone https://udv-code/real --recursive`
2. Create build directory: `mkdir build && cd build`.
3. Configure CMake project: `cmake ..` or with specific generator(for example, VS 2019) : `cmake -G "Visual Studio 16 2019" ..`
	- If you want to build sandbox project, you need to add `-DOPTION_REAL_BUILD_EXAMPLES=ON` to the end of your `cmake` command.

Then you need to build generated project.

### OR
Use CLion!

### MSVC
Generate project files with `"Visual Studio 16 2019"` generator, open generated `.sln` file in Visual Studio and run build.

### Other
Other build types are not tested for now so you can learn how to build CMake projects by yourself(example: [here](https://cliutils.gitlab.io/modern-cmake/chapters/intro/running.html)).