// File: Member.cpp
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the implementation of a class called Member

#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <cstring>
#include <sstream>
#include "stdio.h"
#include <cstdlib>
#include "Member.h"
#include "Library.h"
#include "Periodical.h"
#include "Book.h"
#include "Date.h"

using namespace std;

class Asset;

// The default constructor creates a new member object 
Member :: Member ()
{
    LType = MEMBER;
    CheckedOut.clear();
    CheckedOutStr.clear();
    Name = Address = City = State = Zip = PhoneNumber = "";
    ID = 200; // random very large number, so as not to overwrite early entries
}

// This constructor will create a new member object identical to the passed member object
Member :: Member (const Member & S) 
{
    LType = MEMBER;
    for (int i = 0; i < S.CheckedOut.size(); i++)
        CheckedOut.push_back(S.CheckedOut[i]);
    for (int i = 0; i < S.CheckedOutStr.size(); i++)
        CheckedOutStr.push_back(S.CheckedOutStr[i]);
    Name = S.Name;
    Address = S.Address;
    City = S.City;
    State = S.State;
    Zip = S.Zip;
    PhoneNumber = S.PhoneNumber;
    ID = S.ID;
}

// This destructor currently does nothing
Member :: ~Member () {}

// This assignment operator will copy one object to another of the same type
Member & Member :: operator = (const Member & S)
{
    LType = MEMBER;
    for (int i = 0; i < CheckedOut.size(); i++)
        CheckedOut.push_back(S.CheckedOut[i]);
    for (int i = 0; i < S.CheckedOutStr.size(); i++)
        CheckedOutStr.push_back(S.CheckedOutStr[i]);
    Name = S.Name;
    Address = S.Address;
    City = S.City;
    State = S.State;
    Zip = S.Zip;
    PhoneNumber = S.PhoneNumber;
    ID = S.ID;
}

// The IsA function will return the appropriate LibType value
Library :: LibType Member :: IsA () const
{
    return MEMBER;
}

//
void Member :: CheckoutLink (Library * asset) //const
{
    for (int i = 0; i < CheckedOutStr.size(); i++) {
        if (CheckedOutStr[i] == asset->GetID()) {
            CheckedOut.push_back(asset);
            break;
        }
    }
}

//
void Member :: Checkout (Library *V, string str, int count) //const
{
    CheckedOutStr.push_back(str);
    CheckedOut.push_back(V);
}

//
void Member :: Return (int count) 
{
    CheckedOutStr.erase(CheckedOutStr.begin()+count);
    CheckedOut.erase(CheckedOut.begin()+count);
}

string Member :: GetName () const
{
    return Name;
}

string Member :: GetID () const
{
    return ID;
}

bool Member :: RemoveCard (string check) 
{
    /*string forget;
    locale loc;
      for (int i = 0; i < Name.length(); i++)
      {
      forget = tolower(Name[i], loc);*/
    //forget = Name;
    if (Name == check)
        return true;
    else
        return false;    
    //}
}

//
void Member ::ReadIn (istream & input) //, vector <Library> & L) 
{

    string line;
    while (input >> line)
    {
        if (line == "Type:")
        {
            getline(input, line);
            line.erase(line.begin());
            if (line != "MEMBER")
                return;
        }
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
        if (line == "Address:") 
        {
            getline(input, line);
            line.erase(line.begin());
            Address = line;
        }
        if (line == "City:") 
        {
            getline(input, line);
            line.erase(line.begin());
            City = line;
        }
        if (line == "State:") 
        {
            getline(input, line);
            line.erase(line.begin());
            State = line;
        }
        if (line == "Zip:") 
        {
            getline(input, line);
            line.erase(line.begin());
            Zip = line;
        }
        if (line == "Phone_Number:") 
        {
            getline(input, line);
            line.erase(line.begin());
            PhoneNumber = line;
        }
        if (line == "Checked_Out:") 
        {
            string number, asset, line;
            istringstream strline;
            int count;
            getline(input, line);
            line.erase(line.begin());
            strline.str (line);
            strline >> number;
            count = atoi(number.c_str());
            for (int i = 0; i < count; i++) 
            {
                strline >> asset;
                CheckedOutStr.push_back(asset);
            }
            // split line into invidual asset ids
            // push asset ids into vector named Checked_Out
            return;

        }
        /*
           else if (*line.c_str() == '\n')
           {
           cout << "Break" << line << endl;
           break;	
           }
         */
    }
}

//
void Member:: WriteOut (ostream & output) const
{
    output << "Type: MEMBER" << endl;
    output << "Name: " << Name << endl;
    output << "ID: " << ID << endl;
    output << "Address: " << Address << endl;
    output << "City: " << City << endl;
    output << "State: " << State << endl;
    output << "Zip: " << Zip << endl;
    output << "Phone_Number: " << PhoneNumber << endl;
    output << "Checked_Out: " << CheckedOutStr.size();
    for (int i = 0; i < CheckedOutStr.size(); i++)
        output << "\t" << CheckedOutStr[i];
    output << endl << endl;
}

//
vector <Library *> Member :: GetCheckedOutVec () const
{
    return CheckedOut;
}

// 
string Member:: GetPhone ()
{
    return PhoneNumber;
}
