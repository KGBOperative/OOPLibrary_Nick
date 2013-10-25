#ifndef PERIODICAL_H
#define PERIODICAL_H

// File: Periodical.h
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the description of a class called Periodical

#include <iostream>
#include <vector>
#include "Asset.h"
#include "Date.h"
#include "Library.h"
#include "Member.h"

using namespace std;

class Periodical : public Asset
{
 public:
  // Enumerated type for Periodical Classification
  enum PeriodicalType {FICTION, NONFICTION};
  
  // The default constructor creates a new periodical object 
  Periodical ();
  
  // This constructor will create a new periodical object identical to the passed periodical object
  Periodical (const Periodical & S);
  
  // This destructor currently does nothing
  ~Periodical ();
  
  // This assignment operator will copy one object to another of the same type
  Periodical & operator = (const Periodical & S);
  
  // The IsA function will return the appropriate LibType value
  LibType IsA () const;

  //
  string GetID () const;

  //
  string GetName () const;

  //
  vector <Library*> GetCheckedOutBy () ;

  //
  vector <string> GetCheckedOutByStr () ;
  
  //
  //void SetCheckedOutIssue (Date & D);

  //
  int DaysOverdue (Date today);

  //
  void CheckoutLink (vector <Library *> vB, vector <Library *> vP); //const;

  //
  void Checkout (vector <Library *> V, string str, int count); //const;
  
  //
  void Return (vector <Library *> V, string str, int count);
  
  // This function will read in a Periodical object in a standard formatted file. 
  void ReadIn (istream & input);
  
  // This function eill write out a Periodical object in a standard format. 
  void WriteOut (ostream & output) const;

  //
  vector <Library::Issue> GetIssues ();
  
  //
  //string GetVolume () const;

  
 private:
  Issue I;
  vector <Library*> CheckedOutByVec;
  vector <string> CheckedOutByStrVec;
  string NumIssues;
  string ISSN;
  vector <Issue> Issues;
};

#endif
