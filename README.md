# HaldCLUT
C/C++ generator for Hald Color Lookup Tables. Derived from [C code by Quelsolaar](http://www.quelsolaar.com/technology/clut.html).

## Dependencies
In order to output PNGs, libpng is required. To revert to TARGA files, undefine `HALDLUT_PNG_OUTPUT`.

## Building

    gcc src/create.c -o bin/create -lpng

## Usage

    bin/create <OUTPUT_FILE> <LEVEL>

For example:

    bin/create outputs/hald_clut.png 8

## Known issues
The TARGA output LUTs are offset horizontally. This is a bug in the original code from Quelsolaar, and in deprecating TARGA we're not interested in fixing it.

## Platform binaries

Windows binaries have been included in the `bin` directory.
