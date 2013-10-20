// File: Main.cpp
// Authors: Alex Bretow, Nick Mahnke, Jonah Cohen
// Contents: This file contains the description of a class called Member

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "stdio.h"
#include "ctype.h"
#include <ctime>
#include <locale>
#include "Member.h"
#include "Library.h"
#include "Book.h"
#include "Periodical.h"
#include "Date.h"
#include "Asset.h"
#include <algorithm>
#include <iomanip>

using namespace std;

vector <Library *> vM; //
vector <Library *> vB; //
vector <Library *> vP; //

vector <Library *> vL; //
vector <Library *> AssetsOverdue; //
vector <Library *> MembersOverdue; //

int Menu();
void RestoreLibrary();
void SaveLibrary();
void AddCard();
void RemoveCard();
void AddAsset();
void RemoveAsset();
void CheckoutAsset();
void ReturnAsset();
void GenerateReport();
void Quit();
Date GetCurrentDate();
int ReportSubmenu();
void ReportMembersOverdue();
void ReportOverdueAssets();
void ReportAreaCode();
void DaysOverdueSort (vector <Library*> L);
bool CompareOverdueAssets (Library* A, Library* B);


int main ()
{ 
  int choice = Menu();
  while (choice == -1)
    choice = Menu();
  switch (choice)
    {
    case 1: RestoreLibrary(); main(); break;
    case 2: SaveLibrary(); main(); break;
    case 3: AddCard(); main(); break;
    case 4: RemoveCard(); main(); break;
    case 5: AddAsset(); main(); break;
    case 6: RemoveAsset(); main(); break;
    case 7: CheckoutAsset(); main(); break;
    case 8: ReturnAsset(); main(); break;
    case 9: GenerateReport(); main(); break;
    case 0: Quit(); break;
    }
  return 0;
}

int Menu ()
{
  char selection;
  cout << "---------------------------------------------------\n";
  cout << "Select one of the following options: " << endl << endl;
  cout << "\t1. Restore Library Information from a File\n";
  cout << "\t2. Save Library Information to a File\n";
  cout << "\t3. Add Library Card Holder\n";
  cout << "\t4. Remove Library Card Holder\n";
  cout << "\t5. Add New Library Asset\n";
  cout << "\t6. Remove Library Asset\n";
  cout << "\t7. Card Holder Checkout Asset\n";
  cout << "\t8. Card Holder Return Asset\n";
  cout << "\t9. Generate Reports\n";
  cout << "\t0. Quit\n";
  
  cin >> selection;
  string forget;
  getline (cin, forget);
  
  if (selection == '1' || selection == 'a' || selection == 'A')
    return 1;
  if (selection == '2' || selection == 'b' || selection == 'B')
    return 2;
  if (selection == '3' || selection == 'c' || selection == 'C')
    return 3;
  if (selection == '4' || selection == 'd' || selection == 'D')
    return 4;
  if (selection == '5' || selection == 'e' || selection == 'E')
    return 5;
  if (selection == '6' || selection == 'f' || selection == 'F')
    return 6;
  if (selection == '7' || selection == 'g' || selection == 'G')
    return 7;
  if (selection == '8' || selection == 'h' || selection == 'H')
    return 8;
  if (selection == '9' || selection == 'i' || selection == 'I')
    return 9;
  if (selection == '0' || selection == 'q' || selection == 'Q')
    return 0;
  else 
    cout << "Input out of range. Please try again\n";
  return -1;
}

void RestoreLibrary ( )
{
  string fname;
  cout << "Enter the name of the File you want to restore: ";
  cin >> fname;
  ifstream fin;
  fin.open(fname.c_str(), ifstream::in);
  
  if (fin.fail())
    {
      cerr << "File: " << fname << " not found " << endl;
      //exit (1);
      return;
      
      string choice = "";
    }
  
  string line;
  while (fin >> line)
    {
      if (line == "Type:")
	{
	  getline(fin, line);
	  line.erase(line.begin());
	}
      if (line == "MEMBER")
	{
	  Member *M = new Member(); //= new Member(); //
	  M->ReadIn(fin); //, vL);
	  vM.push_back(M); // 
	  vL.push_back(M);
	}
      else if (line == "BOOK")
	{
	  Book *B = new Book(); // = new Book(); // 
	  B->ReadIn(fin);
	  vB.push_back(B); // 
	  vL.push_back(B); // 
	}
      else if (line == "PERIODICAL")
	{
	  Periodical *P = new Periodical(); // = new Periodical(); //
 	  P->ReadIn(fin);
	  vP.push_back(P); //
	  vL.push_back(P); // 
	}
    }
  // will have to do for entire vector <Library *> vL
  for (int i = 0; i < vM.size(); i++)
    {
      vM[i]->CheckoutLink(vB, vP); 
      /*for (int j = 0; j < vB.size(); j++)
	
	for (int k = 0; k < vM[i]->CheckedOutStr.size(); k++)
	  if (vM[i]->CheckedOutStr[k] == vB[j]->GetID())
	    {
	      Book *b = vB[j];
	      vM[i]->CheckedOut.push_back(b);
	    }
      for (int j = 0; j < vP.size(); j++)
	for (int k = 0; k < vM[i]->CheckedOutStr.size(); k++)
	  if (vM[i]->CheckedOutStr[k] == vP[j]->GetID())
	    {
	      Periodical *p = vP[j];
	      vM[i]->CheckedOut.push_back(p);
	      }*/
    }
  for (int i = 0; i < vB.size(); i++)
    {
      vB[i]->CheckoutLink(vM, vB);
      /*for (int j = 0; j < vM.size(); j++)
	//for (int k = 0; k < vM[i].CheckedOutStr.size(); k++)
	if (vB[i]->CheckedOutByStr == vM[j]->GetID())
	    {
	      Member *m = vM[j];
	      vB[i]->CheckedOutBy = m;
	      }*/
    }
  for (int i = 0; i < vP.size(); i++)
    {
      vP[i]->CheckoutLink(vM, vP);
      /*for (int j = 0; j < vM.size(); j++)
	for (int k = 0; k < vP[i].Issues.size(); k++)
	  if (vP[i]->Issues[k]->CheckedOutByStr == vM[j]->GetID())
	    {
	      Member *m = vM[j];
	      vP[i]->Issues[k]->CheckedOutBy = m;
	      }*/
    }
}

void SaveLibrary()
{
  string fname;
  cout << "Enter the name of the File you want to save to: ";
  cin >> fname;
  string filename = fname + ".lib";
  ofstream fout (filename.c_str());
  for (int i = 0; i < vM.size(); i++)
    vM[i]->WriteOut(fout);
  for (int i = 0; i < vB.size(); i++)
    vB[i]->WriteOut(fout);
  for (int i = 0; i < vP.size(); i++)
    vP[i]->WriteOut(fout);
  //P.WriteOut(fout);
  
}
  
void AddCard()
{
  string fname, choice, temp, endLineClear;
  stringstream Ins;
  cout << "Would you like to add from a file (1) or manually (2)? ";
  cin >> choice;
  if (choice == "1" || choice == "file" || choice == "File" || choice == "FILE") {
    cout << "Enter the name of the File you want to add: ";
    cin >> fname;
    ifstream fin;
    fin.open(fname.c_str(), ifstream::in);
    
    if (fin.fail())
      {
	cerr << "File: " << fname << " not found " << endl;
	//exit (1);
	
	string choice = "";
      }
    
    string line;
    while (fin >> line)
      {
	if (line == "Type:")
	{
	  getline(fin, line);
	  line.erase(line.begin());
	}
	if (line != "MEMBER")
	  {
	    cerr << "File: " << fname << " is not a Card Holder " << endl;
	    break;
	    //exit (1);
	  }
	else 
	{
	  Member *M = new Member(); //= new Member(); //
	  M->ReadIn(fin); //, vL);
	  vM.push_back(M); // 
	  vL.push_back(M); // 
	}
      }
  }
  else if (choice == "2" || choice == "manually" || choice == "Manually" || choice == "MANUALLY" || choice == "manual" || choice == "Manual" || choice == "MANUAL") {
    getline (cin, endLineClear);
    
    cout << "Name: ";
    getline(cin, temp);
    Ins << "Name: " + temp + "\n";
    temp.clear();
    
    cout << "ID: ";
    getline(cin, temp);
    Ins << "ID: " + temp + "\n";
    temp.clear();

    cout << "Address: ";
    getline(cin, temp);
    Ins << "Address: " + temp + "\n";
    temp.clear();

    cout << "City: ";
    getline(cin, temp);
    Ins << "City: " + temp + "\n";
    temp.clear();

    cout << "State: ";
    getline(cin, temp);
    Ins << "State: " + temp + "\n";
    temp.clear();

    cout << "Zip: ";
    getline(cin, temp);
    Ins << "Zip: " + temp + "\n";
    temp.clear();

    cout << "Phone Number: ";
    getline(cin, temp);
    Ins << "Phone_Number: " + temp + "\n";
    temp.clear();

    cout << "Checked Out (Asset ID): ";
    getline(cin, temp);
    Ins << "Checked_Out: " + temp + "\n";
    temp.clear();

    Member *M = new Member();
    M->ReadIn(Ins);
    vM.push_back(M);
    vL.push_back(M);
  }
  else {
    cout << "That was not an option. Please try again. ";
    AddCard();
  }
}

void RemoveCard()
{
  string forget;
  string remove;
  string check = "";
  /*for (int i = 0; i < vM.size(); i++)
    {
      cout << "Name: " << vM[i]->GetName() << "\tID: " << vM[i]->GetID() << endl;
      }*/
  cout << "Enter the ID of the Card you want to remove: ";
  getline (cin, check); //remove;
  cout << check;
  /*locale loc;
  for (int i = 0; i < remove.length(); i++)
  check = tolower(remove[i], loc);*/
  if (check.at(0) == 'M')
    {
      for (int i = 0; i < vM.size(); i++) {
	if (vM[i]->GetID() == check) {
	  vM.erase (vM.begin()+i);
	}
	  //cout << vM[i]->GetName();
      }
    }
  else
    cout << "That Member ID does not exist. \n";
  /*if (putchar (tolower(vM[i].Name.c_str())) == putchar (tolower(remove.c_str())))
    vM.erase (vM.begin()+i);*/
}

void AddAsset()
{
  string fname, choice, temp, endLineClear;
  stringstream Ins;
  cout << "Would you like to add from a file (1) or manually (2)? ";
  cin >> choice;
  if (choice == "1" || choice == "file" || choice == "File" || choice == "FILE") {
    cout << "\nEnter the name of the File you want to add: ";
    cin >> fname;
    ifstream fin;
    fin.open(fname.c_str(), ifstream::in);
    
    if (fin.fail())
      {
	cerr << "File: " << fname << " not found " << endl;
	//exit (1);
      
	string choice = "";
      }
    
    string line;
    while (fin >> line)
      {
	if (line == "Type:")
	{
	  getline(fin, line);
	  line.erase(line.begin());
	}
	if (line != "BOOK" && line != "PERIODICAL")
	  {
	    cerr << "File: " << fname << " is not an Asset" << endl;
	    break;
	    //exit (1);
	  }
	else if (line == "BOOK")
	  {
	    Book *B = new Book(); // = new Book(); // 
	    B->ReadIn(fin);
	    vB.push_back(B); // 
	    vL.push_back(B); // 
	  }
	else if (line == "PERIODICAL")
	  {
	    Periodical *P = new Periodical(); // = new Periodical(); //
	    P->ReadIn(fin);
	    vP.push_back(P); //
	    vL.push_back(P); // 
	  }
      }
  }
  else if (choice == "2" || choice == "manually" || choice == "Manually" || choice == "MANUALLY" || choice == "manual" || choice == "Manual" || choice == "MANUAL") {
    //getline (cin, endLineClear);
    cout << "\nBook (1) or Periodical (2): ";
    temp.clear();
    cin >> temp;
    if (temp == "1" || temp == "book" || temp == "Book" || temp == "BOOK") 
      {
	getline (cin, endLineClear);
	
	cout << "Name: ";
	getline(cin, temp);
	Ins << "Name: " + temp + "\n";
	temp.clear();
	
	cout << "ID: ";
	getline(cin, temp);
	Ins << "ID: " + temp + "\n";
	temp.clear();
	
	cout << "Asset Type: ";
	getline(cin, temp);
	Ins << "Asset_Type: " + temp + "\n";
	temp.clear();
	
	cout << "Author: ";
	getline(cin, temp);
	Ins << "Author: " + temp + "\n";
	temp.clear();

	cout << "ISBN: ";
	getline(cin, temp);
	Ins << "ISBN: " + temp + "\n";
	temp.clear();
	
	cout << "Type: ";
	getline(cin, temp);
	Ins << "Type: " + temp + "\n";
	temp.clear();
	
	cout << "Checked Out On (mm/dd/yyy): ";
	getline(cin, temp);
	Ins << "Checked_Out_On: " + temp + "\n";
	temp.clear();
	
	cout << "Checked Out By (Member ID): ";
	getline(cin, temp);
	Ins << "Checked_Out_By: " + temp + "\n";
	temp.clear();
	
	Book *B = new Book();
	B->ReadIn(Ins);
	vB.push_back(B);
	vL.push_back(B);
      }
    else if (temp == "2" || temp == "periodical" || temp == "Periodical" || temp == "PERIODICAL") 
      {
	int issues;
	getline (cin, endLineClear);
	
	cout << "Name: ";
	getline(cin, temp);
	Ins << "Name: " + temp + "\n";
	temp.clear();
	
	cout << "ID: ";
	getline(cin, temp);
	Ins << "ID: " + temp + "\n";
	temp.clear();
	
	cout << "Asset Type: ";
	getline(cin, temp);
	Ins << "Asset_Type: " + temp + "\n";
	temp.clear();
	
	cout << "ISSN: ";
	getline(cin, temp);
	Ins << "ISSN: " + temp + "\n";
	temp.clear();

	cout << "Issues: ";
	getline(cin, temp);
	Ins << "Issues: " + temp + "\n";
	issues = atoi(temp.c_str());
	temp.clear();

	for (int i = 0; i < issues; i++) 
	  {
	    cout << "Volume: ";
	    getline(cin, temp);
	    Ins << "Volume: " + temp + "\t\t";
	    temp.clear();
	    
	    cout << "Number: ";
	    getline(cin, temp);
	    Ins << "Number: " + temp + "\n";
	    temp.clear();

	    cout << "Publication Date (mm/dd/yyy): ";
	    getline(cin, temp);
	    Ins << "Publication_Date: " + temp + "\n";
	    temp.clear();

	    cout << "Checked Out On (mm/dd/yyy): ";
	    getline(cin, temp);
	    Ins << "Checked_Out_On: " + temp + "\n";
	    temp.clear();
	    
	    cout << "Checked Out By (Member ID): ";
	    getline(cin, temp);
	    Ins << "Checked_Out_By: " + temp + "\n";
	    temp.clear();
	  }
	
	Periodical *P = new Periodical();
	P->ReadIn(Ins);
	vP.push_back(P);
	vL.push_back(P);
      }
  }
  else {
    cout << "That was not an option. Please try again. ";
    AddAsset();
  }
}

void RemoveAsset()
{
  /*string check = "";
    cout << "Enter the name of the Asset you want to remove: ";
    getline (cin, check); //remove;
    for (int i = 0; i < vB.size(); i++) {
    if (vB[i].RemoveCard(check))
      vB.erase (vB.begin()+i);
  }
  for (int i = 0; i < vP.size(); i++) {
    if (vP[i].RemoveCard(check))
      vP.erase (vP.begin()+i);
      }*/ // create bool RemoveCard functions for Book and Periodical <-- Ultimately do on vector <Library> vL
  string check = "";
  string choice = "";
  //cout << "Do you want to remove a Book (1) or Periodical (2)? ";
  //cin >> choice;
  //if (choice == "1" || choice == "book" || choice == "Book" || choice == "BOOK") {
  /*for (int i = 0; i < vB.size(); i++) {
    cout << "Name: " << vB[i]->GetName() << "\tID: " << vB[i]->GetID() << endl;
  }
  for (int i = 0; i < vP.size(); i++) {
    cout << "Name: " << vP[i]->GetName() << "\tID: " << vP[i]->GetID() << endl;
    }*/
  cout << "Enter the ID of the Asset you want to remove: ";
  getline (cin, check); //remove;
  //cout << check;
  /*locale loc;
    for (int i = 0; i < remove.length(); i++)
    check = tolower(remove[i], loc);*/
  if (check.at(0) == 'B') 
    {
      for (int i = 0; i < vB.size(); i++) {
	if (vB[i]->GetID() == check) {
	  vB.erase (vB.begin()+i);
	  //cout << vB[i]->GetName();
	}
      }
    }
  else if (check.at(0) == 'P')
    {
      for (int i = 0; i < vP.size(); i++) {
	if (vP[i]->GetID() == check) {
	  vP.erase (vP.begin()+i);
	}
      }
    }
  else
    cout << "That Asset ID does not exist. \n";
}
/*
Date GetCurrentDate ()
{
  time_t theTime = time(NULL);
  struct tm *aTime = localtime(&theTime);
  
  int cDay = aTime->tm_mday;
  int cMonth = aTime->tm_mon + 1;
  int cYear = aTime->tm_year + 1900;
  Date today = Date ();
  today.SetDay(cDay);
  today.SetMonth(cMonth);
  today.SetYear(cYear);
  //today.WriteOutNum(cout, 1);
  return today;
  }*/

Date GetCurrentDate ()
{
  time_t theTime;
  time (&theTime);
  struct tm *aTime = localtime(&theTime);
  char buffer [80];

  strftime (buffer, 80, "%m/%d/%Y", aTime);
  stringstream temp;
  temp.str(buffer);
 
  /*int cDay = aTime->tm_mday;
  int cMonth = aTime->tm_mon + 1;
  int cYear = aTime->tm_year + 1900;*/
  Date today;
  today.ReadIn(temp);
  //string today;
  /*today.SetDay(cDay);
  today.SetMonth(cMonth);
  today.SetYear(cYear);*/
  //strftime (buffer, 80, "%m/%d/%Y", aTime);
  //string temp =  buffer;
  //cout << today;
  //temp.WriteOutNum(cout, 1);
  //today.WriteOut(cout);
  return today;
}


void OverdueAssets (vector <Library *> vB, vector <Library *> vP)
{
  
  Date coDate;
  Date today = GetCurrentDate();
  vector <Library::Issue> issues;
  vector <Library*> COB;
  int NumDaysOverdue;
  for (int i = 0; i < vB.size(); i++)
    {
      // get this to work or use GetCheckedOut, find way to return Date or int
      NumDaysOverdue = vB[i]->DaysOverdue(today);
      if (NumDaysOverdue > 0) 
	{
	  Library *b = vB[i];
	  COB = vB[i]->GetCheckedOutBy();
	  Library *m = COB[0];//-> GetCheckedOutBy(); 
	  //cout << vB[i];//-> GetCheckedOutBy();
	  
	  AssetsOverdue.push_back(b);
	  MembersOverdue.push_back(m);
	}
      // push information to vector of Overdue Assets or print out Name, ID, DaysOverdue, and CheckedOutBy ID 
    }
  for (int i = 0; i < vP.size(); i++) 
    {
      issues = vP[i]->GetIssues();
      for (int j = 0; j < issues.size(); j++)
	{
	  NumDaysOverdue = issues[j].DaysOverdue(today); 
	  if (NumDaysOverdue > 0)
	    {
	      Library *p = vP[i];
	      Library *m = vP[i]->GetIssues()[j].CheckedOutBy; 
	      //cout << vP[i]-> GetCheckedOutBy(); 
	      AssetsOverdue.push_back(p);
	      MembersOverdue.push_back(m);
	    }
	}
      // push information to vector of Overdue Assets or print out Name, ID, DaysOverdue, and CheckedOutBy ID 
    }
  //  for (int i = 0; i < MembersOverdue.size(); i++)
  //MembersOverdue[i]->WriteOut(cout);
  
}

void CheckoutAsset()
{ // Needs to check if Asset is already checkedout, needs to check which issue for periodical, should print list of mems, assets
  string member, asset;
  bool found = false;
  Date today = GetCurrentDate();
  //string test = GetCurrentDateStr();
  //today.WriteOutNum(cout, 1);
  int memcount = 0;
  int assetcount = 0;
  cout << "Enter the ID of Member who is checking out an Asset: ";
  cin >> member;
  for (int i = 0; i < vM.size(); i++) {
    if (member == vM[i]->GetID()) {
      found = true;
      break;
    }
    memcount++;
  }
  if (found == false) {
    cout << "That Member ID does not exist. " << endl;
    return;
  }
  found = false;
  cout << "Enter the ID of the Asset: ";
  cin >> asset;
  for (int i = 0; i < vB.size(); i++) {
    if (asset == vB[i]->GetID()) {
      found = true;
      vM[memcount]->Checkout(vB, asset, assetcount);
      vB[assetcount]->Checkout(vM, member, memcount);
      vB[assetcount]->SetCheckedOut(today);
      break;
    }
    assetcount++;
  }
  if (found == false) {
    assetcount = 0;
    for (int i = 0; i < vP.size(); i++) {
      if (asset == vP[i]->GetID()) {
	found == true;
	vM[memcount]->Checkout(vP, asset, assetcount);
	vP[assetcount]->Checkout(vM, member, memcount);
	vP[assetcount]->SetCheckedOut(today);
	break;
      }
      assetcount++;
    }
  }
    if (found == false) {
      cout << "That Asset ID does not exist. " << endl;
      return;
    }
  // Create functions in classes and set CheckedOutStr to asset, vM[memcount]->CheckedOut push back pointer to vB[assetcount]
  // or vP[assetcount], vB or vP[assetcount]->CheckedOutByStr to member, vBor vP[assetcount]->CheckedOutBy push back
  // pointer to vM[memcount], setFunction vB or vP->CheckedOutOn to today
}

// reimplement each Classes checkout function to checkout one item, get pointer linking to work in Main.cpp

void ReturnAsset()
{
  string member, asset;
  bool found = false;
  Date ret = Date();
  //string test = GetCurrentDateStr();
  //today.WriteOutNum(cout, 1);
  int memcount = 0;
  int assetcount = 0;
  cout << "Enter the ID of Member who is checking out an Asset: ";
  cin >> member;
  for (int i = 0; i < vM.size(); i++) {
    if (member == vM[i]->GetID()) {
      found = true;
      break;
    }
    memcount++;
  }
  if (found == false) {
    cout << "That Member ID does not exist. " << endl;
    return;
  }
  found = false;
  cout << "Enter the ID of the Asset: ";
  cin >> asset;
  for (int i = 0; i < vB.size(); i++) {
    if (asset == vB[i]->GetID()) {
      found = true;
      vM[memcount]->Return(vB, asset, assetcount); // implement Return in each class to do opposite of Checkout
      vB[assetcount]->Return(vM, member, memcount); // check that asset is indeed checkedout by member
      vB[assetcount]->SetCheckedOut(ret);
      break;
    }
    assetcount++;
  }
  if (found == false) {
    assetcount = 0;
    for (int i = 0; i < vP.size(); i++) {
      if (asset == vP[i]->GetID()) {
	found == true;
	vM[memcount]->Return(vP, asset, assetcount);
	vP[assetcount]->Return(vM, member, memcount);
	vP[assetcount]->SetCheckedOut(ret);
	break;
      }
      assetcount++;
    }
  }
    if (found == false) {
      cout << "That Asset ID does not exist. " << endl;
      return;
      }
}

int ReportSubmenu()
{
  
  char selection;
  cout << "---------------------------------------------------\n";
  cout << "Select one of the following reports: " << endl << endl;
  cout << "\t1. Members with Overdue Assets\n";
  cout << "\t2. All Overdue Assets\n";
  cout << "\t3. Members in a Specific Area Code\n"; 
  cout << "\t0. Main Menu\n"; 
  
  cin >> selection;
  //string forget;
  //getline (cin, forget);
  
  if (selection == '1' || selection == 'a' || selection == 'A')
    return 1;
  if (selection == '2' || selection == 'b' || selection == 'B')
    return 2;
  if (selection == '3' || selection == 'c' || selection == 'C')
    return 3;
  if (selection == '0' || selection == 'm' || selection == 'M')
    return 0;
  else 
    return -1;

}

void GenerateReport()
{
  OverdueAssets(vB, vP);
  sort (AssetsOverdue.begin(), AssetsOverdue.end(), CompareOverdueAssets);  
  int choice = ReportSubmenu();
  while (choice == -1)
    choice = Menu();

    switch (choice)
    {
    case 1: ReportMembersOverdue(); GenerateReport(); break;
    case 2: ReportOverdueAssets(); GenerateReport(); break;
    case 3: ReportAreaCode(); GenerateReport(); break;
    case 0: main(); break;
    }
}

void ReportMembersOverdue()
{
  char choice;
  Date today = GetCurrentDate();
  cout << "Do you want your report in a file(1) or on the screen(2)? : ";
  cin >> choice;

  if (choice == '1')
    {
      string fname;
      cout << "Enter the name of the File you want to save to: ";
      cin >> fname;
      string filename = fname + ".report";
      ofstream fout (filename.c_str());
      
      fout << "Members with Overdue Assets \t\t Today's Date: ";
      today.WriteOut(fout);
      fout << endl << endl;
      for (int i = 0; i < MembersOverdue.size(); i++)
	{
	  //MembersOverdue[i]->WriteOut(fout);
	  fout << "\t" << "Assets Overdue Count: " << AssetsOverdue.size() << endl;
	  for (int j = 0; j < AssetsOverdue.size(); j++)
	    {
	      if (AssetsOverdue[j]->GetID() == MembersOverdue[i]->GetID())
		{
		  fout << "/t"  << AssetsOverdue[j]->GetID() << ": ";
		  fout << AssetsOverdue[j]->GetName() << "/t";
		  fout << "Days Overdue: " <<  AssetsOverdue[j]->DaysOverdue(today) << endl;
		}
	    }
	}
      
    }
  else if (choice == '2')
    {
      return;
    }
      
}

void ReportOverdueAssets()
{
  //OverdueAssets(vB, vP);
  DaysOverdueSort(AssetsOverdue);
  char choice;
  string type;
  Date today = GetCurrentDate();
  cout << "Do you want your report in a file(1) or on the screen(2)? : ";
  cin >> choice;

  if (choice == '1')
    {
      string fname;
      cout << "Enter the name of the File you want to save to: ";
      cin >> fname;
      string filename = fname + ".report";
      ofstream fout (filename.c_str());
      
      fout << "Overdue Assets \t\t Today's Date: ";
      today.WriteOut(fout);
      fout << endl << endl;
      for (int i = 0; i < AssetsOverdue.size(); i++)
	{
	  if (AssetsOverdue[i]->IsA() == Library::BOOK)
	    {
	      type = "BOOK";
	      fout << "Type: " << type << endl;
	      fout << "Asset Name: " << AssetsOverdue[i] -> GetName() << endl;
	      fout << "Days Overdue: " << AssetsOverdue[i] -> DaysOverdue(today) << endl;
	      fout << "ID: " << AssetsOverdue[i] -> GetID() << endl;
	      fout << "Name: " << AssetsOverdue[i] -> GetCheckedOutBy()[0] -> GetName() <<
		endl << endl;
	    }
	  else
	    {
	      type = "PERIODICAL";
	      vector <Library::Issue> issues;
	      for (int j = 0; j < AssetsOverdue[i]->GetIssues().size(); j++)
		{
		  issues = AssetsOverdue[i]->GetIssues();
		  if (issues[j].DaysOverdue(today) > 0 && issues[j].CheckedOutBy != NULL)
		    {
		      fout << "Type: " << type << endl;
		      fout << "Asset Name: " << AssetsOverdue[i] -> GetName() << endl;
		      fout << "Days Overdue: " << issues[j].DaysOverdue(today) << endl; 
		      fout << "ID: " << AssetsOverdue[i] -> GetID() << endl;
		      fout << "Name: " << issues[j].CheckedOutBy -> GetName() << endl << endl;
		    }
		}
	    }
	}
      fout << "Total: " << AssetsOverdue.size() << endl;
      fout << "Total Fees: $" << 13 * AssetsOverdue.size() << endl;
       	    
    }
  else if (choice == '2')
   {
     for (int i = 0; i < AssetsOverdue.size(); i++)
       {
	 if (AssetsOverdue[i]->IsA() == Library::BOOK)
	   {
	     type = "BOOK";
	     cout << "Type: " << type << endl;
	     cout << "Asset Name: " << AssetsOverdue[i] -> GetName() << endl;
	     cout << "Days Overdue: " << AssetsOverdue[i] -> DaysOverdue(today) << endl;
	     cout << "ID: " << AssetsOverdue[i] -> GetID() << endl;
	     cout << "Name: " << AssetsOverdue[i] -> GetCheckedOutBy()[0] -> GetName() <<
	       endl << endl;
	   }
	 else
	   {
	     type = "PERIODICAL";
	     vector <Library::Issue> issues;
	     for (int j = 0; j < AssetsOverdue[i]->GetIssues().size(); j++)
	       {
		 issues = AssetsOverdue[i]->GetIssues();
		 if (issues[j].DaysOverdue(today) > 0 && issues[j].CheckedOutBy != NULL)
		   {
		      cout << "Type: " << type << endl;
		      cout << "Asset Name: " << AssetsOverdue[i] -> GetName() << endl;
		      cout << "Days Overdue: " << issues[j].DaysOverdue(today) << endl; 
		      cout << "ID: " << AssetsOverdue[i] -> GetID() << endl;
		      cout << "Name: " << issues[j].CheckedOutBy -> GetName() << endl << endl;
		   }
	       }
	   }
       }
     cout << "Total: " << AssetsOverdue.size() << endl;
     cout << "Total Fees: $" << 13 * AssetsOverdue.size() << endl;     
   }
}


void ReportAreaCode()
{
  char choice;
  string type;
  Date today = GetCurrentDate();
  cout << "Do you want your report in a file(1) or on the screen(2)? : ";
  cin >> choice;

  if (choice == '1')
    {
      string fname;
      cout << "Enter the name of the File you want to save to: ";
      cin >> fname;
      string filename = fname + ".report";
      ofstream fout (filename.c_str());
      
      string areacode;
      cout << "What area code do you want to see? : " << endl;
      cin >> areacode;
      fout << "Members in " << areacode << endl;
      fout << "Generated on: ";
      today.WriteOut(fout);
      fout  << endl;
      fout << "---------------------------------------------------" << endl;
      fout << setw(6) << left << "ID" << setw(22) << left << "Name" << setw(14) << left 
	   << "Phone Number" << endl;
      for (int i = 0; i < vM.size(); i++)
	if (areacode == vM[i]->GetPhone().substr(0,3))
	  fout << setw(4) << left << vM[i]->GetID() << "  " << setw(20) 
	       << left << vM[i]->GetName() << "  " << setw(12) 
	       << left <<  vM[i]->GetPhone() << endl;
    }
  if (choice == '2')
    {
      string areacode;
      cout << "What area code do you want to see? : " << endl;
      cin >> areacode;
      cout << "Members in " << areacode << endl;
      cout << "Generated on: ";
      today.WriteOut(cout);
      cout << endl;
      cout << "---------------------------------------------------" << endl;
      cout << setw(6) << left << "ID" << setw(22) << "Name" << setw(14) << "Phone Number" << endl; 
      for (int i = 0; i < vM.size(); i++)
	if (areacode == vM[i]->GetPhone().substr(0,3))
	  cout << setw(4) << left << vM[i]->GetID() << "  " << setw(20) << vM[i]->GetName() 
	       << "  " << setw(12) << vM[i]->GetPhone() << endl;
    }
}

bool CompareOverdueAssets ( Library* A, Library* B)
{
  return (A->GetID() < B->GetID());
}

void Quit () 
{
  string choice;
  bool cont = true;
  while (cont == true) {
    cout << "Do you want to save changes made to Library (Y/N)? ";
    cin >> choice;
    if (choice == "y" || choice == "Y" || choice == "yes" || choice == "Yes" || choice == "YES")
      {
	SaveLibrary();
	cont = false;
      }
    else if (choice == "n" || choice == "N" || choice == "no" || choice == "No" || choice == "NO")
      {
	exit(0);
	cont = false;
      }
    else 
      cout << "Please enter Y or N ";
  }
}

void DaysOverdueSort (vector <Library*> L)
{
  Library* temp;
  Date today = GetCurrentDate();
  for (int i = 0; i < L.size()-1; i++)
      if (L[i]->DaysOverdue(today) < L[i+1]->DaysOverdue(today))
	{
	  temp = L[i];
	  L[i] = L[i+1];
	  L[i+1] = temp;
	}
}
