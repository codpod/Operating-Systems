#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <string>
#include <vector>

using namespace std;

class Flights
{

public:
    Flights(){};      //constructor
    bool data(string);
    int getYear();
    int getMonth();
    string getMonthName(); 
    int getDay();
    string getDate();
    string getKey();
    string getFlightNum();
    string getFlightLeg();

    string getFirst();
    string getLast();
    //string getName();

private:
    int year;
    int month;
    string monthName;
    int day;
    string date;       //#### Month ##

    int calcMonthNum(string monthShortName);
    string calcMonthName(int monthNum);
    //string name;       //Doe, Jane    
    string flightNum;  //WN###
    string flightLeg;  //NNN-NNN
    string flightKey;  //ABC###
    
    string last;
    string first;
};

bool flightCompare (Flights* a, Flights* b);
#endif