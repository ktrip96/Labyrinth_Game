#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <stdlib.h>

using namespace std;

#define MAX_MAP_LENGTH 500

class Engine
{
    // χειρισμός χάρτη (στον constructor)
    // υπολογισμός score
protected:
    /**  -1, * ===> τοίχος
     *    0,  ===> δρόμος
     *    1, @ ===> πετράδια + περγαμηνή
     *    2, $ ===> τέρας
     *    3, # ===> player
     **/
    vector<vector<pair<char, int>>> Labyrinth;
    pair<int, int> PotterCoords;
    int gemCounter = 0;

public:
    friend class Moving;
    friend class Potter;
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
            cout << "*** Dear Summoner welcome to the Labyrinth Game ***" << endl;
            // διάβασμα αρχείου
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

            // Δημιούργησε random συντεταγμένες για τον παίκτη μας και τα πετράδια
            randomizeLabyrith();
        }
        my_file.close();
    }

    // η randomCoordPair αναπαράγει τυχαία ζευγάρια, στο μέγεθος του λαβυρίνθου

    pair<int, int> randomCoordPair()
    {
        int i = rand() % Labyrinth.size();
        int j = rand() % Labyrinth[0].size();

        return make_pair(i, j);
    }

    //

    pair<int, int> validPair()
    {
        pair<int, int> temp;
        temp = randomCoordPair();
        // όσο οι συντεταγμένες που μου έδωσες πέφτουν σε άλλο αντικείμενο εκτός από δρόμο
        // ξαναδώσε μου άλλες random συντεταγμένες.
        while (Labyrinth[temp.first][temp.second].second != 0)
        {
            temp = randomCoordPair();
        }
        return temp;
    }

    //  η randomizeLabyrinth παράγει τις τυχαίες θέσεις για τα αντικείμενά μας.

    void randomizeLabyrith()
    {
        int gemsCounter = 0;
        pair<int, int> temp;
        // αρχικοποίησε τα πετράδια
        while (gemsCounter < 10)
        {
            temp = validPair();
            Labyrinth[temp.first][temp.second].second = 1;
            Labyrinth[temp.first][temp.second].first = '@';

            gemsCounter++;
        }

        temp = validPair();
        Labyrinth[temp.first][temp.second].second = 3;
        Labyrinth[temp.first][temp.second].first = '#';
        PotterCoords = temp;
    }

    // συνάρτηση που θα εκτυπώνει τον λαβύρινθο στην οθόνη

    void renderLabyrinth()
    {
        cout << "Labyrinth with Symbols " << endl;
        for (int i = 0; i < Labyrinth.size(); i++)
        {
            for (int j = 0; j < Labyrinth[i].size(); j++)
            {
                cout << Labyrinth[i][j].first << " ";
            }
            cout << endl;
        }
        // cout << "Labyrinth with Numbers " << endl;

        // for (int i = 0; i < Labyrinth.size(); i++)
        // {
        //     for (int j = 0; j < Labyrinth[i].size(); j++)

        //     {

        //         if (Labyrinth[i][j].second != -1)
        //             cout << " " << Labyrinth[i][j].second << " ";
        //         else
        //             cout << Labyrinth[i][j].second << " ";
        //     }
        //     cout << endl;
        // }
    }

    // συνάρτηση, που θα εκτυπώνει τον αριθμό των σμαραγιών
    void printGems()
    {
        cout << "Current numbers of gathered gems :" << gemCounter << endl;
    }
};

class Moving
{

public:
    Moving()
    {
    }
};

class Potter : public Moving
{
public:
    void movePotter(Engine &e, char destination)
    {
        cout << "PotterCoords are currently:" << e.PotterCoords.first << " " << e.PotterCoords.second << endl;
        int i = e.PotterCoords.first;
        int j = e.PotterCoords.second;
        // τσέκαρε αν υπάρχει δρόμος, εκεί που πάει ο χρήστης
        // αν υπάρχει, τότε άλλαξε την καινούργια τοποθεσία του χρήστη
        // αν στην καινούργια τοποθεσία, έχει διαμάντι, τότε αύξησε το gemCounter κατά 1.
        // κάνε update την παλιά τοποθεσία (εκεί που είχε #, βάλε δρόμο, κενό δηλαδή)
        switch (destination)
        {
        case 'A':
            if (e.Labyrinth[i][j - 1].second == -1)
                cout << "You can't walk into a wall. Please choose another move" << endl;
            else
            {
                e.PotterCoords.second--;
                if (e.Labyrinth[i][j - 1].second == 1)
                {
                    e.gemCounter++;
                }
                e.Labyrinth[i][j - 1].first = '#';
                e.Labyrinth[i][j - 1].second = '3';
                e.Labyrinth[i][j].first = ' ';
                e.Labyrinth[i][j].second = '0';
            }
            break;
        case 'W':
            if (e.Labyrinth[i - 1][j].second == -1)
                cout << "You can't walk into a wall. Please choose another move" << endl;
            else
            {
                e.PotterCoords.first--;
                if (e.Labyrinth[i - 1][j].second == 1)
                {
                    e.gemCounter++;
                }
                e.Labyrinth[i - 1][j].first = '#';
                e.Labyrinth[i - 1][j].second = '3';
                e.Labyrinth[i][j].first = ' ';
                e.Labyrinth[i][j].second = '0';
            }

            break;
        case 'S':
            if (e.Labyrinth[i + 1][j].second == -1)
                cout << "You can't walk into a wall. Please choose another move" << endl;
            else
            {
                e.PotterCoords.first++;
                if (e.Labyrinth[i + 1][j].second == 1)
                {
                    e.gemCounter++;
                }
                e.Labyrinth[i + 1][j].first = '#';
                e.Labyrinth[i + 1][j].second = '3';
                e.Labyrinth[i][j].first = ' ';
                e.Labyrinth[i][j].second = '0';
            }

            break;
        case 'D':
            if (e.Labyrinth[i][j + 1].second == -1)
                cout << "You can't walk into a wall. Please choose another move" << endl;
            else
            {
                e.PotterCoords.second++;
                if (e.Labyrinth[i][j + 1].second == 1)
                {
                    e.gemCounter++;
                }
                e.Labyrinth[i][j + 1].first = '#';
                e.Labyrinth[i][j + 1].second = '3';
                e.Labyrinth[i][j].first = ' ';
                e.Labyrinth[i][j].second = '0';
            }

            break;
        case 'Q':
            break;
        }
    }
};