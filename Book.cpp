// File: Book.cpp
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the implementation of a class called Book

#include <iostream>
#include <vector>
#include <string>
#include "Book.h"
#include "Asset.h"
#include "Date.h"
#include "Library.h"
#include <cstdlib>

using namespace std;

// The default constructor creates a new book object 
Book :: Book ()
{
    LType = BOOK;
    BType = FICTION;
    Author = ISBN = Name = ID = CheckedOutByStr = "";
}

// This constructor will create a new book object identical to the passed book object
Book :: Book (const Book & S)
{
    LType = BOOK;
    BType = S.BType;
    Author = S.Author;
    ISBN = S.ISBN;
    Name = S.Name;
    ID = S.ID;
    CheckedOut = S.CheckedOut;
    CheckedOutByStr = S.CheckedOutByStr;
}

// This destructor currently does nothing
Book :: ~Book () {}

// This assignment operator will copy one object to another of the same type
Book & Book :: operator = (const Book & S)
{
    LType = BOOK;
    BType = S.BType;
    Author = S.Author;
    ISBN = S.ISBN;
    Name = S.Name;
    ID = S.ID;
    CheckedOut = S.CheckedOut;
    CheckedOutByStr = S.CheckedOutByStr;
}

// The IsA function will return the appropriate LibType value
Library :: LibType Book :: IsA () const
{
    return BOOK;
}

// 
string Book :: GetID () const
{
    return ID;
}

string Book :: GetName () const
{
    return Name;
}


vector <Library*> Book :: GetCheckedOutBy () const
{
    return vector<Library*>(1,CheckedOutBy);
}

vector <string> Book :: GetCheckedOutByStr () const
{
    return vector<string>(1, CheckedOutByStr);
}

int Book :: DaysOverdue (Date today)
{
    int NumDaysOverdue;
    if (CheckedOut.IsNull())
        return 0;
    NumDaysOverdue = (today - CheckedOut) - 21;
    return NumDaysOverdue;
}


void Book :: SetCheckedOut (Date & D)
{
    CheckedOut = D;
}

//
void Book :: CheckoutLink (Library * M) // const
{
    if (CheckedOutByStr == M->GetID()) {
        CheckedOutBy = M;
    }
}

//
void Book :: Checkout (vector <Library *> V, string str, int count) // const
{
    CheckedOutByStr = str;
    CheckedOutBy = V[count];
}

//
void Book :: Return (int count)                                                
{                                 
    CheckedOutByStr = "NONE";
    CheckedOutBy = NULL;
}

//
void Book ::ReadIn (istream & input)
{
    string line;
    while (input >> line)
    {
        if (line == "Name:")
        {
            getline(input, line);
            line.erase(line.begin());
            Name = line;
        }
        if (line == "ID:")
        {
            getline(input, line);
            line.erase(line.begin());
            ID = line;
        }
        if (line == "Asset_Type:")
        {
            getline(input, line);
            line.erase(line.begin());
            AType = GetAType(line);
        }
        if (line == "Author:")
        {
            getline(input, line);
            line.erase(line.begin());
            Author = line;
        }
        if (line == "ISBN:")
        {
            getline(input, line);
            line.erase(line.begin());
            ISBN = line;
        }
        if (line == "Type:")
        {
            getline(input, line);
            line.erase(line.begin());
            BType = GetBType(line);
        }
        if (line == "Checked_Out_On:")
        {
            CheckedOut.ReadIn(input);
        }
        if (line == "Checked_Out_By:")
        {
            getline(input, line);
            line.erase(line.begin());
            //cout << line;
            CheckedOutByStr = line;
            //cout << CheckedOutBy;
            // Implement assignment to Member*
            return;
        }
    }
}
//
void Book ::WriteOut (ostream & output) const
{
    output << "Type: BOOK" << endl;
    output << "Name: " << Name << endl;
    output << "ID: " << ID << endl;
    output << "Asset_Type: " << GetATypeAsString(AType) << endl; 
    output << "Author: " << Author << endl;
    output << "ISBN: " << ISBN << endl;
    output << "Type: " << GetBTypeAsString(BType) << endl; 
    output << "Checked_Out_On: "; CheckedOut.WriteOut(output); output << endl;
    output << "Checked_Out_By: " << CheckedOutByStr << endl << endl;
}

Book :: BookType Book :: GetBType (string S)
{
    if (S == "FICTION")
        return FICTION;
    if (S == "NONFICTION")
        return NONFICTION;
} 

string Book :: GetBTypeAsString (BookType S) const
{
    if (S == FICTION)
        return "FICTION";
    if (S == NONFICTION)
        return "NONFICTION";
}




