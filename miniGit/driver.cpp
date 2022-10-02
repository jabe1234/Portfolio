#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#include "miniGit.hpp"

using namespace std;
namespace fs = std::filesystem;

// returns filename without format (file.txt -> file)
string nameFile(string fileName)
    {
        int length = fileName.length();
        string sub = fileName.substr(0, length - 4);
        return sub;
    }

// returns format of file (file.txt -> .txt)
string format(string fileName)
    {
        int length = fileName.length();
        string sub = fileName.substr(length - 4);
        return sub;
    }

// returns true if two files entered are the same
bool checkSimilarity(string file1, string file2)
    {
        ifstream in_file1;
        in_file1.open(file1);

        ifstream in_file2;
        in_file2.open(file2);

        string line1, line2;

        vector<string> file1Line;
        vector<string> file2Line;

        while (getline(in_file1, line1))
            {
                file1Line.push_back(line1);
            }
        
        
        while(getline(in_file2, line2))
            {
                file2Line.push_back(line2);
            }
        
        
        
        if (file2Line.size() != file1Line.size())
            {
                in_file1.close();
                in_file2.close();
                return false;
            }

        for (int i = 0; i < file1Line.size(); i++)
            {
                if (file1Line[i].length() != file2Line[i].length())
                    {
                        in_file1.close();
                        in_file2.close();
                        return false;
                    }
            }
        
        for (int i = 0; i < file1Line.size(); i++)
            {
                for (int y = 0; y < file1Line[i].size(); y++)
                    {
                        if (file1Line[i][y] != file2Line[i][y])
                            {
                                in_file1.close();
                                in_file2.close();
                                return false;
                            }
                    }
            }
        
        
        in_file1.close();
        in_file2.close();
        return true;
    }

// returns false if the files are different and updates Commit and Update to the lines that are the first to be different
bool diff(string file1, string file2, string &Commit, string &Update)
    {

        ifstream in_file1;
        in_file1.open(file1);

        ifstream in_file2;
        in_file2.open(file2);

        string line1, line2;

        vector<string> file1Line;
        vector<string> file2Line;

        while (getline(in_file1, line1))
            {
                file1Line.push_back(line1);
            }
        
        
        while(getline(in_file2, line2))
            {
                file2Line.push_back(line2);
            }
        
        for (int i = 0; i < file1Line.size(); i++)
            {
                if (file1Line[i] != file2Line[i])
                    {
                        Commit = file1Line[i];
                        Update = file2Line[i];
                        in_file1.close();
                        in_file2.close();
                        return false;
                    }
            }
        
        for (int i = 0; i < file1Line.size(); i++)
            {
                for (int y = 0; y < file1Line[i].size(); y++)
                    {
                        if (file1Line[i][y] != file2Line[i][y])
                            {
                                Commit = file1Line[i];
                                Update = file2Line[i];
                                in_file1.close();
                                in_file2.close();
                                return false;
                            }
                    }
            }
        
        
        in_file1.close();
        in_file2.close();
        return true;
    }

//prints menu
void printMenu()
    {
        cout << "====================" << endl;
        cout << "Make a choice:" << endl;
        cout << "1: Add" << endl;
        cout << "2: Remove" << endl;
        cout << "3: Commit" << endl;
        cout << "4: Checkout" << endl;
        cout << "5: Status" << endl;
        cout << "6: Diff" << endl;
        cout << "7: Quit" << endl;
        cout << "====================" << endl;
        return;
    }

//copys contents of file1 to file2
void copy(string file1, string file2)
    {
        ifstream in_file;
        in_file.open(file1);

        ofstream out_file;
        out_file.open(file2);

        string curr;

        while (getline(in_file, curr))
            {
                out_file << curr << endl;
            }
        
        in_file.close();
        out_file.close();
        return;
    }

int main()  {
    
    //initalize repositiory
    cout << "Would the user like to create a repository? (Y/N)" << endl;
    string line;
    getline(cin,line);

    
    if (line != "Y")
        {
            cout << "Error: repository required" << endl;
            cout << "Closing program"<< endl;
            return 0;
        }

    fs::create_directory(".minigit");
    miniGit* MG = new miniGit;
    MG->addDouble(0);


    int choice = 0;
    ifstream in_file;
    ofstream out_file;
    int commitN = 0;
    string fileName = "file1.txt";
    string Storedfile;
    string oldFileType;
    string fileType;
    string fileVersion;
    string destination = "/Users/jaybentley/Documents/CSCI2270/miniGit_Phase2/.miniGit/";
    bool similiarity;
    bool notAdd;

    string commitChoice;
    string yes;

    string NewFile;
    bool currentCommit = true;
    bool needToCommit = false;
    bool differenceCheck;

    int changeVersion;

    doublyNode* curr;
    singlyNode* cur;
    singlyNode* prev;

    string fileName1;
    string fileName2;



    while (choice != 7) {

        printMenu(); // print menu

        getline(cin,line);
        choice = stoi(line);

        switch (choice)
        {
        case 1: // add

            if (currentCommit == false)
                {
                    cout << "The current version of the files must be checked out to add files" << endl;
                    cout << "Current Commit: " << commitN -1 << endl; 
                    break;
                }

            cout << "What file would you like to add?" << endl;
            getline(cin,line);

            if (MG->checkAdd(commitN, line))
                {
                    cout << "File is already added to be commited" << endl;
                    break;
                }

            //check if file exists in directory
            in_file.open(line);
           // cout << "hi" << endl;
            if (in_file.fail() == true)
                {
                    in_file.close();
                    cout << "file does not exist in directory" << endl;
                    break;
                }
          //cout << "hi" << endl;
            in_file.close();

            fileName = line + fileType;

            fileType = format(line);

            MG->checkVersion(commitN, line, fileVersion);

            // if (fileVersion == "-1")
            //     {
            //         fileVersion = "0";
            //     }

            MG->addSingle(commitN, line, fileVersion); 


            cout << "Successfully added " << line << " to the commit list" << endl;
            //curr = MG->getHead();
            //cout << curr->head->fileName << endl;

            break;

        case 2: // remove

            if (currentCommit == false)
                {
                    cout << "The current version of the files must be checked out to remove files" << endl;
                    cout << "Current Commit: " << commitN -1 << endl; 
                    break;
                }

            cout << "Which file would you like to remove?" << endl;
            getline(cin, line);

            MG->removeSingle(commitN, line);

            break;

        case 3: // commit

            if (currentCommit == false)
                {
                    cout << "The current version of the files must be checked out to commit files" << endl;
                    cout << "Current Commit: " << commitN -1 << endl; 
                    break;
                }

            cur = MG->getLinked(commitN);
            prev = MG->getLinked(commitN - 1);

            if (cur == NULL)
                {
                    cout << "There are no files added" << endl;
                    break;
                }

            needToCommit = false;

            while (cur != NULL)
                {
                    //check for similaity

                    fileName1 = nameFile(cur->fileName) + "." + cur->fileVersion + format(cur->fileName);
                    fileName2 = cur->fileName;

                    similiarity = true;
                    similiarity = checkSimilarity(destination + fileName1, fileName2);
                    //cout << similiarity << endl;


                    if (cur->fileVersion == "-1")
                        {
                            needToCommit = true;
                            changeVersion = stoi(cur->fileVersion);
                            changeVersion++;
                            cur->fileVersion = to_string(changeVersion);


                            //create and copy file
                            NewFile = destination + nameFile(cur->fileName) + "." + cur->fileVersion + format(cur->fileName);
                            copy(fileName2, NewFile);
                            cout << "Successfully commited " << nameFile(cur->fileName) + "." + cur->fileVersion + format(cur->fileName) << endl;
                        }

                    else if (similiarity == true)
                        {
                            cout << fileName2 << " has no changes from last commit" << endl;
                        }
                    
                    else
                        {

                            needToCommit = true;
                             //change version number
                            changeVersion = stoi(cur->fileVersion);
                            changeVersion++;
                            cur->fileVersion = to_string(changeVersion);


                            //create and copy file
                            NewFile = destination + nameFile(cur->fileName) + "." + cur->fileVersion + format(cur->fileName);
                            copy(fileName2, NewFile);
                            cout << "Successfully commited " << nameFile(cur->fileName) + "." + cur->fileVersion + format(cur->fileName) << endl;

                        }

                    

                 

                    cur = cur->next;
                }

        if (needToCommit == true)
            {
                commitN++; // end with incrimenting commitN
                //cout << commitN << endl;

                MG->addDouble(commitN);
                MG->copySLL(commitN);
            }
            break;

        case 4: // checkout

            if (commitN == 0)
                {
                    cout << "No files have been commited yet" << endl;
                    break;
                }

            cout << "Which commit would you like to checkout from?" << endl;
            getline(cin, commitChoice);

            similiarity = true;
            cur = MG->getLinked(commitN - 1);

            yes = "Y";
            while (cur != NULL)
                {
                    line = cur->fileName;
                    similiarity = checkSimilarity(line, destination + nameFile(cur->fileName) + "." + cur->fileVersion + format(cur->fileName));
                            
                    if (similiarity == false)
                        {
                            cout << "Warning: work will be lost" << endl;
                            cout << "Coutinue? (Y/N)" << endl;
                            getline(cin, yes);
                            break;
                        }
                        
                    cur = cur->next;
                }
            if (yes == "N")
                {
                    break;
                }

            
            if (stoi(commitChoice) == commitN -1)
                {
                    currentCommit = true;
                }
            
            else
                {
                    currentCommit = false;
                }
            
            
            
            cur = MG->getLinked(stoi(commitChoice));

            while (cur != NULL)
                { 
                    cout << cur->fileName << " successfully checked out" << endl;
                    copy(nameFile(destination + cur->fileName) + "." + cur->fileVersion + format(cur->fileName),cur->fileName);
                    cur = cur->next;
                }
                


            break;

        case 5: // status

            if (commitN == 0)
                {
                    cout << "No files have been commited yet" << endl;
                    break;
                }

            cur = MG->getLinked(commitN - 1);
            
            while (cur != NULL)
                {
                    if (MG->checkAdd(commitN, cur->fileName) == false)
                        {
                            cout << cur->fileName << " is not currently added" << endl;
                            
                        }
                    else    {
                            similiarity = checkSimilarity(destination + nameFile(cur->fileName) + "." + cur->fileVersion + format(cur->fileName),cur->fileName);
                            if (similiarity != true)
                                    {
                                        cout << cur->fileName << " version is different than last commit" << endl;
                                        
                                    }
                            else    {
                                cout << cur->fileName << " has not changed since last commit" << endl;
                            }
                    }
                    cur = cur->next;
                }

            
            break;

        case 6: // diff


            if (commitN == 0)
                {
                    cout << "No files have been commited yet" << endl;
                    break;
                }
            
            
                
            cout << "What file would you like to check for a difference?" << endl;
            getline(cin, line);
        
            if (MG->checkAdd(commitN, line) == false)
                {
                    cout << line << " is not currently added" << endl;
                    break;
                }

            cur = MG->getLinked(commitN - 1);
            differenceCheck = false;

            while (cur != NULL)
                {
                    if (cur->fileName == line)
                        {
                            differenceCheck = true;
                            fileName  = destination + nameFile(cur->fileName) + "." + cur->fileVersion + format(cur->fileName);
                            break;
                        }
                    cur = cur->next;
                }

            similiarity = checkSimilarity(line, fileName);

            if (differenceCheck == false)
                {
                    cout << "File was not found in the most-current commit" << endl;
                    break;
                }

            if (similiarity == true)
                {
                    cout << "File is up to date" << endl;
                    break;
                }
            
            else
                {
                    similiarity = diff(fileName, line, fileName1, fileName2);
                    cout << "Commited Version: " << fileName1 << endl;
                    cout << "Edited Version: " << fileName2 << endl;
                }
            break;

        case 7:

            cout << "Thanks for working with us!" << endl;
            cout << "Closing Program" << endl;
            break;
        
        default:
            cout << "Invalid entry" << endl;
            cout << "Enter a new option" << endl;
            break;
        }
    }

fs::remove_all(".minigit");
MG->~miniGit();
//delete MG;

return 0;
}
