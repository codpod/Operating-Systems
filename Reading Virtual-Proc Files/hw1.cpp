/***************************************

 Class:     CSCI 480 - 2
 Program:   Assignment 1
 Author:    Cody McAntire
 Z-number:  z1859456
 Date Due:  01/29/2020

 Purpose: Reading Virtual/proc files
 Execution: ./hw1.exe

***************************************/
#include "procInfo.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

    void numRecords();
    void numCharacters();

    void numCores();
    void numPhysCores();
    void physIds();

    void firstProcessor();
    void uptime();
int main () 
{
//part A answers in full sentences
cout << "A. Questions about the cpuinfo file" << endl;
cout << "1. The file names are " << ( "/proc/cpuinfo" ) << "and" << ( "/proc/uptime" )<< "." << endl; //answers question A-1
numRecords(); //answers question A-2
numCharacters(); //answers question A-3 and A-4

cout << "B: Questions about the configuration" << endl;
numCores(); 
numPhysCores(); 
physIds(); 

cout << endl;

cout << "C: Questions about processor 0" << endl;
firstProcessor();
cout << endl;

cout << "D. Questions about uptime" << endl;
uptime(); 
	return 0;
}

void numRecords()
{
	int numLines = 0;
	string lines;
	ifstream file{ "/proc/cpuinfo" }; //open first file

	while(getline(file, lines))
		++numLines;
	cout << "2. There are " << numLines << " records in the first file." << endl; //display number of records (216)
}

//function for part A question 3 - how many characters
void numCharacters()
{
	ifstream file{ "/proc/cpuinfo" }; //open first file
	char ch;
        int i;
	int numCharacters = -1;
	while(file)
	{
		file.get(ch);
		i = ch; //set i to ch to assign int to chars
		if(i > 0 && i < 127) 
			numCharacters++; //count each character
	}
	cout << "3. There are " << numCharacters << " characters in the first file." << endl; //display number of characters (8584)
	cout << "4. The system utilities I used for answers two and three were getline and get." << endl << endl;
}

//function for Part B Question 1 - how many machine processors
void numCores()
{
	size_t pos = 0;
	int numCPUs = 0;
	string countCPU = "";

	ifstream file{ "/proc/cpuinfo" }; //file to operate on
	string const procInfo = static_cast<ostringstream&>(ostringstream{} << file.rdbuf()).str(); //cast cpuinfo to string

	pos = procInfo.rfind("processor") + 12; //find the word processor and set position
	countCPU = procInfo.substr(pos, 2);

	stringstream data(countCPU);
	data >> numCPUs;
	numCPUs++; //count the number of processors

	cout << "1. There are " << numCPUs << " processors in this system." << endl; //display processors (8)
}

//function for Part B Question 2 - how many physical CPUs
void numPhysCores()
{
	int pos = 0;
	int phyCPU = 0;
	string countPhyID = "";

    ifstream file{ "/proc/cpuinfo" }; //file to get info from
	string const fileInfo = static_cast<ostringstream&>(ostringstream{} << file.rdbuf()).str(); //cast to string

	pos = fileInfo.rfind("physical id") + 14; //set position to word physical id
	countPhyID = fileInfo.substr(pos, 2);

	stringstream x(countPhyID);
	x >> phyCPU;
	phyCPU++; //count number of physical IDs
	
	cout << "2. There are " << phyCPU << " physical CPUs in this system." << endl; //display physical CPUs (2)
}

void physIds()
{
	string physicalIDf = "";
	string physicalIDb = "";
	int physIDa = 0; 
	int physIDb = 0;

	ifstream inFile("/proc/cpuinfo"); //go in file
	string const procInfo = static_cast<ostringstream&>(ostringstream{} << inFile.rdbuf()).str(); //cast to string

	physIDa = procInfo.find("physical id"); //find position of first physical id
	physicalIDf = procInfo.substr(physIDa +14, 1); //set first physical ID
	physIDb = procInfo.rfind("physical id"); //go backwards to find position of second physical id
	physicalIDb = procInfo.substr(physIDb + 14, 1); //set first physical ID

	cout << "3. The physical IDs are " << physicalIDf << ", " << physicalIDb << "." << endl;
	cout << "4. There are processors that share cache." << endl;
}

//function for part C - questions about processor 0
void firstProcessor()
{
	string physAddressSize = "";
	string virtAddressSize = "";
	string cacheSize ="";
	int posP = 0;
	int ratio = 0;
	int posC = 0;
	int cacheBytes = 0;

	ifstream inFile("/proc/cpuinfo"); //go in file
	string const procInfo = static_cast<ostringstream&>(ostringstream{} << inFile.rdbuf()).str(); //cast to string

	posP = procInfo.rfind("address sizes"); //find position of physical size
	physAddressSize = procInfo.substr(posP+16, 2); //set physical address size
	virtAddressSize = procInfo.substr(posP+34, 2); //set virutal address size

	int i_physAddressSize = stoi (physAddressSize); //convert string physAddressSize to integer
	int i_virtAddressSize = stoi (virtAddressSize); //convert strong virtAddressSize to integer
	ratio = (  (i_virtAddressSize - i_physAddressSize) * (i_virtAddressSize - i_physAddressSize) ); //use converted address sizes to calculate ratio

	posC = procInfo.rfind("cache size"); //find position of cache size
	cacheSize = procInfo.substr(posC+13, 8); //set cache size

	int i_cacheSize = stoi (cacheSize); //convert cache string to integer
	cacheBytes = (i_cacheSize * 1024); //calculate cache size in bytes

	cout << "1. The physical address size is " << physAddressSize << " bytes." << endl; //display physical address size (46)
	cout << "2. The virtual address size is " << virtAddressSize << " bytes." << endl; //display virtual address size (48)
	cout << "3. The ratio of physical to virtual size is " << ratio << "." << endl; //display ratio (2^(v bits - p bits))
	cout << "4. This CPU has a floating point unit." << endl; //display fpu (yes)
	cout << "5. The cache has " << cacheSize << "." << endl; //display cache size (10240KB)
	cout << "6. The cache has " << cacheBytes << " bytes." << endl;
}

//function for part D - Questions about uptime
void uptime()
{
        ifstream inFile;
	string time ="";

	int seconds = 0;
	int minutes = 0;
	int hours = 0;
	int days = 0;
	int n = 0;

	inFile.open("/proc/uptime"); //open uptime
	inFile >> time; //get time
	inFile.close(); //close uptime

	cout << "1. The system has been up for " << time << " seconds." << endl; //display uptime seconds

	n = stof (time);
	days = n / (24 * 3600);

	n = n % (24 * 3600); 
        hours = n / 3600; 

        n %= 3600; 
        minutes = n / 60 ; 

        n %= 60; 
        seconds = n; 

	cout << "2. The system has been up for " << days << " days, " << hours << " hours, " << minutes << " minutes, and " << seconds << " seconds." << endl; //display uptime
}
