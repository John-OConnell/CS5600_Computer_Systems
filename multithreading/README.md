# How to Run

In order to compile the necessary executables simply run make from the command line. This will produce
three executables: genRandWord, multithread, and unittests.

In order to generate the file of random words needed to pass to the multithread program, simply run:\
./genRandWord num-of-rand-words file-name\
For example, to generate a file of 10,000 words called test.txt you would run:\
./genRandWord 10000 example.txt

In order to then encode those words using the multithread progam, simply run:\
./multithread  file-name\
For the previous example, you would run:\
./multithread example.txt

In order to ensure the correct output, please make sure the "output" directory is present in the same folder
as the executables as this is where the output from the multithread program will be written.

In order to verify the code is working, you can run the unittests executable. The unittests executbale doesn't
take any arguments, and prints various messages to the screen based on what input is passed. The final unit
test takes the test.txt file as an input and creates an output that can be used to verify the encryption is
performing as expected. The test.txt file was manually generated to provide a simple way to validate the
encryption.
