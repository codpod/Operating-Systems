/********************************************************

Class:     CSCI 480 - 2
Program:   Assignment 2
Author:    Cody McAntire
Z-number:  z1859456
Date Due:  02/26/2021

Purpose: API use: uname << getenv << fork << wait and system
Execution: ./hw2.exe

*******************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h> 

using namespace std; 
#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1
void partA();
void partB();
void partC(); 

int main() 
{
    cout << unitbuf; //command to unbuffer the output at beginning of program

    partA(); //call part A

    partB(); //call part B

    partC(); //call part C

    return 0;
}

//function to neatly print part a
void partA()
{
    struct utsname buffer; //initialize buffer

    if (uname(&buffer) != 0) 
    {
        cerr << "error: uname";
        exit(-1);
    }
    cout << "SECTION A **************************************\n\n"; //display beginning of section a
    cout << "Field               File data                 API data\n\n"; //display header
    cout << "ostype" << setw(19) << buffer.sysname << setw(26) << buffer.sysname << endl; //print ostype linux
    cout << "hostname" << setw(18) << buffer.nodename << setw(26) << buffer.nodename << endl; //print hostname hopper or turing
    cout << "osrelease" << setw(26) << buffer.release << setw(26) << buffer.release << endl; //print osrealease 4.19.0-11-amd64
    string str (buffer.version); //string to resize version
    str.resize (24); //cut off the date
    cout << "version             " << setw(20) << str << setw(26) << str << endl; //print version without date #1 SMP Debian 4.19.146-1
    cout << "machine" << setw(45) << buffer.machine << endl << endl; //print machine x86_64
}//end part A



void partB()
{
    cout << "SECTION B **************************************\n\n"; //display beginning of section b

    string env_fullpath = getenv("PATH"); //use getenv to find the full path
    char* fullpath = getenv("PATH"); //set the full path 
    int length = strlen(fullpath) -1; //find length of full path 
    cout << "Full path: " << endl << env_fullpath << "    " << length << " bytes"<< endl << endl; //display the full path 
    cout << "PATH:" << setw(45) <<   "LENGTH:\n\n"; //display header

    size_t i = 0; //set size
    string path = ":"; //to know when to move to next path
    string pl; //path length string
    int bytes = 0; //int to count bytes
    int paths = 0; //int to incriment paths
    while ((i = env_fullpath.find(path)) != std::string::npos) //loop through path
    {
        pl = env_fullpath.substr(0, i); //set the path length
        cout << setw(25) << left << pl <<setw(20) << right << pl.length() <<'\n'; //format lengths
        
        bytes += pl.length(); //count length of each path
        paths++; //go through each path
        
        env_fullpath.erase(0, i + path.length());
    }
    cout << setw(20) << left << env_fullpath << setw(25) << right << env_fullpath.length() << "\n\n"; //format path
    int totalbytes = length - 4; //calculate total bytes which is length of path entry minus number of colons
    cout << "Total: " << setw(38) << totalbytes << " bytes  " << paths+1 << " entries \n\n"; //print total bytes and paths

}//end part B

void partC()
{
    cout << "SECTION C **************************************" << endl << endl; //display beginning of section c
    setbuf(stdout, NULL);
	char write_msg[BUFFER_SIZE];
	char read_msg[BUFFER_SIZE];
	pid_t pidChildA, pidChildB;
	int pipeA[2]; //pipeA where pipeA[0] for read end and pipeA[1] for write end.
	int pipeB[2]; //pipeB where pipeB[0] for read end and pipeB[1] for write end.

	if (pipe(pipeA) == -1) //if pipe A fails
	{
		cerr << "pipe A failed"; //let user know
	}
	if (pipe(pipeB) == -1) //if pipe B fails
	{
		cerr << "pipe B failed"; //let user know
	}
	pidChildA = fork(); //create child for original process
	pidChildB = fork(); //create its own child, child B

	if (pidChildA < 0) //if fork fails
	{
		cerr << "Fork failed"; //let user know
	}

    //Parent
	if (pidChildA > 0 && pidChildB > 0)
	{  
		close(pipeA[READ_END]); //close end of pip a
        ostringstream parentmsg; //ostringstream to build message before printing
		parentmsg << "Parent: My PID is " << getpid() << ".\n" //display parents PID
        << "My parent is " << getppid() << ".\n" //display parents parent
        << "My children are " << pidChildA << " and " << pidChildB << ".\n\n" //display the two children
        << "Parent: Issuing command: /bin/ps -f --ppid " << getppid() << ", " << getpid() << ", " << pidChildA << "\n\n"; 
        cout << parentmsg.str(); //print parent's full info

		close(pipeA[WRITE_END]); //close write end of pipe a

   		char command[100]; //will be used to print processes
		sprintf(command, "/bin/ps -f --ppid %d,%d,%d,%d ", getppid(), getpid(), pidChildA, pidChildB); //set up command to invoke
        system(command); //display processes using command made earlier
        cout << "\n";

		while (waitpid(pidChildA, NULL, 0) > 0 || waitpid(pidChildB, NULL, 0) > 0); //wait till children are finished executing

        cout << "Parent: All processes finished. \n"; //display processes finished
	}

    //Middle
	else if (pidChildA == 0 && pidChildB > 0) //go into middle
	{   
		close(pipeB[READ_END]); //close end of pipe

        ostringstream middlemsg; //ostringstream to build message before printing
        middlemsg << "Middle: My PID is " << getpid() << ".\n" //display middle PID
        << "My parent is " << getppid() << ".\n" //display middle's parent
        << "My child is " << pidChildB << ".\n\n"; //display middle's child
        cout << middlemsg.str(); //print middle's full info

		write(pipeB[WRITE_END], write_msg, strlen(write_msg)); //write to the end of pipe

		close(pipeB[WRITE_END]); //close write 
		sleep(3); //Sleep for 3 seconds.
        ostringstream middleawake; //hold message to show middle is awake
        middleawake << "Middle: " << getpid() << " is awake. \n\n"; //build message
        cout << middleawake.str(); //display the status of middle
	}

    //Child a
	else if (pidChildA > 0 && pidChildB == 0) //go into first child
	{
		close(pipeA[WRITE_END]); //close end of pipe
		read(pipeA[READ_END], read_msg, BUFFER_SIZE); //read from pipe

        ostringstream childAmsg; //stringstream to hold child A's message
        childAmsg << "Child: My PID is " << getpid() << ".\n" //display first childs PID
        << "My parent is " << getppid() << ".\n\n"; //display childs parent
        cout << childAmsg.str(); //print child A's info

		close(pipeA[READ_END]); //close read end of pipe a
		sleep(3); //Sleep for 3 seconds.
        ostringstream childAawake; //hold message to show child A is awake
        childAawake << "Child: " << getpid() << " is awake.\n\n"; //build child A awake message
        cout << childAawake.str(); //print child a is awake
	}

    //Child b
	else
	{
		close(pipeB[WRITE_END]); //close end of pipe b
		read(pipeB[READ_END], read_msg, BUFFER_SIZE); //read from pipe b

        ostringstream childBmsg; //ostringstream to hold child B's message
        childBmsg << "Child: My PID is " << getpid() << ".\n" //display PID of this child
        << "My parent is " << getppid() << ".\n\n"; //display parent of this child
        cout << childBmsg.str(); //print child A's info

		close(pipeB[READ_END]); //close read end of pipe b
		sleep(3); //sleep for 3 seconds
        ostringstream childBawake; //hold msg saying child b is awake
        childBawake << "Child: " << getpid() << " is awake.\n\n"; //build child b awake message
        cout << childBawake.str(); //print child b is awake
	}
}//end part C
