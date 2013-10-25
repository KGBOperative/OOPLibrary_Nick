// File: Date.cpp
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contents the implementation of a class called Date

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Date.h"
#include <stdio.h>
#include <cstring>
#include <ctime>

using namespace std;

// Default constructor
Date::Date ()
{
  month = 0;
  day = 0;
  year = 0;
  Month = Day =  "00";
  Year = "0000";
}

// Copy constructor
Date::Date (const Date & D)
{
  month = D.month;
  day = D.day;
  year = D.year;
  Month = D.Month;
  Day = D.Day;
  Year = D.Year;
}
  
// Empty Destructor
Date::~Date ()
{}

// Assignment Operator
Date & Date :: operator = (const Date & D)
{
  month = D.month;
  day = D.day;
  year = D.year;
  Month = D.Month;
  Day = D.Day;
  Year = D.Year;
}

// Month Mutator
void Date :: SetMonth (int inMonth)
{
  month = inMonth;
}

// Day Mutator
void Date :: SetDay (int inDay)
{
  day = inDay;
}

// Year Mutator
void Date :: SetYear (int inYear)
{
  year = inYear;
}

// Month Mutator
void Date :: SetMonthStr (string inMonth)
{
  Month = inMonth;
}

// Day Mutator
void Date :: SetDayStr (string inDay)
{
  Day = inDay;
}

// Year Mutator
void Date :: SetYearStr (string inYear)
{
  Year = inYear;
}

// Month Accessor
int Date :: GetMonth () const
{
  return month;
}

// Day Accessor
int Date :: GetDay () const
{
  return day;
}

// Year Accessor
int Date :: GetYear () const
{
  return year;
}

tm Date :: maketm (int year, int month, int day)
{
  tm tm1 = {0};
  tm1.tm_year = year - 1900;
  tm1.tm_mon = month - 1;
  tm1.tm_mday = day;
  return tm1;
}

// Calcualtes difference (in days) between two dates.
double Date :: operator - (const Date & D)
{
  int bDay = D.day;
  int bMonth = D.month;
  int bYear = D.year;
  
  tm tm1 = maketm (year, month, day);
  tm tm2 = maketm (bYear, bMonth, bDay);
  time_t time1 = mktime (&tm1);
  time_t time2 = mktime (&tm2);

  const int seconds = 60*60*24;
  
  time_t difference = (time1 - time2) / seconds;

  return difference;
}

// Returns true if "this" date is earlier than the passed date.
bool Date :: operator < (const Date & D) const
{
  if (year < D.year)
    return true;
  if (month < D.month)
    return true;
  if (day < D.day)
    return true;
  return false;
}

// Returns true if "this" date is later than the passed date.
bool Date :: operator > (const Date & D) const
{
 if (year > D.year)
    return true;
  if (month > D.month)
    return true;
  if (day > D.day)
    return true;
  return false;
}

// Reads in a date in a formatted way. Gets both int and string versions. 
void Date::ReadIn(istream & ins)
{
  ins >> ws;
  getline(ins, Month, '/'); ins >> ws;
  getline(ins, Day, '/'); ins >> ws;
  getline(ins, Year); ins >> ws;
  month = atoi(Month.c_str());
  day = atoi(Day.c_str());
  year = atoi(Year.c_str());
}

// Writes out date in mm/dd/yyyy format. Will include leading zeroes.
void Date::WriteOut(ostream & outs) const
{
  outs << Month << '/' << Day << '/' << Year;
}

// Writes out date in mm/dd/yyyy format. Will include leading zeroes.
void Date::WriteOutNum(ostream & outs, bool num) const
{ // make these into one WriteOut function and determine whether it's int or string by bool num
  // change all Date calls to WriteOut to account for this
  // Have this function check and add leading zeros if month, day, year are less than or = 9
  outs << month << '/' << day << '/' << year;
}
 
bool Date::IsNull ()
{
  if (month == 0 && day == 0)
    return true;
  return false;
}
