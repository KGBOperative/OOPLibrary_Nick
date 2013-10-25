// File: Library.cpp
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the implementation of a virtual class called Library

#include <iostream>
#include "Library.h"
#include "Date.h"

using namespace std;

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
    return LIBRARY;
}

string Library :: GetID () const
{
    return ID;
}

void Library :: SetID(string id) {
    ID = id;
}

string Library :: GetName () const
{
    return Name;
}


vector <Library*> Library :: GetCheckedOutBy () const
{
    return vector <Library*>();
} 

vector <string> Library :: GetCheckedOutByStr () const
{
    return vector <string>();
} 


//
void Library :: SetCheckedOut (Date & D)
{
    return;
}

//
void Library :: Issue :: SetCheckedOutIssue (Date & D)
{
    return;
}

int Library :: DaysOverdue (Date today)
{
    return 0;
}

//
bool Library:: operator == (Library L)
{
    return ID == L.ID;
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
void Library :: CheckoutLink (Library * lib) 
{
}

void Library :: Checkout (Library * L, string str, int count) 
{
}

//
void Library :: Return (int count) 
{
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

vector <Library *> Library :: GetCheckedOutVec () const
{
    vector <Library *> V;
    return V;
}

string Library :: Issue :: GetVolume () const
{
    return "";
}


//
int Library :: Issue :: DaysOverdue(Date today)
{
    if (CheckedOut.IsNull())
        return 0;

    return (today - CheckedOut) - 7;
}


