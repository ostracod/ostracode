
# OstraCode

A programming language by Jack Eisenmann

## Installation

To compile the interpreter, you will need these system-wide dependencies:

* C++ 17 compiler such as Clang or GCC
* Conan ^2.0.9
* CMake ^3.27.2

If you are using macOS, you can obtain a C++ compiler by installing the [Xcode command line tools](https://mac.install.guide/commandlinetools/index.html). Then you can use [Brew](https://brew.sh) to install Conan and CMake: `brew install cmake conan`

After you install the system-wide dependencies, perform these commands within the OstraCode repository directory:

```
conan profile detect --force
conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## Usage

TODO: Write this section.

## Design Goals

OstraCode has the following design goals:

* Support large and complex applications
* Enable highly flexible type relationships
* Allow multiple inheritance
* Avoid namespace collision
* Prevent side-effects of module imports
* Use self-consistent syntax
* Favor verbose and explicit constructs
* Preserve backward compatibility

## Language Documentation

To learn more about OstraCode, please consult these pages:

* [Fundamentals](languageDocumentation/fundamentals.md)
* [Syntax](languageDocumentation/syntax.md)
* [Operators and Specials](languageDocumentation/operators.md)
* [Statements](languageDocumentation/statements.md)
* [Built-In Constants](languageDocumentation/builtIn.md)
* [Example Code](languageDocumentation/exampleCode.md)
* [Feature System](languageDocumentation/featureSystem.md)
* [Package System](languageDocumentation/packageSystem.md)


