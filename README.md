# CPL Project Template
## About
This is a setup for making projects with CPL. All dependencies are in `dependencies/`.
Also this project uses nob.h - a build system in C (this can of course be changed if you do want to use CMake or Make).

## Important
This setup is for me and I use Gentoo Linux. That means that the libraries in `dependencies/lib/` are either `.a` or `.so` files (for Linux).
Additionally Gentoo uses X11 so if Wayland is required you should build the `.a` file for GLFW (`libglfw3.a`) yourself and replace it with this one here.
Otherwise you can directly use this ready to go project.

## How to build
In order to create and start the executable, execute these commands in the root of the project (replace <exe> with the actual executable name:

```bash
./nob
./build/<exe>

```
And that is already it

## nob.h

This is the whole starter `nob.c` file:

```c
#define NOB_IMPLEMENTATION
#define NOB_EXPERIMENTAL_DELETE_OLD
#include "build_tool/nob.h"

#define CC "clang"
#define SRC_FOLDER "src/"
#define BUILD_FOLDER "build/"
#define INCLUDE_FOLDER "dependencies/include"
#define LIB_FOLDER "dependencies/lib"
#define EXEC_NAME "a"
// DEV, REL or DEB build
#define DEV

const char *flags[] = {
#ifdef DEB
    "-fsanitize=address,undefined",
    "-fsanitize-recover=address",
    "-fno-omit-frame-pointer",
    "-g",
    "-O0"
#elifdef DEV
    "-g",
    "-O2",
    "-fno-omit-frame-pointer",
    "-DNDEBUG"
#else
    "-g",
    "-O3",
    "-ffast-math",
    "-DNDEBUG"
#endif
};

const char *src[] = {
    "main.c"
};

const char *libs[] = {
    "cpstd",
    "freetype",
    "glad",
    "glfw3",

    "m",
    "bz2",
    "png",
    "z"
};

int main(int argc, char *argv[]) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    if (!nob_mkdir_if_not_exists(BUILD_FOLDER)) {
        return 1;
    }
    Nob_Cmd cmd = {0};
    nob_cmd_append(&cmd, CC);
    for (int i = 0; i < sizeof(flags) / sizeof(*flags); ++i) {
        nob_cmd_append(&cmd, flags[i]);
    }
    char src_paths[sizeof(src) / sizeof(*src)][1024];
    {
        int n = sizeof(src) / sizeof(*src);
        memset(src_paths, 0, n * 1024);
        for (int i = 0; i < n; ++i) {
            strcat(src_paths[i], SRC_FOLDER);
            strcat(src_paths[i], src[i]);
            nob_cmd_append(&cmd, src_paths[i]);
        }
    }
    nob_cmd_append(&cmd, "-o", BUILD_FOLDER EXEC_NAME);
    nob_cmd_append(&cmd, "-I" INCLUDE_FOLDER);
    nob_cmd_append(&cmd, "-L" LIB_FOLDER);
    char lib_paths[sizeof(libs) / sizeof(*libs)][1024];
    {
        int n = sizeof(libs) / sizeof(*libs);
        memset(lib_paths, 0, n * 1024);
        for (int i = 0; i < n; ++i) {
            strcat(lib_paths[i], "-l");
            strcat(lib_paths[i], libs[i]);
            nob_cmd_append(&cmd, lib_paths[i]);
        }
    }
    if (!nob_cmd_run(&cmd)) {
        return 1;
    }
}
```

You do not need to understand all of it since what main does and the includes do not matter. But you should know what these ones do:

```c
#define CC "clang" // The name of your compiler (f.e. "gcc" or here "clang")
#define SRC_FOLDER "src/" // Folder of your source files
#define BUILD_FOLDER "build/" // Folder where the executable will be
#define INCLUDE_FOLDER "dependencies/include" // Folder where the headers for the dependencies are
#define LIB_FOLDER "dependencies/lib" // Folder where the lib files for the dependencies are
#define EXEC_NAME "a" // Name of your executable (f.e. "Game", "Test" etc.)
#define DEV // Build Mode (DEV = Dev, DEB = Debug, REL or nothing = Release)

// Flags (can be changed if wanted)
const char *flags[] = {
#ifdef DEB // Flags for Debug Build
    "-fsanitize=address,undefined",
    "-fsanitize-recover=address",
    "-fno-omit-frame-pointer",
    "-g",
    "-O0"
#elifdef DEV // Flags for Dev Build
    "-g",
    "-O2",
    "-fno-omit-frame-pointer",
    "-DNDEBUG"
#else // Flags for Release Build
    "-g",
    "-O3",
    "-ffast-math",
    "-DNDEBUG"
#endif
};

// Name of source files
const char *src[] = {
    "main.c"
};

// Name of the libraries (without lib or -l prefix)
const char *libs[] = {
    "cpstd",
    "freetype",
    "glad",
    "glfw3",

    "m",
    "bz2",
    "png",
    "z"
};
```
