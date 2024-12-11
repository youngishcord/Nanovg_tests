OpenGL template using CMake for build with GLM, GLEW and GLFW libs
=======================

Example in `src` written on `C`, but `CPP` is possible.

Clone (With submodules):
========================

```bash
git clone ----recursive-submodules https://github.com/youngishcord/OpenGL_template.git
```
or
```bash
git submodule init
git submodule update
```

Build
========================

I use MinGW-64 by MSYS2. VSCode and CMake v3.21.2
```bash
cd /project
mkdir build
cd build 
cmake ..
make
```
or use VSC CMake plugin