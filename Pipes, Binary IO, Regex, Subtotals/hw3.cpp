/******************************************************************

Author:    Cody McAntire

Purpose:	1. uses fork() to create a partent/child set up
			2. pipe set up between parent and child so parent is 
            	producer and child is consumer
			3. interlacing of messages printed by different 
            	processes depend on timing of program
		
Execution: ./hw3.exe

*******************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

#include <vector>
#include <sstream>
#include <string>
#include <cstring>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>

#include "Flights.h"

using namespace std;

int main(int argc, char *argv[])
{
	vector<Flights*> flight; //flights pointer

	//pipe and fork
	int pid;
	int fd[2];
	int ret;

	//file
	//bool beg_of_file = true;
	ifstream file;
	string filename;

	cout << unitbuf; //prevent buffering


	//create pipe
	ret = pipe(fd);
	if ( ret== -1)
    {
        cerr << "Pipe Failed" << ret << endl; //tell user it didnt work
        exit(-1);
    }

	//fork another process
	pid = fork();
    if (pid < 0) //error
    {
        cerr << "Fork Failed" << ret << endl; //show user error
        exit(-1);
    }

    // Parent process (producer)
    if (pid > 0)
    {
		close (fd[0]); //close read end
		if (argc == 2)
			filename = argv[1];
		else
			filename = "/home/turing/t90rkf1/d480/dhw/hw3-air/resv0.txt" ; //file were using

		file = ifstream(filename);
		if(file.fail()) //file doesnt open
		{
			cerr << "cant open file " + filename + "\n"; //let user know
			exit(-1);
		}

		int linenum = 0; //to count line number
		int bytes = 0;
		int length = 1000; //the length of file
		string line;
		bytes = line.length(); //find the length of each line
		char record[1000]; 
		while (true)
		{
			getline(file, line);
			strncpy(record, line.c_str(), 999); 
			if (file.eof())
				break; //break at end of file
			
			linenum++; //iterated and count each record number
			ostringstream prmsg; //to avoid overloading 
			prmsg << "parent read record # " << setw(2) << linenum << ": " << record << "\n";
			cout << prmsg.str(); //print all parent record info formatted above

			bytes = strlen(record);
			write (fd[1], record, 1000);
			ostringstream pwmsg; //for write message
			pwmsg << "parent wrote " << setw(2) << length 
			<< " bytes w/ msg of " << bytes << " bytes plus term\n\n";
			cout << pwmsg.str(); //print parent write info formatted above
		}
		file.close();
		close (fd[1]); //close write end
	}//end parent process

    // child process (consumer)
    if(pid == 0)
    {
		close(fd[1]); //close unused write end

		int records;
		int bytes;
		char readmsg[1000];
		records = 0;
		while (true) //loop to read binary input
		{
			bytes = read(fd[0], readmsg, 1000); //read from pipe
			if (bytes == 0)
				break;

			records += 1; //count each record
			ostringstream crmsg; //for child read message
			crmsg << "child read record # " << setw(2) << records << ": " << readmsg << "\n";
			cout << crmsg.str(); //print child record 
			
			ostringstream cbmsg; //for child bytes read msg
			cbmsg << "child read " << setw(2) << bytes 
			<< " bytes w/ msg of " << strlen(readmsg) << " bytes plus term\n\n";
			cout << cbmsg.str(); //print second child message

			string input;
			input = readmsg; //convert char array to string of input

			Flights* flightp = new Flights(); //build Flights
			ret = flightp->data(input);
			if(!ret)
			{
				ostringstream er;
				er << "**** could not parse last record\n\n";
				cout << er.str();
				exit(-1);
			}
			flight.push_back(flightp);
		}//end of binary input / output
		close (fd[0]);//close read end

		string prev_flightLeg;
		string prev_flightNum;
		string in_flightLeg;
		string in_flightNum;
		string in_number;

		int prev_day;
		//int prev_month;
		int prev_year;
		
		string prev_monthName;
		string prev_key; // locator
		string prev_firstName;
		string prev_lastName;



		bool beg_of_file = true;

		ifstream in_file;
		in_file.open("/home/turing/t90rkf1/d480/dhw/hw3-air/resv0.txt");
		//sort vector
		stable_sort (flight.begin(), flight.end(), flightCompare);

		int num = 0;
		for (auto a : flight)
		{
			prev_flightLeg = a->getFlightLeg(); //bwi-fll
			prev_flightNum = a->getFlightNum();	//wn123
			prev_day       = a->getDay();
			//prev_month     = a->getMonth();
			prev_year      = a->getYear();
			prev_monthName = a->getMonthName();
			prev_key       = a->getKey();
			prev_firstName = a->getFirst();
			prev_lastName  = a->getLast();
			cout << prev_year << "  " << prev_monthName << "  " << prev_day << "  " 
			<< prev_flightNum << "  " << prev_flightLeg << "  " << num << "  "
			<< prev_key << "  " << prev_lastName << ", " << prev_firstName << endl;
			num++;
			if(in_file.eof())	break;
			if(beg_of_file)
			{
				beg_of_file = false;
			}

			cout << prev_year << "  " << prev_monthName << "  " << prev_day << "  " 
			<< prev_flightNum << "  " << prev_flightLeg << "  " << num << endl << endl;

		};

		//eoj output
		cout << prev_year << "  " << prev_monthName << "  " << prev_day << "  " << prev_flightNum << "  " << prev_flightLeg<< "     1     *       Passengers this leg\n\n";
		cout << prev_year << "  " << prev_monthName << "  " << prev_day << "  " << prev_flightNum << "              1     **      Passengers all legs\n\n";
		cout << prev_year << "  " << prev_monthName << "  " << prev_day << "  " << "                   1     ***     Date total\n\n";
		cout << prev_year << "  " << prev_monthName << "  " << "                      1     ****    Month total\n\n";
		cout << "                                     5     *****   Grand total\n\n";
		in_file.close();
		close (fd[1]);
	}//end child/consumer process
return 0;
}
