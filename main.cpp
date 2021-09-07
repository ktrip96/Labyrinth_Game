#include <iostream>
#include "Engine.h"

using namespace std;

// χρησιμοποιώ τα argc και argv, για να διαβάσω το αρχείο με τον χάρτη από το terminal

int main(int argc, char **argv)
{
    Engine e(argc, argv);
    // e.renderLabyrinth();
    Potter p;
    Traal t;
    Gnome g;

    char ch;
    while (1)
    {
        if (e.returnisFoundPergamini())
        {
            return 0;
        }
        if (e.returnIsHarryAlive())
        {
            cout << "Harry Potter, the boy who lived, come to die" << endl;
            return 0;
        }
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
        // uncomment the following line, if you want 2 monsters on the field
        // t.move(e, "Traal");
        g.move(e, "Gnome");
    }

    return 0;
}