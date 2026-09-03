# CPL Project Template
## About
This is a setup for making projects with CPL. All dependencies are in 'dependencies/'.
Also this project uses nob.h - a build system in C (this can of course be changed if you do want to use CMake or Make).

## Important
This setup is for me and I use Gentoo Linux. That means that the libraries in 'dependencies/lib' are either .a or .so files (for Linux).
Additionally Gentoo uses X11 so if Wayland is required you should build the .a file for GLFW (libglfw3.a) yourself and replace it with this one here.
Otherwise you can directly use this ready to go project.

## How to build
In order to create and start the executable:
1. Run ./nob
2. Run ./build/<executable_name> (if nob.c is not edited, then ./build/a)
And that is already it
