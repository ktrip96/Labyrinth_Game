#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

#define MAX_MAP_LENGTH 500

class Engine
{
    // χειρισμός χάρτη (στον constructor)
    // υπολογισμός score
protected:
    /**  -1 ===> τοίχος
     *    0 ===> δρόμος
     *    1 ===> πετράδια + περγαμηνή
     *    2 ===> τέρας
     *    3 ===> player
     **/
    vector<vector<pair<char, int>>> Labyrinth;

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
                vector<pair<char, int>> temp;
                for (int i = 0; i < MAX_MAP_LENGTH; i++)
                {
                    // αν συναντήσεις το τέλος γραμμής, τότε βγες από την επανάληψη
                    if (row[i] == '\0')
                    {
                        break;
                    }
                    else if (row[i] == '*')
                    {
                        // o τοίχος συμβολίζεται με -1
                        temp.push_back(make_pair(row[i], -1));
                    }
                    else
                    {
                        // ο δρόμος συμβολίζεται με 0
                        temp.push_back(make_pair(row[i], 0));
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
        cout << "*** Labyrinth with Symbols *** " << endl;
        for (int i = 0; i < Labyrinth.size(); i++)
        {
            for (int j = 0; j < Labyrinth[i].size(); j++)
            {
                cout << Labyrinth[i][j].first << " ";
            }
            cout << endl;
        }
        cout << "*** Labyrinth with Numbers *** " << endl;

        for (int i = 0; i < Labyrinth.size(); i++)
        {
            for (int j = 0; j < Labyrinth[i].size(); j++)
            {
                if (Labyrinth[i][j].second == 0)
                    cout << " " << Labyrinth[i][j].second << " ";
                else
                    cout << Labyrinth[i][j].second << " ";
            }
            cout << endl;
        }
    }
};