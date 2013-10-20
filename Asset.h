#ifndef ASSET_H
#define ASSET_H

// File: Asset.h
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the description of a class called Asset

#include <iostream>
#include "Library.h"

using namespace std;

class Asset : public Library
{
    public:
        // Enumerated type for Asset Classification
        enum AssetType {SHORT, LITERARY, MYSTERY, SCIFI, SELFHELP, BIOGRAPHY, COOKING, SPORTS, OTHER};

        // The default constructor creates a new asset object 
        Asset ();

        // This constructor will create a new asset object identical to the passed asset object
        Asset (const Asset & S);

        // This destructor currently does nothing
        ~Asset ();

        // This assignment operator will copy one object to another of the same type
        Asset & operator = (const Asset & S);

        // The IsA function will return the appropriate LibType value
        virtual LibType IsA () const;

        //
        virtual void Checkout ();

        //
        virtual void Return ();

        //
        virtual void ReadIn (istream & input);

        //
        virtual void WriteOut (ostream & output);

        //
        AssetType GetAType (string S); 

        //
        string GetATypeAsString (AssetType S) const;

    protected:
        AssetType AType;

    private:
};

#endif
