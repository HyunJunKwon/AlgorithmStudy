JC = javac
ANT = java -jar /usr/local/lib/antlr-4.5.3-complete.jar
SRC = *.java
GRA = AutoC.g4

all: visitor compile

listener:
	$(ANT) $(GRA)

visitor:
	$(ANT) -visitor $(GRA)	

compile:
	$(JC) $(SRC)

clean:
	rm -f *.class *.tokens

clean_dist:
	rm -f CBaseListener.java CLexer.java CListener.java CParser.java
