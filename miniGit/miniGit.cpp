#include <iostream>
#include "miniGit.hpp"


doublyNode* miniGit::getHead()
    {
        return RepositoryHead;
    }

void miniGit::addDouble(int commit)
    {
        if (RepositoryHead == NULL)
            {
                doublyNode* head = new doublyNode;
                RepositoryHead = head;
                head->commitNumber = 0;
                head->head = NULL;
                head->next = NULL;
                head->previous = RepositoryHead;
                return;
            }
        
        doublyNode* node = new doublyNode;
        node->commitNumber = commit;

        doublyNode* curr = RepositoryHead;

        while (curr->commitNumber != commit - 1)
            {
                curr = curr->next;
            }

        curr->next = node;
        node->previous = curr;
        node->head = NULL;
        node->next = NULL;
        return;

    }

void miniGit::addSingle(int commit, string fileName, string versionName)
    {
       // cout << "uuu" << endl;
        //cout << RepositoryHead->commitNumber << endl;
        doublyNode* curr = RepositoryHead;

        

        while (curr->commitNumber != commit)
            {
                curr = curr->next;
            }
              


        if (curr->head == NULL)
            {
               //cout << "hi" << endl;
                singlyNode* Node = new singlyNode;
                // cout << "hi" << endl;
                curr->head = Node;
                // cout << "hi" << endl;
                Node->next = NULL;
                // cout << "hi" << endl;
                Node->fileName = fileName;
                 //cout << "hi" << endl;
                Node->fileVersion = versionName;
                 //cout << "hi" << endl;
                return;
            }

        singlyNode* cur = curr->head;

        while (cur->next != NULL)
            {
                cur = cur->next;
            }
        
        singlyNode* Node = new singlyNode;
        cur->next = Node;
        Node->next = NULL;
        Node->fileName = fileName;
        Node->fileVersion = versionName;
        return;


    }

void miniGit::removeSingle(int commit, string fileName)
    {
        doublyNode* curr = RepositoryHead;

        while (curr->commitNumber != commit)
            {
                curr = curr->next;
            }

        if (curr->head == NULL)
            {
                cout << "File is not currently added" << endl;
                return;
            }
        
        singlyNode* cur = curr->head;
        singlyNode* prev = curr->head;

        if (curr->head->fileName == fileName)
            {
                cur = curr->head;
                curr->head = cur->next;
                delete cur;
                cout << "Successfully removed " << fileName << " from added list" << endl;
                return;
            }

        while (cur->next != NULL)
            {
                cur = cur->next;
                if (cur->fileName == fileName)
                    {
                        prev->next = cur->next;
                        delete cur;
                        cout << "Successfully removed " << fileName << " from added list" << endl;
                        return;
                    }
                prev = prev->next;
            }
        
        cout << "File is not currently added" << endl;
        return;
    }


singlyNode* miniGit::getLinked(int commit)
    {
        doublyNode* curr = RepositoryHead;

        for (int i = 0; i < commit; i++)
            {
                curr = curr->next;
            }
        
        return curr->head;
    }

void miniGit::copySLL(int commit)
    {

        doublyNode* curr = RepositoryHead;
        doublyNode* prev = RepositoryHead;

        while(curr->next != NULL)
            {
                prev = curr;
                curr = curr->next;
            }

        



        
        singlyNode* copy = prev->head;
        singlyNode* PostCopy;




        singlyNode* newNode = new singlyNode;
        newNode->fileName = copy->fileName;
        newNode->fileVersion = copy->fileVersion;
        newNode->next = NULL;
        curr->head = newNode;
        PostCopy = curr->head;
        copy = copy->next;

        while (copy != NULL)
            {
                singlyNode* newNode = new singlyNode;
                newNode->fileName = copy->fileName;
                newNode->fileVersion = copy->fileVersion;
                newNode->next = NULL;

                PostCopy->next = newNode;
                PostCopy = PostCopy->next;
                copy = copy->next;
            }
    }

bool miniGit::checkAdd(int commit, string fileName)
    {
        doublyNode* curr = RepositoryHead;

        while (curr->commitNumber != commit)
            {
                curr = curr->next;
            }
        
        singlyNode* cur = curr->head;

        while (cur != NULL)
            {
                
                if (cur->fileName == fileName)
                    {
                        return true;
                    }
                cur = cur->next;
            }
        
        return false;
    }

void miniGit::checkVersion(int commit, string fileName, string &version)
    {
        if (commit < 0)
            {
                version = "-1";
                return;
            }
        
        doublyNode* curr = RepositoryHead;

        while (curr->commitNumber != commit)
            {
                curr = curr->next;
            }
        
        singlyNode* cur = curr->head;

        while (cur != NULL)
            {
                if (cur->fileName == fileName)
                    {
                        version = cur->fileVersion;
                        return;
                    }
                    cur = cur->next;
            }
        
        checkVersion(commit - 1, fileName, version);
    }

miniGit::~miniGit()
    {
        doublyNode* curr = RepositoryHead;
        doublyNode* next = RepositoryHead;
        singlyNode* cur = curr->head;
        while (curr != NULL)
            {
                next = curr->next;

                cur = curr->head;
                while (curr->head != NULL)
                    {
                        cur = curr->head;
                        curr->head = curr->head->next;
                        delete cur;
                    }
                
                delete curr;
                curr = next;
            }
    }