# Math Parser
A small CLI app to parse a mathematical expression into a postfix tree and to evaluate such a tree into a numerical results. It uses an implementation of [shunting-yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm).

## Installation notes
It requires CMake to generate makefiles (e.g. to install CMake on Fedora, run 'sudo yum cmake').
The project utilizes [Google Tests](https://github.com/google/googletest/) for unit testing.
To produce the test binaries, download the content of the [test repository](https://github.com/google/googletest/) into '/tst' directory and run CMake, e.g., by running 'cmake . -DCMAKE\_BUILD\_TYPE=Release -G \"Unix Makefiles\"' in the root directory.

CMake will produce Makefile in the bin directory. Resulting test binary will be made in 'bin/tst' directory.

## Math expressions and known limitations
At this stage the parser can read expressions involvilg numbers, 1-char variables and operations '+', '-', '*', '/'. 
 
