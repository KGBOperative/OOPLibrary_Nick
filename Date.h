#ifndef DATE_H
#define DATE_H

// File: Date.h
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the description of a class called Date

#include <iostream>

using namespace std;

class Date
{
    public:
        // The default constructor creates a new date object 
        Date ();

        // This constructor will create a new date object identical to the passed date object
        Date (const Date & D);

        // This destructor currently does nothing
        ~Date ();

        // Assignment Operator
        Date & operator = (const Date & D);

        //
        void SetMonth (int inMonth);

        //
        void SetDay (int inDay);

        //
        void SetYear (int inYear);

        //
        void SetMonthStr (string inMonth);

        //
        void SetDayStr (string inDay);

        //
        void SetYearStr (string inYear);

        //
        int GetMonth () const;

        //
        int GetDay () const;

        //
        int GetYear () const;

        //
        void ReadIn (istream & ins);

        //
        void WriteOut (ostream & outs) const;

        //
        void WriteOutNum (ostream & outs, bool num) const;

        //
        tm maketm(int year, int month, int day);

        //
        double operator - (const Date & D);

        //
        bool operator < (const Date & D) const;

        //
        bool operator > (const Date & D) const;

        //
        bool IsNull ();

    private:
        int month;
        int day;
        int year;
        string Month, Day, Year;
};

#endif
