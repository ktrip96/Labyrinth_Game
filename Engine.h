#include <iostream>

using namespace std;

class Engine
{
    // χειρισμός χάρτη (στον constructor)
    // υπολογισμός score

public:
    Engine(int argc, char **argv)
    {
        cout << "Constructor" << endl;
        cout << "Argc is : " << argc << " and argv[1] is: " << argv[1] << endl;
    }
};