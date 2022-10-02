#ifndef MINIGIT_H
#define MINIGIT_H

using namespace std;

struct singlyNode{
string fileName; // Name of local file
string fileVersion; // Name of file in .minigit folder
singlyNode * next;
};


struct doublyNode{
int commitNumber;
singlyNode * head;
doublyNode * previous;
doublyNode * next;
};


class miniGit {

    public:
        ~miniGit();
        void addDouble(int commit);
        void addSingle(int commit, string fileName, string fileVersion);
        void removeSingle(int commit, string fileName);
        bool checkAdd(int commit, string fileName);
        void checkVersion(int commit, string fileName, string &version);
        doublyNode* getHead();
        singlyNode* getLinked(int commit);
        void copySLL(int commit);
        

    private:
        doublyNode* RepositoryHead;


};

#endif

