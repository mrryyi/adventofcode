# Steps

* Install MSBuild/whatever (visual studio shit)
* Add MSBuild bin to path
* mkdir build
* CMake -S . -B build/
* Debug: MSBuild build/aoc_2022_09.vcxproj
* Release: cmake --build build/ --config Release