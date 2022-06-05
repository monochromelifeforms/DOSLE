A clone of WORDLE that runs in DOS.

It was developed on a 286 with an MDA-compatible graphics adapter,
using Borland Turbo C++ 1.01.

The build that is included in the git repository was built on that 286,
though it should also work on XT class machines.

Currently, only MDA or compatible graphics adapters are supported.
The code does not use conio.h functionality, instead accessing the
video RAM at 0xB000 directly.

It currently implements two text-mode-based representations of the
WORDLE grid. They can be selected with the /m or /M command line
arguments. (Use /h for a help message.)

The score is tracked in a file name derived from the executable file
name, replaceing '.EXE' by '.SAV'. To reset the scores, simply delete
the .SAV file.

The software is not written with performance or file size in mind.
Instead, it makes full use of object-oriented C++ functionality.
I wanted to know how well C++ development would have worked in the
late 80s or early 90s. It turns out to work surprisingly well.

