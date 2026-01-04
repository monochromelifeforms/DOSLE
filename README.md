# DOSLE

A clone of WORDLE that runs in DOS.

## How to Run

The only file that needs to be downloaded is `DOSLE.EXE`. Run this on any PC running some kind of DOS with an MDA or compatible
graphics card.

If you don't have such a computer, you can use DOSBOX. Be sure to set
```
machine = hercules
```
in the dosbox configuration file.

Currently, the game implements two text-mode-based representations of the
WORDLE grid. They can be selected with the /m or /M command line
arguments. (Use /h for a help message.)

The score is tracked in a file name derived from the executable file
name, replacing '.EXE' by '.SAV'. To reset the scores, simply delete
the .SAV file.

## Implementation Details

The game itself was developed 100% on a 286 with an MDA-compatible graphics adapter,
using Borland Turbo C++ 1.01.

Preprocessing the WORDLE list was done on a modern computer using python.

The software is not written with performance or file size in mind.
Instead, it makes full use of object-oriented C++ functionality.
I wanted to know how well C++ development would have worked in the
late 80s or early 90s. It turns out to work surprisingly well.

Currently, only MDA or compatible graphics adapters are supported.
The code does not use `conio.h` functionality, instead accessing the
video RAM at 0xB000 directly.

Due to the way C++ was used, extending it to CGA, EGA, or VGA adapters
should be trivial. If there is any interest, or if anyone else wants to attempt
implementing this, please let me know.
