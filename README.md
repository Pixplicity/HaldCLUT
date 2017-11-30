# HaldCLUT
C generator for Hald Color Lookup Tables

## Dependencies
In order to output PNGs, libpng is required. To revert to TARGA files, undefine `HALDLUT_PNG_OUTPUT`.

## Building

    gcc src/create.c -o bin/create -lpng

## Usage

    bin/create outputs/hald_clut.png 8

## Known issues
The TARGA output LUTs are offset horizontally. This is a bug in the original code from Quelsolaar, and in deprecating TARGA we're not interested in fixing it.

## Platform binaries

Windows binaries have been included in the `bin` directory.
