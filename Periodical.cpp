// File: Periodical.cpp
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the implementation of a class called Periodical

#include "Periodical.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Member.h"
#include "Asset.h"
#include "Library.h"
#include "Date.h"

using namespace std;

// The default constructor creates a new periodical object 
Periodical :: Periodical ()
{  
  I.Volume = I.Number = I.CheckedOutByStr = "";
  ISSN = NumIssues = Name = ID = "";
  LType = PERIODICAL;
}

// This constructor will create a new periodical object identical to the passed periodical object
Periodical :: Periodical (const Periodical & S)
{
  LType = PERIODICAL;
  AType = S.AType;
  I.Volume = S.I.Volume;
  I.Number = S.I.Number;
  ISSN = S.ISSN;
  NumIssues = S.NumIssues;
  Name = S.Name;
  ID = S.ID;
  I.PubDate = S.I.PubDate;
  I.CheckedOut = S.I.CheckedOut;
  I.CheckedOutByStr = S.I.CheckedOutByStr;
  Issues = S.Issues;
}

// This destructor currently does nothing
Periodical :: ~Periodical ()
{}

// This assignment operator will copy one object to another of the same type
Periodical & Periodical ::  operator = (const Periodical & S)
{
  LType = PERIODICAL;
  AType = S.AType;
  I.Volume = S.I.Volume;
  I.Number = S.I.Number;
  ISSN = S.ISSN;	
  NumIssues = S.NumIssues;
  Name = S.Name;
  ID = S.ID;
  I.PubDate = S.I.PubDate;
  I.CheckedOut = S.I.CheckedOut;
  I.CheckedOutByStr = S.I.CheckedOutByStr;
  Issues = S.Issues;
}

// The IsA function will return the appropriate LibType value
Library :: LibType Periodical :: IsA () const
{
  return PERIODICAL;
}

//
string Periodical :: GetID () const
{
  return ID;
}

//
string Periodical :: GetName () const
{
  return Name;
}

//
vector <Library*> Periodical :: GetCheckedOutBy () 
{
  for (int i = 0; i < Issues.size(); i++)
    CheckedOutByVec.push_back(Issues[i].CheckedOutBy);
  return CheckedOutByVec;
}

//
vector <string> Periodical :: GetCheckedOutByStr () 
{
  for (int i = 0; i < Issues.size(); i++)
    CheckedOutByStrVec.push_back(Issues[i].CheckedOutByStr);
  return CheckedOutByStrVec;
}

//
/*void Periodical :: Library :: Issue :: SetCheckedOutIssue (Date & D)
{
  CheckedOut = D;
  }*/


//
int Periodical :: DaysOverdue (Date today)
{
  int NumDaysOverdue;
  if (I.CheckedOut.IsNull())
    return 0;
  NumDaysOverdue = (today - I.CheckedOut) - 7;
  return NumDaysOverdue;
}


//
void Periodical :: CheckoutLink (vector <Library *> vB, vector <Library *> vP) //const 
{
  for (int j = 0; j < vB.size(); j++)
    for (int k = 0; k < Issues.size(); k++)
      if (vB[j] != NULL && Issues[k].CheckedOutByStr == vB[j]->GetID())
	{
	  Library *m = vB[j]; // Member *m = vB[j];
	  Issues[k].CheckedOutBy = m;
	  break;
	}
}

//
void Periodical :: Checkout (vector <Library *> V, string str, int count) //const
{
  I.CheckedOutByStr = str;
  I.CheckedOutBy = V[count];
} 

//
void Periodical :: Return (vector <Library *> V, string str, int count)     
{                                                            
  I.CheckedOutByStr = "NONE";                                    
  I.CheckedOutBy = NULL;                                     
}

// This function reads in a periodical object from a standard formatted file.
void Periodical :: ReadIn (istream & input)
{
  string line;
  int issues;
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
    if (line == "ISSN:")
      {
	getline(input, line);
	line.erase(line.begin());
	ISSN = line;
      }
    if (line == "Issues:")
      {
	getline(input, line);
	line.erase(line.begin());
        NumIssues = line;
	issues = atoi(line.c_str());
	break;
      }
    }
  for (int i = 0; i < issues; i++)
    {
      while(input >> line)
	{
	  if (line == "Volume:")
	    { 
	      input >> line;
	      I.Volume = line;
	    }
	  if (line == "Number:")
	    {
	      getline(input, line);
	      line.erase(line.begin());
	      I.Number = line;
	    }
	  if (line == "Publication_Date:")
	    {
	      I.PubDate.ReadIn(input);
	    }
	  if (line == "Checked_Out_On:")
	    {
	      I.CheckedOut.ReadIn(input);
	    }
	  if (line == "Checked_Out_By:")
	    {
	      getline(input, line);
	      line.erase(line.begin());
	      I.CheckedOutByStr = line;
	      break;
	      // Implement assignment to a Member*
	    }
	}
      Issues.push_back(I);
    }
  return;
}

// This function writes out a Periodical object in a standard format.
void Periodical :: WriteOut (ostream & output) const
{
  output << "Type: PERIODICAL" << endl;
  output << "Name: " << Name << endl;
  output << "ID: " << ID << endl;
  output << "Asset_Type: " << GetATypeAsString(AType) << endl;
  output << "ISSN: " << ISSN << endl;
  output << "Issues: " << NumIssues << endl;
  for (int i = 0; i < Issues.size(); i++)
    {
      output << "Volume: " << Issues[i].Volume << "\tNumber: " << Issues[i].Number << endl;
      output << "Publication_Date: "; Issues[i].PubDate.WriteOut(output); output  << endl;
      output << "Checked_Out_On: "; Issues[i].CheckedOut.WriteOut(output); output << endl;
      output << "Checked_Out_By: " << Issues[i].CheckedOutByStr << endl;
   }
  output << endl;
}

vector <Library::Issue> Periodical::GetIssues () 
{
  return Issues;
}

/*string Periodical :: GetVolume () const
{
  return I.Volume;
  }*/
