#include <iostream>
using namespace std;


void split(string line, char spliter, string array[], int capacity)
    {
        int i = 0;
        int f = 0;
        bool checker = false;

          for (int g = 0; g < line.length(); g++) // splits the line by ,
                {
                    if (i > 4)
                        {
                            checker = true;
                        }
                    if (line[g] == spliter)
                        {
                            array[i] = line.substr(f,g - f);
                            i++;
                            f = g + 1;
                        }
                }
        if (checker == false)
        {
            array[i] = line.substr(f,line.length() - f);
        }
    }

int main() {
    string test = "Ritchie,5,2,w,34,456,2,899961,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1";
    int capacity = 51;
    string storage[capacity];

    cout << storage[0] << endl;
    cout << storage[1] << endl;
    cout << storage[2] << endl;
    cout << storage[3] << endl;
    cout << storage[4] << endl;
    cout << storage[5] << endl;
    cout << storage[6] << endl;
    cout << storage[7] << endl;
    

}