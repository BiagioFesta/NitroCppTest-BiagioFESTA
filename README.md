# NitroCppTest
![BuildStatus](https://travis-ci.org/BiagioFesta/NitroCppTest-BiagioFESTA.svg?branch=master)

##  How To Compile
### Requirements
  * [CMake](https://cmake.org/) as build system.
  * Compiler with `C++14` support.
  * [GTest](https://github.com/google/googletest) (optional, not needed for evaluation purpose).
  
### Build Procedure
The build procedure is quite standard for a *C++ project* using *CMake*.
 * Open your console/terminal.
 * Download the repository.
 * Change the *working directory* on the root directory of this repository.
 * Create a `build/` directory.
 * Enter in the `build/` directory and generate the build files: `cmake ..`
 * Build the project: `cmake --build .`

#### One-line Script:
On a *Linux* system you can just copy/paste the following commands to download and build the entire project:
~~~
git clone https://github.com/BiagioFesta/NitroCppTest-BiagioFESTA.git && \
cd NitroCppTest-BiagioFESTA && \
mkdir build && \
cd build && \
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TEST=NO && \
cmake --build .
~~~

#### Advanced Options
The build can be configured with two main parameters:
 * `CMAKE_BUILD_TYPE=(Debug|Release)`
 It can be `Debug` or `Release`. If you are planning to use the solver with a considerable size of the input, it is preferable to use `Release` in order to enable compiler optimisations.
 
 * `BUILD_TEST=(YES|NO)`
 By default, this option is disabled. For evaluation purpose, you do not need to launch Unit Tests. In case you want to enable the building of Unit Tests, you should have `GTest` library installed on your environment.
 Once build, you can launch the tests with the simple *CMake* command: `ctest`.

## Usage
The program can be launched from the command line. The synopsis of the command is the following:

~~~
./NitroCpp FILENAME
~~~

where `FILENAME` is the file given as input.

E.g. (let us assume you have built the binary file inside the `build` directory):

~~~
cd build && \
./NitroCpp ../data/inputExampleData.json
~~~

