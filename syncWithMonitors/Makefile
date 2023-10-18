JFLAGS = -g
CLASSPATH = ./src
OUTDIR = ./out
JC = javac
MAIN_CLASS = boundedBuffer.main  # Update this to your main class

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) -d $(OUTDIR) -cp $(CLASSPATH) $*.java

CLASSES = \
	  src/boundedBuffer/BoundedBuffer.java \
	  src/boundedBuffer/producerThread.java \
	  src/boundedBuffer/consumerThread.java \
	  src/boundedBuffer/main.java

default: classes

classes: $(CLASSES:.java=.class) \

run:
	java -cp $(OUTDIR) $(MAIN_CLASS)

clean:
	@$(RM) $(OUTDIR)/boundedBuffer/*.class
