# HaldCLUT
C/C++ generator for Hald Color Lookup Tables. Derived from [C code by Quelsolaar](http://www.quelsolaar.com/technology/clut.html).

## Dependencies
In order to output PNGs, libpng is required.

## Building

    gcc src/create.c -o bin/create -lpng

## Usage

    bin/create <OUTPUT_FILE> <LEVEL>

For example:

    bin/create outputs/hald_clut.png 8

## Platform binaries

Windows binaries have been included in the `bin` directory.
