JC = javac
ANT = java -jar /usr/local/lib/antlr-4.5.3-complete.jar
SRC = *.java
GRA = C.g4

all: listener compile

listener:
	$(ANT) $(GRA)

visitor:
	$(ANT) -no-listener -visitor $(GRA)	

compile:
	$(JC) $(SRC)

clean:
	rm -f *.class *.tokens

test1:
	java C2CApp hello.c

test2:
	java C2CApp score.c 

test3:
	java C2CApp score2.c

clean_dist:
	rm -f CBaseListener.java CLexer.java CListener.java CParser.java
