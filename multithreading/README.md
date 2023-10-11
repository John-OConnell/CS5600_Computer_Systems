# How to Run

In order to compile the necessary executables simply run make from the command line. This will produce
two executables: genRandWord, and multithread.

In order to generate the file of random words needed to pass to the multithread program, simply run:\
./genRandWord num-of-rand-words file-name\
For example, to generate a file of 10,000 words called test.txt you would run:\
./genRandWord 10000 test.txt

In order to then encode those words using the multithread progam, simply run:\
./multithread  file-name\
For the previous example, you would run:\
./multithread test.txt

In order to ensure the correct output, please make sure the "output" directory is present in the same folder
as the executables as this is where the output from the multithread program will be written.
