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

vector <Library *> vM;
vector <Library *> vB;
vector <Library *> vP;

vector <Library *> vL;
vector <Library *> AssetsOverdue;
vector <Library *> MembersOverdue;

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
bool isfound (vector <Library *> L, Library * Ptr);
void OverdueAssets (vector <Library *> vB, vector <Library *> vP);


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
            Member *M = new Member(); 
            M->ReadIn(fin);
            Library * l = M;
            if (!isfound(vM, l))
                vM.push_back(M);  
            vL.push_back(M);
        }
        else if (line == "BOOK")
        {
            Book *B = new Book(); 
            B->ReadIn(fin);
            Library * l = B;
            if (!isfound(vB, l))
                vB.push_back(B); 
            vL.push_back(B);  
        }
        else if (line == "PERIODICAL")
        {
            Periodical *P = new Periodical(); 
            P->ReadIn(fin);
            Library * l = P;
            if (!isfound(vP, l))
                vP.push_back(P); 
            vL.push_back(P);  
        }
    }
    // will have to do for entire vector <Library *> vL
    for (int i = 0; i < vM.size(); i++)
    {
        vM[i]->CheckoutLink(vB, vP);
    }
    for (int i = 0; i < vB.size(); i++)
    {
        vB[i]->CheckoutLink(vM, vB);
    }
    for (int i = 0; i < vP.size(); i++)
    {
        vP[i]->CheckoutLink(vM, vP);
    }
}

void SaveLibrary()
{
    string fname;
    cout << "Enter the name of the File you want to save to: ";
    cin >> fname;
    string filename = fname;
    ofstream fout (filename.c_str());
    for (int i = 0; i < vM.size(); i++)
        vM[i]->WriteOut(fout);
    for (int i = 0; i < vB.size(); i++)
        vB[i]->WriteOut(fout);
    for (int i = 0; i < vP.size(); i++)
        vP[i]->WriteOut(fout);

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
            }
            else 
            {
                Member *M = new Member();
                M->ReadIn(fin); 
                Library * l = M;
                if (!isfound(vM, l))
                    vM.push_back(M);
                vL.push_back(M);
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
        Library * l = M;
        M->ReadIn(Ins);
        if (!isfound(vM, l))
            vM.push_back(M);
        vL.push_back(M);
    }
    else {
        cout << "That was not an option. Please try again. \n";
        AddCard();
    }
    /*for (int i = 0; i < vM.size(); i++)
      {
      vM[i]->CheckoutLink(vB, vP);
      }
      for (int i = 0; i < vB.size(); i++)
      {
      vB[i]->CheckoutLink(vM, vB);
      }
      for (int i = 0; i < vP.size(); i++)
      {
      vP[i]->CheckoutLink(vM, vP);
      }*/ // will have to do link after adding card
}

void RemoveCard()
{
    string forget;
    string remove;
    string check = "";
    Date ret = Date();
    vector <Library::Issue> issues;

    cout << "Enter the ID of the Card you want to remove: ";
    getline (cin, check); //remove;
    //cout << check;
    /*locale loc;
      for (int i = 0; i < remove.length(); i++)
      check = tolower(remove[i], loc);*/
    if (check.at(0) == 'M')
    {
        for (int i = 0; i < vM.size(); i++) {
            if (vM[i]->GetID() == check) {
                /*for (int j = 0; j < vB.size(); j++)
                  if (check == vB[j]->GetCheckedOutBy()[0]->GetID() && vB[j]->GetCheckedOutByStr()[0] != "NONE") 
                  {
                //vM[memcount]->Return(vB, asset, assetcount);
                vB[j]->Return(vM, check, i); 
                vB[j]->SetCheckedOut(ret);
                }
                for (int j = 0; j < vP.size(); j++)
                {
                issues = vP[j]->GetIssues();
                for (int k = 0; k < issues.size(); k++)
                if (issues[k].CheckedOutBy->GetID() == check && issues[k].CheckedOutBy != NULL)
                {
                vP[j]->Return(vM, issues[k].CheckedOutBy->GetID(), i); 
                issues[k].SetCheckedOutIssue(ret);
                }
                }*/ // Get return to work for removed cards
                vM.erase (vM.begin()+i);
            }
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
        cout << "Enter the name of the File you want to add: ";
        cin >> fname;
        ifstream fin;
        fin.open(fname.c_str(), ifstream::in);

        if (fin.fail())
        {
            cerr << "File: " << fname << " not found " << endl;
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
            }
            else if (line == "BOOK")
            {
                Book *B = new Book();
                B->ReadIn(fin);
                Library *l = B;
                if (!isfound(vB, l))
                    vB.push_back(B); 
                vL.push_back(B);  
            }
            else if (line == "PERIODICAL")
            {
                Periodical *P = new Periodical(); 
                P->ReadIn(fin);
                Library *l = P;
                if (!isfound(vP, l))
                    vP.push_back(P); 
                vL.push_back(P);  
            }
        }
    }
    else if (choice == "2" || choice == "manually" || choice == "Manually" || choice == "MANUALLY" || choice == "manual" || choice == "Manual" || choice == "MANUAL") {
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
            Library *l = B;
            if (!isfound(vB, l))
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
            Library *l = P;
            if (!isfound(vP, l))
                vP.push_back(P);
            vL.push_back(P);
        }
    }
    else {
        cout << "That was not an option. Please try again. \n";
        AddAsset();
    }
    /*for (int i = 0; i < vM.size(); i++)
      {
      vM[i]->CheckoutLink(vB, vP);
      }
      for (int i = 0; i < vB.size(); i++)
      {
      vB[i]->CheckoutLink(vM, vB);
      }
      for (int i = 0; i < vP.size(); i++)
      {
      vP[i]->CheckoutLink(vM, vP);
      }*/ // will have to do link after adding assets
}

void RemoveAsset()
{
    // create bool RemoveCard functions for Book and Periodical <-- Ultimately do on vector <Library> vL
    string check = "";
    string choice = "";
    int memcount = 0;
    Date ret = Date();
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
                for (int j = 0; j < vM.size(); j++)
                    if (vB[i]->GetCheckedOutBy()[0]->GetID() == vM[j]->GetID())
                        memcount = j;
                vM[memcount]->Return(vB, vB[i]->GetID(), i);
                //vB[i]->Return(vM, vB[i]->GetCheckedOutBy()[0]->GetID(), memcount); 
                //vB[i]->SetCheckedOut(ret);
                vB.erase (vB.begin()+i);
            }
        }
    }
    else if (check.at(0) == 'P')
    {
        for (int i = 0; i < vP.size(); i++) {
            if (vP[i]->GetID() == check) {
                vector <Library::Issue> issues;
                issues = vP[i] -> GetIssues();
                for (int j = 0; j < vM.size(); j++)
                    for (int k = 0; k < issues.size(); k++)
                        if (issues[k].CheckedOutBy != NULL && issues[k].CheckedOutBy->GetID() == vM[j]->GetID())
                        {
                            memcount = j;
                            vM[memcount]->Return(vP, vP[i]->GetID(), i);
                            //vP[i]->Return(vM, issues[k].CheckedOutBy->GetID(), memcount); 
                            //issues[k].SetCheckedOutIssue(ret);
                        }
                vP.erase (vP.begin()+i);
            }
        }
    }
    else
        cout << "That Asset ID does not exist. \n";
}

Date GetCurrentDate ()
{
    time_t theTime;
    time (&theTime);
    struct tm *aTime = localtime(&theTime);
    char buffer [80];

    strftime (buffer, 80, "%m/%d/%Y", aTime);
    stringstream temp;
    temp.str(buffer);

    Date today;
    today.ReadIn(temp);
    return today;
}

bool isfound (vector <Library *> L, Library * Ptr)
{
    //cout << "inside isfound\n";
    for (int i = 0; i < L.size(); i++) {
        //cout << "comparing " << L[i]->GetID() << " to " << Ptr->GetID() << endl;
        if (L[i]->GetID() == Ptr->GetID()) {
            //cout << Ptr->GetID() << " was found at i = " << i << endl;
            return true;
        }
    }
    //cout << Ptr->GetID() << " was not found\n";
    return false;
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
        //cout << "Checking books\n";
        NumDaysOverdue = vB[i]->DaysOverdue(today);
        if (NumDaysOverdue > 0) 
        {
            if (!isfound(AssetsOverdue, vB[i]))
                AssetsOverdue.push_back(vB[i]);
            if (!isfound(MembersOverdue, vB[i]->GetCheckedOutBy()[0])) {
                //cout << "pushing member " << vB[i]->GetCheckedOutBy()[0]->GetID() << " to the list\n";
                MembersOverdue.push_back(vB[i]->GetCheckedOutBy()[0]);
            }
        } 
    }
    for (int i = 0; i < vP.size(); i++) 
    {
        //cout << "Checking periodicals\n";
        issues = vP[i]->GetIssues();
        //cout << "Creating issues\n";
        for (int j = 0; j < issues.size(); j++)
        {
            //cout << "Checking issues\n";
            NumDaysOverdue = issues[j].DaysOverdue(today); 
            if (NumDaysOverdue > 0)
            {
                Library *p = vP[i];
                Library *m = issues[j].CheckedOutBy;
                if (!isfound(AssetsOverdue, p))
                    AssetsOverdue.push_back(p);
                if (!isfound(MembersOverdue, m)) {
                    //cout << "pushing member " << m->GetID() << " to the list\n";
                    MembersOverdue.push_back(m);
                }
            }
        }
    }
}
//  for (int i = 0; i < MembersOverdue.size(); i++)
//MembersOverdue[i]->WriteOut(cout);


void CheckoutAsset()
{ // Needs to check if Asset is already checkedout, needs to check which issue for periodical, should print list of mems, assets
    string member, asset, vol, volume;
    bool found = false;
    Date today = GetCurrentDate();
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
    vector <Library::Issue>  issues;
    bool memberhas = false;
    for (int i = 0; i < vB.size(); i++)
    {
        if (asset == vB[i]->GetID() && vB[i]->GetCheckedOutBy()[0] == NULL)
        {
            found = true;
            //if (vM[memcount]->GetID() == vB[assetcount]->GetCheckedOutByStr()[0])
            //{
            memberhas = true;
            vM[memcount]->Checkout(vB, asset, assetcount);
            vB[assetcount]->Checkout(vM, member, memcount);
            vB[assetcount]->SetCheckedOut(today);
            break;
            //}
        }
        assetcount++;
    }
    if (found == false) 
    {
        assetcount = 0;
        for (int i = 0; i < vP.size(); i++)
        {
            issues = vP[i]->GetIssues();
            if (asset == vP[i]->GetID())
            {
                found == true;
                for (int j = 0; j < issues.size(); j++)
                    if (issues[j].CheckedOutBy == NULL)
                    {
                        /*cout << "Which Volume are they checking out: ";
                          cin >> vol;*/
                        //if (vM[memcount]->GetID() == issues[j].CheckedOutByStr)
                        //{
                        //isse = atoi(iss.c_str());
                        /*if (issues[j].GetVolume() == vol)
                          {*/
                        memberhas = true;
                        vM[memcount]->Checkout(vP, asset, assetcount);
                        vP[assetcount]->Checkout(vM, member, memcount);
                        vP[assetcount]->SetCheckedOut(today);
                        break;
                        //}
                        //}
                    }
            }
        }
        assetcount++;
    }
    if (found == false)
    {
        cout << "That Asset ID does not exist. " << endl;
        return;
    }
    if (!memberhas)
    { 
        cout << "That Asset is already checked out! " << endl;
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
    int memcount = 0;
    int assetcount = 0;

    cout << "Enter the ID of Member who is returning an Asset: ";
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
            if (vM[memcount]->GetID() == vB[assetcount]->GetCheckedOutBy()[0] -> GetID())
            {
                vM[memcount]->Return(vB, asset, assetcount);
                vB[assetcount]->Return(vM, member, memcount); 
                vB[assetcount]->SetCheckedOut(ret);
                break;
            }
            else 
            {
                cout << "That Member has not checked out that Asset!" << endl;
            }
        }
        assetcount++;
    }
    if (found == false) {
        assetcount = 0;
        for (int i = 0; i < vP.size(); i++) {
            if (asset == vP[i]->GetID()) {
                found == true;
                vector <Library::Issue> issues;
                issues = vP[i] -> GetIssues();
                bool memberhas = false;
                for (int j = 0; j <issues.size(); j++)
                {
                    if (vM[memcount]->GetID() == issues[j].CheckedOutByStr)
                    {
                        vM[memcount]->Return(vP, asset, assetcount);
                        vP[assetcount]->Return(vM, member, memcount);
                        vP[assetcount]->SetCheckedOut(ret);
                        memberhas = true;
                        break;
                    }
                }
                if (!memberhas)
                {
                    cout << "That Member has not checked out that Asset!" << endl;
                }
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
    int count;
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
            if (MembersOverdue[i] != NULL)
            {
                count = 0;
                MembersOverdue[i]->WriteOut(fout);
                vector <Library *> checkedout;
                checkedout = MembersOverdue[i]->GetCheckedOutVec();
                for (int i = 0; i < checkedout.size(); i++)
                    if (isfound(AssetsOverdue, checkedout[i]))
                        count++;
                fout << "\t" << "Assets Overdue Count: " << count << endl;
                for (int j = 0; j < AssetsOverdue.size(); j++)
                {
                    for (int k = 0; k < checkedout.size(); k++) {
                        if (AssetsOverdue[j]->GetID() == checkedout[k]->GetID()) 
                        {
                            if (AssetsOverdue[j]->IsA() == Library::BOOK)
                            {
                                fout << "\t"  << AssetsOverdue[j]->GetID() << ": ";
                                fout << setw (18) << left << AssetsOverdue[j]->GetName() << "\t";
                                fout << "Days Overdue: " <<  AssetsOverdue[j]->DaysOverdue(today) << endl;
                            }
                            else 
                            {
                                vector <Library::Issue> issues;
                                issues = AssetsOverdue[j]->GetIssues();
                                for (int z = 0; z < issues.size(); z++)
                                    if (issues[z].DaysOverdue(today) > 0 && !issues[z].CheckedOut.IsNull())
                                    {
                                        fout << "\t"  << AssetsOverdue[j]->GetID() << ": ";
                                        fout << setw (18) << left << AssetsOverdue[j]->GetName() << "\t";
                                        fout << "Days Overdue: " <<  issues[z].DaysOverdue(today) << endl;
                                    }
                            }
                        }
                    }
                }
                fout << endl;
                /*MembersOverdue[i]->WriteOut(fout);
                  vector <Library *> checkedout;
                  checkedout = MembersOverdue[i]->GetCheckedOutVec();
                  fout << "\t" << "Assets Overdue Count: " << checkedout.size() << endl;
                  for (int j = 0; j < AssetsOverdue.size(); j++)
                  {
                  for (int k = 0; k < checkedout.size(); k++) {
                  if (AssetsOverdue[j]->GetID() == checkedout[k]->GetID()) //MembersOverdue[i]->GetID())//checkedout[i]) // return CheckedOut vector
                  {
                  fout << "/t"  << AssetsOverdue[j]->GetID() << ": ";
                  fout << AssetsOverdue[j]->GetName() << "/t";
                  fout << "Days Overdue: " <<  AssetsOverdue[j]->DaysOverdue(today) << endl;
                  }
                  }
                  }*/
            }

            else 
            {
            }

        }
    }
    else if (choice == '2')
    {
        cout << "\nMembers with Overdue Assets \t\t Today's Date: ";
        today.WriteOut(cout);
        cout << endl << endl;
        for (int i = 0; i < MembersOverdue.size(); i++)
        {
            if (MembersOverdue[i] != NULL)
            {
                count = 0;
                MembersOverdue[i]->WriteOut(cout);
                vector <Library *> checkedout;
                checkedout = MembersOverdue[i]->GetCheckedOutVec();
                for (int i = 0; i < checkedout.size(); i++)
                    if (isfound(AssetsOverdue, checkedout[i]))
                        count++;
                cout << "\t" << "Assets Overdue Count: " << count << endl;
                for (int j = 0; j < AssetsOverdue.size(); j++)
                {
                    for (int k = 0; k < checkedout.size(); k++) {
                        if (AssetsOverdue[j]->GetID() == checkedout[k]->GetID()) 
                        {
                            if (AssetsOverdue[j]->IsA() == Library::BOOK)
                            {
                                cout << "\t"  << AssetsOverdue[j]->GetID() << ": ";
                                cout << setw (18) << left << AssetsOverdue[j]->GetName() << "\t";
                                cout << "Days Overdue: " <<  AssetsOverdue[j]->DaysOverdue(today) << endl;
                            }
                            else 
                            {
                                vector <Library::Issue> issues;
                                issues = AssetsOverdue[j]->GetIssues();
                                for (int z = 0; z < issues.size(); z++)
                                    if (issues[z].DaysOverdue(today) > 0 && !issues[z].CheckedOut.IsNull())
                                    {
                                        cout << "\t"  << AssetsOverdue[j]->GetID() << ": ";
                                        cout << setw (18) << left << AssetsOverdue[j]->GetName() << "\t";
                                        cout << "Days Overdue: " <<  issues[z].DaysOverdue(today) << endl;
                                    }
                            }
                        }
                    }
                }
                cout << endl;
            }
            else 
            {
            }

        }
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
        fout << endl << endl ;
        for (int i = 0; i < AssetsOverdue.size(); i++)
        {
            if (AssetsOverdue[i]->IsA() == Library::BOOK)
            {
                if (AssetsOverdue[i]->GetCheckedOutBy()[0] != NULL)
                {
                    /*Library *b = new Book();
                      b = AssetsOverdue[i];
                      if (!b->CheckedOut.IsNULL())
                      {*/
                    type = "BOOK";
                    fout << "\nType: " << type << endl;
                    fout << "Asset Name: " << AssetsOverdue[i] -> GetName() << endl;
                    fout << "Days Overdue: " << AssetsOverdue[i] -> DaysOverdue(today) << endl;
                    fout << "ID: " << AssetsOverdue[i] -> GetID() << endl;
                    fout << "Name: " << AssetsOverdue[i] -> GetCheckedOutBy()[0] -> GetName() <<
                        endl << endl;
                    //}
                }
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
                        if (!issues[j].CheckedOut.IsNull())
                        {
                            fout << "\nType: " << type << endl;
                            fout << "Asset Name: " << AssetsOverdue[i] -> GetName() << endl;
                            fout << "Days Overdue: " << issues[j].DaysOverdue(today) << endl; 
                            fout << "ID: " << AssetsOverdue[i] -> GetID() << endl;
                            fout << "Name: " << issues[j].CheckedOutBy -> GetName() << endl << endl;
                        }
                    }
                }
            }
        }
        fout << "Total: " << AssetsOverdue.size() << endl;
        fout << "Total Fees: $" << 13 * AssetsOverdue.size() << endl;

    }
    else if (choice == '2')
    {
        cout << "\nOverdue Assets \t\t Today's Date: ";
        today.WriteOut(cout);
        cout << endl << endl;
        for (int i = 0; i < AssetsOverdue.size(); i++)
        {
            if (AssetsOverdue[i] != NULL)
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
        cout << "What area code do you want to see? : ";
        cin >> areacode;
        fout << "Members in " << areacode << endl;
        fout << "Generated on: ";
        today.WriteOut(fout);
        fout  << endl;
        fout << "---------------------------------------------------" << endl;
        fout << setw(6) << left << "ID" << setw(22) << left << "Name" << setw(14) << left 
            << "Phone Number" << endl << endl;
        for (int i = 0; i < vM.size(); i++)
            if (areacode == vM[i]->GetPhone().substr(0,3))
                fout << setw(4) << left << vM[i]->GetID() << "  " << setw(20) 
                    << left << vM[i]->GetName() << "  " << setw(12) 
                    << left <<  vM[i]->GetPhone() << endl;
    }
    if (choice == '2')
    {
        string areacode;
        cout << "What area code do you want to see? : ";
        cin >> areacode;
        cout << "\nMembers in " << areacode << endl;
        cout << "Generated on: ";
        today.WriteOut(cout);
        cout << endl;
        cout << "---------------------------------------------------" << endl;
        cout << setw(6) << left << "ID" << setw(22) << "Name" << setw(14) << "Phone Number" << endl << endl; 
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
            exit(0);
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
