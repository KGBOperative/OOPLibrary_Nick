// File: Library.cpp
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the implementation of a virtual class called Library

#include <iostream>
#include "Library.h"
#include "Date.h"

using namespace std;

// Hopefully not necessary...
enum LibType {LIBRARY, MEMBER, ASSET, BOOK, PERIODICAL};

// The default constructor creates a new library object 
Library::Library () 
{
    LType = LIBRARY;
    Name = ID = "";
}

// This constructor will create a new library object identical to the passed library object
Library::Library (const Library & S) 
{
    //Library L = S; // will need to do deep copy
}

// This destructor currently does nothing
Library::~Library () {}

// This assignment operator will copy one object to another of the same type
Library & Library::operator = (const Library & S) 
{
    //Library L = S; // will need to do deep copy
}

// The IsA function will return the appropriate LibType value
Library :: LibType Library :: IsA () const
{
    LibType temp = LIBRARY;
    return temp;
}

string Library :: GetID () const
{
    return ID;
}

string Library :: GetName () const
{
    return Name;
}


vector <Library*> Library :: GetCheckedOutBy () const
{
    vector <Library*> V;
    return V;
} 

vector <string> Library :: GetCheckedOutByStr () const
{
    vector <string> V;
    return V;
} 


//
void Library :: SetCheckedOut (Date & D)
{
    return;
}


int Library :: DaysOverdue (Date today)
{
    int NumDaysOverdue = 0;
    return NumDaysOverdue;
}


// The input operator will call the ReadIn function for the passed library object
istream & operator >> (istream & ins, const Library & S)
{
    //  S.ReadIn(ins);
    return ins;
}

// The ouput operator will call the WriteOut function for the passed library object
ostream & operator << (ostream & outs, const Library & S)
{
    //S.WriteOut (outs);
    return outs;
}

//
void Library :: CheckoutLink (vector <Library *> vB, vector <Library *> vP) 
{
    return;
}

void Library :: Checkout (vector <Library *> V, string str, int count) 
{
    return;
}

//
void Library :: Return (vector <Library *> V, string str, int count) 
{
    return;
}

//
void Library :: ReadIn (istream & input) {}

//
void Library :: WriteOut (ostream & output) const {}

//
vector <Library::Issue> Library::GetIssues() 
{
    return vector<Library::Issue>();
}

//
string Library :: GetPhone() 
{
    return "";
}

//
int Library :: Issue :: DaysOverdue(Date today)
{
    Date null;
    null.SetDay(0);
    null.SetMonth(0);
    null.SetYear(0);
    if (CheckedOut - null > 0) {
        int NumDaysOverdue;
        NumDaysOverdue = (today - CheckedOut) - 7;;
        return NumDaysOverdue;
    }
    return 0;
}
