#include <iostream>
#include "Engine.h"

using namespace std;

// χρησιμοποιώ τα argc και argv, για να διαβάσω το αρχείο με τον χάρτη από το terminal

int main(int argc, char **argv)
{
    Engine e(argc, argv);
    e.renderLabyrinth();
    return 0;
}