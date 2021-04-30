# COURSE:     CSCI 480-2
# PROGRAM:    Assignment 2
# PROGRAMMER: Cody McAntire
# Z ID:       z1859456
# DATE DUE:   02/26/21

# Compiler variables
CCFLAGS = -ansi -Wall -std=c++11 -Wextra

#Rule to combine object code files to create executable file
hw2.exe: hw2.o
	g++ $(CCFLAGS) -o hw2.exe hw2.o

#Rule to compile source code files to object code
hw2.o: hw2.cpp
	g++ $(CCFLAGS) -c hw2.cpp

# Pseudo_target to execute the executable file
execute:
	./hw2.exe

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o hw2.exe