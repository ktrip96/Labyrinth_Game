#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAX_MAP_LENGTH 500

class Engine
{
    // χειρισμός χάρτη (στον constructor)
    // υπολογισμός score
protected:
    vector<vector<char>> Labyrinth;

public:
    // constructor
    Engine(int argc, char **argv)
    {
        ifstream my_file;
        char row[MAX_MAP_LENGTH];
        my_file.open(argv[1]);
        if (!my_file)
        {
            cout << "No such file" << endl;
            // εδώ μπορώ να πετάξω και ένα exception
        }
        else
        {
            while (my_file.getline(row, MAX_MAP_LENGTH))
            {
                vector<char> temp;
                for (int i = 0; i < MAX_MAP_LENGTH; i++)
                {
                    // αν συναντήσεις το τέλος γραμμής, τότε βγες από την επανάληψη
                    if (row[i] == '\0')
                    {
                        break;
                    }
                    else
                    {
                        temp.push_back(row[i]);
                    }
                }
                Labyrinth.push_back(temp);
            }
        }
        my_file.close();
    }

    // συνάρτηση που θα εκτυπώνει τον λαβύρινθο στην οθόνη

    void renderLabyrinth()
    {
        for (int i = 0; i < Labyrinth.size(); i++)
        {
            for (int j = 0; j < Labyrinth[i].size(); j++)
            {
                cout << Labyrinth[i][j] << " ";
            }
            cout << endl;
        }
    }
};