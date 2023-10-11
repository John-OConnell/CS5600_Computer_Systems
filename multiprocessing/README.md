# How to Run

In order to compile the necessary executables simply run make from the command line. This will produce
three executables: genRandWord, multiprocess, and cipher. 

In order to generate the file of random words needed to pass to the multiprocess program, simply run:
./genRandWord <num-of-rand-words> <file>
For example, to generate a file of 10,000 words called test.txt you would run:
./genRandWord 10000 test.txt

In order to then encode those words using the multiprocess progam, simply run:
./multiprocess <file>
For the previous example, you would run:
./multiprocess test.txt

In order to ensure the correct output, please make sure the "output" directory is present in the same folder
as the executables as this is where the output from the multiprocess program will be piped.

Please note: the cipher executable is called in the multiprocess program and is not required to be run from
the command line at any point.