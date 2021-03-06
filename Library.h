#ifndef LIBRARY_H
#define LIBRARY_H

// File: Library.h
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the description of a virtual class called Library

#include <iostream>
#include <vector>
#include "Date.h"
#define DEBUG false
#define debug if (DEBUG) cout

using namespace std;

class Library
{
    public:
        // Enumerated types for Library Objects
        enum LibType {LIBRARY, MEMBER, ASSET, BOOK, PERIODICAL};

        // The default constructor creates a new library object 
        Library ();

        // This constructor will create a new library object identical to the passed library object
        Library (const Library & S);

        // This destructor currently does nothing
        ~Library ();

        // This assignment operator will copy one object to another of the same type
        Library & operator = (const Library & S);

        // The IsA function will return the appropriate LibType value
        virtual LibType IsA () const;

        //
        virtual string GetID () const;

        // This mutator function sets the ID of the Library object
        virtual void SetID(string id);

        //
        virtual string GetName () const;

        //
        virtual vector<Library*> GetCheckedOutBy () const;

        //
        virtual vector<string> GetCheckedOutByStr () const;

        //
        virtual void SetCheckedOut (Date & D);

        //
        virtual int DaysOverdue (Date today);

        //
        bool operator == (Library L);

        // The input operator will call the ReadIn function for the passed library object
        friend istream & operator >> (istream & ins, const Library & S);

        // The ouput operator will call the WriteOut function for the passed library object
        friend ostream & operator << (ostream & outs, const Library & S);

        //
        virtual void CheckoutLink (Library * lib);

        //
        virtual void Checkout (Library * L, string str, int count);

        //
        virtual void Return (int count);

        //
        virtual void ReadIn (istream & input);

        //
        virtual void WriteOut (ostream & output) const;

        //
        virtual string GetPhone();

        //
        virtual vector <Library*> GetCheckedOutVec () const;

        //
        struct Issue
        {
            string Volume;
            string Number;
            Date PubDate;
            Date CheckedOut;
            Library * CheckedOutBy;
            string CheckedOutByStr;
            int DaysOverdue (Date today);
            void SetCheckedOutIssue (Date & D);
            string GetVolume () const;
        };

        //
        virtual vector<Issue> GetIssues();


    protected:
        LibType LType;
        string Name;
        string ID;
        Date D;

    private:

};

#endif
