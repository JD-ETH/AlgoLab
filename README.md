# AlgoLab2016

**Overview**

My solutions for class Algorithms Lab in ETH, Autumn 2016 

Not coming from the computer science background, I have been trying to learn some coding with this class. That's why I was switching between different editors/IDE during the class, which can make my folder structure bit messy.

This was for my personal learning purpose, thus the documentations are often incomplete or insufficient.

**Compiling**

For simple programs which use only STL for compilation use:
```
g++ -std=c++11 <file_name>
```
For programs using BGL we compile using:
```
g++ -std=c++11 -I /usr/local/include/ <file_name>
```
For programs using CGAL it is necessary to first create Cmake file using:
```
cgal_create_cmake_script .
```
in the working directory. Then create Makefile
```
cmake .
```
and then running and compile it:
```
make
```
