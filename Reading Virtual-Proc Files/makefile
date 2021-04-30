
# COURSE:     CSCI 480-2
# PROGRAM:    Assignment 1
# PROGRAMMER: Cody McAntire
# Z ID:       z1859456
# DATE DUE:   01/29/20

# Compiler variables
CCFLAGS = -ansi -Wall -std=c++11 -Wextra

#Rule to combine object code files to create executable file
hw1.exe: hw1.o procInfo.o
	g++ $(CCFLAGS) -o hw1.exe hw1.o procInfo.o

#Rule to compile source code files to object code
hw1.o: hw1.cpp procInfo.h
	g++ $(CCFLAGS) -c hw1.cpp

procInfo.o: procInfo.cpp procInfo.h
	g++ $(CCFLAGS) -c procInfo.cpp

# Pseudo_target to execute the executable file
execute:
	./hw1.exe

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o hw1.exe
