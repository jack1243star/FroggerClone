FroggerClone
============

A clone of the classic game Frogger, written in C using libSDL.

Instructions
============

Move with `W`, `S`, `A`, `D`. Click on the bottom-left bar to adjust game speed.

Building Instructions
=====================

Tools
-----

*   Visual Studio

        Tested using Visual Studio Community 2015.

Dependencies
------------

The numbers in the parentheses denote tested revisions.

*   Simple DirectMedia Layer (2.0.5)

        Provides graphics, input handling and threading.
        Website: https://www.libsdl.org/

Steps
-----

1.  Download dependencies into corresponding directories. For example,
    put `SDL2-devel-2.0.5-VC.zip` into `Dependency\SDL2`.

2.  Extract the archives in-place.

3.  From top directory, run `nmake`. Note that this command comes with
    Visual Studio, and you might need "Developer Command Prompt" to
    do this.

4.  If anything goes wrong, check the error message and take a look at
    the makefile.

5.  The binaries are located under the `Release` directory.
