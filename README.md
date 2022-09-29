# Reading Is Good

Don't save your skill books for later!

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++
* [SKSE64 SDK](https://skse.silverlock.org/)
	* Add the environment variable `SKSE64Path`
* [SkyUI SDK](https://drive.google.com/uc?export=download&id=0B4iEH8ar3jtxbFlkVzZSVHN0alk)
	* Add the environment variable `SkyUISDKPath`

## Register Visual Studio as a Generator
* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

## Building
```
git clone https://github.com/Exit-9B/Reading-Is-Good
cd Reading-Is-Good
git submodule update --init --recursive
cmake --preset vs2022-windows
cmake --build build --config Release
```
