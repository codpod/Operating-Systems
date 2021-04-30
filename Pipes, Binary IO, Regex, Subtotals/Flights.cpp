#include "Flights.h"

#include <iostream> 
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string.h>
#include <regex>
using namespace std;

bool Flights::data(string str) 
{
    bool ret;
    string yearz;
    string monthz;
    string dayz;

    //ifstream file { "/home/turing/t90rkf1/d480/dhw/hw3-air/resv0.txt" }; //file to work in
    regex re("(\\d\\d)(\\w{3})(\\d\\d)/(\\w{5})/(\\w{3}-\\w{3})/(\\w{6})/(\\w+)/(\\w+)/(.*)");
    //                         DD     MMM      YY  /   FLY# / FRM-TO / KEY  /  LAST  / FIRST  / REST
    //                          1      2       3        4       5       6       7       8        9
    smatch matches;
    ret = regex_match(str, matches, re);
    if (!ret) //if parse fails
    {
        cout << "could not parse input record: " + str + "\n\n";
        return false;
    }
    //date setting
    dayz   = matches[1]; //set day
    monthz = matches[2]; //set month
    yearz  = matches[3]; //set year
    day = stoi(dayz); //convert day
    date = dayz + monthz + yearz; //set all to date
    month = calcMonthNum(monthz); //get month number
    monthName = calcMonthName(month); //set month name to full month
    year = 2000 + stoi(yearz); //convert year and add 2000 so its four digits

    //flight details
    flightNum = matches[4]; //set flight number WN###
    flightLeg = matches[5]; //set city pair NNN-NNN
    flightKey = matches[6]; //set locator ABC###
    last      = matches[7]; //set last name 
    first     = matches[8]; //set first name
    return true;

}

int Flights::calcMonthNum(string monthShortName)
{
    string monthAbbr[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUNE", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"}; //month abbreviations from file
    string* index; //declare an index stringptr 
    int ret; //int to return
    index = find(monthAbbr, monthAbbr+12, monthShortName);
    ret = index - monthAbbr + 1;
    return ret; //return month num
}
string Flights::calcMonthName(int monthNum)
{
    string monthFull[12] = {"January", "February", "March", "April", "May", "June", "July",
                            "August", "September", "October", "November", "December"}; //full month names
    string ret;
    ret = monthFull[monthNum - 1];
    return ret;
}
string Flights::getDate()
{
    return date;
}

int Flights::getYear()
{
    return year;
}
int Flights::getMonth()
{
    return month;
}
string Flights::getMonthName()
{
    return monthName;
}
int Flights::getDay()
{
    return day;
}

string Flights::getFirst()
{
    return first;
}
string Flights::getLast()
{
    return last;
}

string Flights::getKey()
{
    return flightKey;
}

string Flights::getFlightNum()
{
    return flightNum;
}

string Flights::getFlightLeg()
{
    return flightLeg;
}

//compare function for stable sort
bool flightCompare (Flights* a, Flights* b)
{
    bool ret;

    if (a->getYear() != b->getYear())
    {
        ret = (a->getYear() < b->getYear());
        return ret;
    }

    if (a->getMonth() != b->getMonth())
    {
        ret = (a->getMonth() < b->getMonth());
        return ret;
    }

    if (a->getDay() != b->getDay())
    {
        ret = (a->getDay() < b->getDay());
        return ret;
    }


    if (a->getFlightNum() != b->getFlightNum())
    {
        ret = (a->getFlightNum() < b->getFlightNum());
        return ret;
    }


    if (a->getFlightLeg() != b->getFlightLeg())
    {
        ret = (a->getFlightLeg() < b->getFlightLeg());
        return ret;
    }

    if (a->getLast() != b->getLast())
    {
        ret = (a->getLast() < b->getLast());
        return ret;
    }


    if (a->getFirst() != b->getFirst())
    {
        ret = (a->getFirst() < b->getFirst());
        return ret;
    }

    ret = true;
    return ret;
}
