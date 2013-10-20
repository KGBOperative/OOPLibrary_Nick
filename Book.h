#ifndef BOOK_H
#define BOOK_H

// File: Book.h
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the description of a class called Book

#include <iostream>
#include "Asset.h"
#include "Date.h"
#include "Library.h"
#include "Member.h"

using namespace std;

class Book : public Asset
{
    public:
        // Enumerated type for Book Classification
        enum BookType {FICTION, NONFICTION};

        // The default constructor creates a new book object 
        Book ();

        // This constructor will create a new book object identical to the passed book object
        Book (const Book & S);

        // This destructor currently does nothing
        ~Book ();

        // This assignment operator will copy one object to another of the same type
        Book & operator = (const Book & S);

        // The IsA function will return the appropriate LibType value
        LibType IsA () const;

        //
        string GetID () const;

        //
        string GetName () const;

        //
        vector <Library*> GetCheckedOutBy () const;

        //
        vector <string> GetCheckedOutByStr () const;

        //
        int DaysOverdue (Date today);

        //
        void SetCheckedOut (Date & D);

        //
        void CheckoutLink (vector <Library *> vB, vector <Library *> vP); // const;

        //
        void Checkout (vector <Library *> V, string str, int count); // const;

        //
        void Return (vector <Library *> V, string str, int count);

        //
        void ReadIn (istream & input);

        //
        void WriteOut (ostream & output) const;

        // 
        BookType GetBType (string S);

        // 
        string GetBTypeAsString (Book :: BookType) const;

    private:
        string Author;
        string ISBN;
        BookType BType;
        Date CheckedOut;
        string CheckedOutByStr;
        Library * CheckedOutBy;
};

#endif
