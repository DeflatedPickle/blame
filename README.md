# blame
A curses-like library for C++.

## Compatibility
Your terminal will need to implement at least the ANSI escape code for moving the caret for Blame to look readable, and the font used will need to support the [block elements](https://en.wikipedia.org/wiki/Block_Elements) and [box drawing](https://en.wikipedia.org/wiki/Box_Drawing) unicode blocks.

## Demos
### Widgets
The `/demos/widgets` folder contains a demonstration of different widgets offered by Blame.
### Dim
The `/demos/dim` folder contains a Vim-like demonstration.

## Building
### Windows
To build the library on Windows, you will need [CMake](https://cmake.org/) 3.13 or higher and [Cygwin](https://www.cygwin.com/) 2.11.2 or higher (Cygwin is required as it is the only, to my knowledge, GNU tool distribution on Windows to support libraries such as `termios` and `ioctl`).