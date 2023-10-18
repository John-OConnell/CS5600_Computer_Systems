# Assignment / Syncronization with Montiors

### How to Run
Once the .tar file has been unzipped, use the terminal to navigate to the synchWithMonitors directory.
From there simply run "make" to build the project, and "make run" to run the project once it has been built.
Alternatively, you can run "make && make run" to build and run the project all at once. Running "make clean"
will remove all files created when building the project.

### Changing Project Variables
There are three variables that can be altered in this project: the number of producer threads, the number of
insertions made by each producer thread, and the capacity of the bounded buffer. Currently, the project is set
to 3 producer threads, 30 insertions per thread, and a bounded buffer capacity of 15.
All three variables are initialized in the main.java file on lines 7-9. To change them, simply open that file 
and change whichever variable you would like.