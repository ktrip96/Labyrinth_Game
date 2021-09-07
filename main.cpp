#include <iostream>
#include "Engine.h"

using namespace std;

// χρησιμοποιώ τα argc και argv, για να διαβάσω το αρχείο με τον χάρτη από το terminal

int main(int argc, char **argv)
{
    Engine e(argc, argv);
    // e.renderLabyrinth();
    Potter p;

    char ch;
    while (1)
    {
        e.printGems();
        e.renderLabyrinth();

        cout << "Please press W, A, S, D to move, Q to stay still and E to exit" << endl;
        cin >> ch;
        switch (ch)
        {
        case 'A':
            p.movePotter(e, 'A');
            break;
        case 'W':
            p.movePotter(e, 'W');

            break;
        case 'S':
            p.movePotter(e, 'S');

            break;
        case 'D':
            p.movePotter(e, 'D');

            break;
        case 'Q':
            p.movePotter(e, 'Q');

            break;
        }
        if (ch == 'E')
            break;
    }

    return 0;
}