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
void OverdueAssets ();


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

    if (selection == '1')
        return 1;
    if (selection == '2')
        return 2;
    if (selection == '3')
        return 3;
    if (selection == '4')
        return 4;
    if (selection == '5')
        return 5;
    if (selection == '6')
        return 6;
    if (selection == '7')
        return 7;
    if (selection == '8')
        return 8;
    if (selection == '9')
        return 9;
    if (selection == '0' || selection == 'q')
        return 0;
    else 
        cout << "Invalid input\n";
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
            Library *M = new Member(); 
            M->ReadIn(fin);
            if (!isfound(vL, M))
                vL.push_back(M);  
        }
        else if (line == "BOOK")
        {
            Library * B = new Book(); 
            B->ReadIn(fin);
            if (!isfound(vL, B))
                vL.push_back(B); 
        }
        else if (line == "PERIODICAL")
        {
            Library *P = new Periodical(); 
            P->ReadIn(fin);
            if (!isfound(vL, P))
                vL.push_back(P); 
        }
    }

    for (int i = 0; i < vL.size(); i++) {
        if (vL[i]->IsA() == Library::MEMBER) {
            for (int j = 0; j < vL.size(); j++) {
                if (vL[j]->IsA() != Library::MEMBER) {
                    debug << "checkout link for member " << vL[i]->GetID() << " and asset " << vL[j]->GetID() << endl;
                    vL[i]->CheckoutLink(vL[j]);
                    vL[j]->CheckoutLink(vL[i]);
                }
            }
        }
    }
    /*
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
    */
}

void SaveLibrary() {
    string fname;
    cout << "Enter the name of the File you want to save to: ";
    cin >> fname;
    string filename = fname;
    ofstream fout (filename.c_str());
    for (int i = 0; i < vL.size(); i++)
        vL[i]->WriteOut(fout);

}

void AddCard() {
    string fname, choice, temp, endLineClear;
    stringstream Ins;
    cout << "Would you like to add from a file (1) or manually (2)? ";
    cin >> choice;
    if (choice == "1") {
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
                Library *M = new Member();
                M->ReadIn(fin); 
                if (!isfound(vL, M))
                    vL.push_back(M);
            }
        }
    }
    else if (choice == "2") {
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

        Library *M = new Member();
        M->ReadIn(Ins);
        if (!isfound(vL, M))
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

void RemoveCard() {
    string forget;
    string remove;
    string check = "";
    Date ret = Date();

    cout << "Enter the ID of the Card you want to remove: ";
    getline (cin, check); //remove;

    if (check.at(0) == 'M') {
        for (int i = 0; i < vL.size(); i++) {
            if (vL[i]->GetID() == check) {
                vector<Library*> checkedout = vL[i]->GetCheckedOutVec();

                debug << "Member " << vL[i]->GetID() << " has " << checkedout.size() << " assets checked out\n";

                for (int j = 0; j < checkedout.size(); j++) {
                    vector <Library::Issue> issues = checkedout[j]->GetIssues();

                    debug << "does " << checkedout[j]->GetID() << " have issues?\n";
                    if (issues.size() > 0) {
                        for (int k = 0; k < issues.size(); k++) {
                            debug << "is " << issues[k].CheckedOutByStr << " == " << check << "?\n";
                            if (issues[k].CheckedOutByStr == check) {
                                debug << "Member " << check << " is returning " << checkedout[j]->GetID() << ":" << k << " before being removed\n";
                                checkedout[j]->Return(k);
                            }
                        }
                    }
                    
                    else {
                        debug << "Member " << check << " is returning " << checkedout[j]->GetID() << " before being removed\n";
                        checkedout[j]->Return(0);
                    }
                }

                vL.erase (vL.begin()+i);
                break;
            }
        }
    }
    else
        cout << "That Member ID does not exist. \n";
    /*if (putchar (tolower(vM[i].Name.c_str())) == putchar (tolower(remove.c_str())))
      vM.erase (vM.begin()+i);*/
}

void AddAsset() {
    string fname, choice, temp, endLineClear;
    stringstream Ins;
    cout << "Would you like to add from a file (1) or manually (2)? ";
    cin >> choice;
    if (choice == "1") {
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
    else if (choice == "2") {
        cout << "\nBook (1) or Periodical (2): ";
        temp.clear();
        cin >> temp;
        if (temp == "1") {
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

            Library *B = new Book();
            B->ReadIn(Ins);
            if (!isfound(vL, B))
                vL.push_back(B);
        }
        else if (temp == "2")
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

            Library *P = new Periodical();
            P->ReadIn(Ins);
            if (!isfound(vL, P))
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

void RemoveAsset() {
    // create bool RemoveCard functions for Book and Periodical <-- Ultimately do on vector <Library> vL
    string check = "";
    string choice = "";
    int memcount = 0;
    Date ret = Date();
    cout << "Enter the ID of the Asset you want to remove: ";
    getline (cin, check); //remove;

    if (check.at(0) == 'B' || check.at(0) == 'P') 
    {
        for (int i = 0; i < vL.size(); i++) {
            if (vL[i]->GetID() == check) {
                vector<Library::Issue> issues = vL[i]->GetIssues();
                if (issues.size() > 0) {
                    for (int j = 0; j < issues.size(); j++) {
                        for (int k = 0; k < vL.size(); k++) {
                            if (issues[j].CheckedOutByStr == vL[k]->GetID()) {
                                vector<Library*> checkedout = vL[k]->GetCheckedOutVec();

                                for (int l = checkedout.size()-1; l >= 0; l--) {
                                    if (checkedout[l]->GetID() == check) {
                                        vL[k]->Return(l);
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    for (int j = 0; j < vL.size(); j++) {
                        vector<Library*> checkedout = vL[j]->GetCheckedOutVec();
                        for (int k = 0; k < checkedout.size(); k++) {
                            if (checkedout[k]->GetID() == check) {
                                checkedout.erase(checkedout.begin()+k);
                                break;
                            }
                        }
                    }
                }

                vL.erase (vL.begin()+i);
            }
        }
    }
    else
        cout << "That Asset ID does not exist. \n";
}

Date GetCurrentDate () {
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
    debug << "inside isfound\n";
    for (int i = 0; i < L.size(); i++) {
        debug << "comparing " << L[i]->GetID() << " to " << Ptr->GetID() << endl;
        if (L[i]->GetID() == Ptr->GetID()) {
            debug << Ptr->GetID() << " was found at i = " << i << endl;
            return true;
        }
    }
    debug << Ptr->GetID() << " was not found\n";
    return false;
}

void OverdueAssets () {
    Date today = GetCurrentDate();

    for (int i = 0; i < vL.size(); i++)
    {
        vector <Library::Issue> issues = vL[i]->GetIssues();

        if (issues.size() > 0) {
            for (int j = 0; j < issues.size(); j++)
            {
                if (issues[j].DaysOverdue(today) > 0); 
                {
                    Library *p = vL[i];
                    Library *m = issues[j].CheckedOutBy;
                    if (!isfound(AssetsOverdue, p))
                        AssetsOverdue.push_back(p);
                    if (!isfound(MembersOverdue, m)) {
                        debug << "pushing member " << m->GetID() << " to the list\n";

                        MembersOverdue.push_back(m);
                    }
                }
            }
        }

        else if (vL[i]->DaysOverdue(today) > 0);
        {
            if (!isfound(AssetsOverdue, vL[i]))
                AssetsOverdue.push_back(vL[i]);
            if (!isfound(MembersOverdue, vL[i]->GetCheckedOutBy()[0])) {
                debug << "pushing member " << vL[i]->GetCheckedOutBy()[0]->GetID() << " to the list\n";

                MembersOverdue.push_back(vL[i]->GetCheckedOutBy()[0]);
            }
        } 
    }
}
//  for (int i = 0; i < MembersOverdue.size(); i++)
//MembersOverdue[i]->WriteOut(cout);


void CheckoutAsset()
{ // Needs to check if Asset is already checkedout, needs to check which issue for periodical, should print list of mems, assets
    string memID;
    cout << "Enter the ID of Member who is checking out an Asset: ";
    cin >> memID;
    
    Library *searchMem = new Member();
    searchMem->SetID(memID);

    if (!isfound(vL, searchMem)) {
        cout << "That Member ID does not exist. " << endl;
        return;
    }

    int memIndex;
    for (int i = 0; i < vL.size(); i++) {
        if (memID == vM[i]->GetID()) {
            memIndex = i;
            break;
        }
    }

    string assetID;
    cout << "Enter the ID of the Asset: ";
    cin >> assetID;
    vector <Library::Issue>  issues;
    bool memberhas = false;
    for (int i = 0; i < vB.size(); i++)
    {
        issues = vP[i]->GetIssues();

        if (assetID == vP[i]->GetID())
        {
            if (issues.size() > 0) {
                int vol;
                cout << "Which Volume are they checking out: ";
                cin >> vol;
                if (issues[vol-1].CheckedOutBy == NULL)
                {
                    vL[memIndex]->Checkout(vL[i], "", 0);
                    vL[i]->Checkout(vL[memIndex], memID, vol-1);
                }
                else {
                    cout << "That Asset has been checked out already\n";
                }

                return;
            }

            else if (vB[i]->GetCheckedOutBy()[0] == NULL)
            {
                vL[memIndex]->Checkout(vL[i], "", 0);
                vL[i]->Checkout(vL[memIndex], memID, 0);
                return;
            }

            else {
                cout << "That Asset has been checked out already\n";
                return;
            }
        }
    }

    cout << "That Asset ID does not exist. " << endl;
    // Create functions in classes and set CheckedOutStr to asset, vM[memcount]->CheckedOut push back pointer to vB[assetcount]
    // or vP[assetcount], vB or vP[assetcount]->CheckedOutByStr to member, vBor vP[assetcount]->CheckedOutBy push back
    // pointer to vM[memcount], setFunction vB or vP->CheckedOutOn to today
}

// reimplement each Classes checkout function to checkout one item, get pointer linking to work in Main.cpp

void ReturnAsset()
{
    string memID, assetID;
    Date ret = Date();
    int memIndex;

    cout << "Enter the ID of Member who is returning an Asset: ";
    cin >> memID;

    for (int i = 0; i < vL.size(); i++) {
        if (memID == vL[i]->GetID()) {
            cout << "Enter the ID of the Asset to return: ";
            cin >> assetID;

            vector<Library*> checkedout = vL[i]->GetCheckedOutVec();
            for (int j = 0; j < checkedout.size(); j++) {
                if (assetID == checkedout[j]->GetID()) {
                    vector<Library::Issue> issues = checkedout[j]->GetIssues();
                    if (issues.size() > 0) {
                        int vol;
                        cout << "Enter the issue number to return: ";
                        cin >> vol;

                        if (vol <= issues.size() && issues[vol-1].CheckedOutByStr == memID) {
                            checkedout[j]->Return(vol-1);
                            vL[i]->Return(j);
                            return;
                        }
                        else {
                            cout << "Member " << memID << " does not have that Asset checked out\n";
                            return;
                        }
                    }
                    else {
                        if (checkedout[j]->GetCheckedOutByStr()[0] == memID) {
                            checkedout[j]->Return(0);
                            vL[i]->Return(j);
                            return;
                        }
                    }

                    cout << "Member " << memID << " does not have that Asset checked out\n";
                    return;
                }
            }

            cout << "Member " << memID << " does not have that Asset checked out\n";
            return;
        }
    }

    cout << "Member " << memID << " was not found\n";
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

    int sel = selection - '1';

    if (sel >= 0 && sel <= 3)
        return sel;
    else {
        cout << "Invalid input\n";
        return -1;
    }
}

void GenerateReport()
{
    OverdueAssets();
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
        fout << setw(6) << left << "ID" << setw(22) << left << "Name" << setw(14) << left << "Phone Number" << endl << endl;
        for (int i = 0; i < vL.size(); i++) {
            if (vL[i]->IsA() == Library::MEMBER && areacode == vL[i]->GetPhone().substr(0,3)) {
                fout << setw(4) << left << vL[i]->GetID() << "  " << setw(20) << left << vL[i]->GetName() << "  " << setw(12) << left <<  vL[i]->GetPhone() << endl;
            }
        }
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

        for (int i = 0; i < vL.size(); i++) {
            if (vL[i]->IsA() == Library::MEMBER && areacode == vL[i]->GetPhone().substr(0,3)) {
                cout << setw(4) << left << vL[i]->GetID() << "  " << setw(20) << vL[i]->GetName() << "  " << setw(12) << vL[i]->GetPhone() << endl;
            }
        }
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
