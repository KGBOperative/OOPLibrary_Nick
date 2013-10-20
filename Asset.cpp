// File: Asset.cpp
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the implementation of a class called Asset

#include <iostream>
#include "Asset.h"
#include "Library.h"

using namespace std;

// The default constructor creates a new asset object 
Asset :: Asset ()
{
    AType = OTHER;
} 

// This constructor will create a new asset object identical to the passed asset object
Asset :: Asset (const Asset & S)
{
    AType = S.AType;
}

// This destructor currently does nothing
Asset :: ~Asset ()
{}

// This assignment operator will copy one object to another of the same type
Asset & Asset ::  operator = (const Asset & S)
{
    AType = S.AType;
}

// The IsA function will return the appropriate LibType value
Library :: LibType Asset ::  IsA () const
{
    return ASSET;
}

//
void  Asset ::Checkout ()
{}

//
void Asset ::Return ()
{}

// Nothing to read in, handled by child functions.
void Asset :: ReadIn (istream & input)
{}

// Nothing to write out, handled by child functions.
void Asset :: WriteOut (ostream & output)
{}

// Converts string Asset Types into actual Asset Types
Asset :: AssetType Asset :: GetAType (string S)
{
    if (S == "SHORT")
        return SHORT;
    if (S == "LITERARY")
        return LITERARY;
    if (S == "MYSTERY")
        return MYSTERY;
    if (S == "SCIFI")
        return SCIFI;
    if (S == "SELFHELP")
        return SELFHELP;
    if (S == "BIOGRAPHY")
        return BIOGRAPHY;
    if (S == "COOKING")
        return COOKING;
    if (S == "SPORTS")
        return SPORTS;
    if (S == "OTHER")
        return OTHER;
}

// Converts asset types to strings.
string Asset :: GetATypeAsString (AssetType S) const
{
    if (S == SHORT)
        return "SHORT";
    if (S == LITERARY)
        return "LITERARY";
    if (S == MYSTERY)
        return "MYSTERY";
    if (S == SCIFI)
        return "SCIFI";
    if (S == SELFHELP)
        return "SELFHELP";
    if (S == BIOGRAPHY)
        return "BIOGRAPHY";
    if (S == COOKING)
        return "COOKING";
    if (S == SPORTS)
        return "SPORTS";
    if (S == OTHER)
        return "OTHER";
}
