#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <math.h>

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
    pair<int, int> GnomeCoords;
    pair<int, int> TraalCoords;
    bool foundPergamini = false;
    bool killPotter = false;
    int gemCounter = 0;

public:
    friend class Moving;
    friend class Potter;
    friend class Gnome;
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
        Labyrinth[temp.first][temp.second].first = 'P';
        PotterCoords = temp;

        temp = validPair();
        Labyrinth[temp.first][temp.second].second = 2;
        Labyrinth[temp.first][temp.second].first = 'T';
        TraalCoords = temp;

        temp = validPair();
        Labyrinth[temp.first][temp.second].second = 2;
        Labyrinth[temp.first][temp.second].first = 'G';
        GnomeCoords = temp;
    }

    void randomizePergamini()
    {
        pair<int, int> temp;
        temp = validPair();
        Labyrinth[temp.first][temp.second].second = 4;
        Labyrinth[temp.first][temp.second].first = '!';
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
        // For Developing purposes
        // cout << "Labyrinth with Numbers" << endl;

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

    bool returnisFoundPergamini()
    {
        return foundPergamini;
    }

    bool returnIsHarryAlive()
    {
        return killPotter;
    }
};

class Moving
{

public:
    Moving()
    {
    }

    double returnDistance(int a, int b, int c, int d)
    {
        return sqrt(pow((c - a), 2) + pow((d - b), 2));
    }

    void move(Engine &e, string S)
    {
        int i = (S == "Traal") ? e.TraalCoords.first : e.GnomeCoords.first;
        int j = (S == "Traal") ? e.TraalCoords.second : e.GnomeCoords.second;
        int k = e.PotterCoords.first;
        int l = e.PotterCoords.second;
        double min = 1000000000;
        char destination = 'Z';
        // η ευριστική που χρησιμοποιείται, έχει να κάνει με την ευκλείδια απόσταση του τέρατος από τον Potter
        // αν μπορείς να πας && η διαδρομή είναι πιο σύντομη από εσένα,
        // τότε θα πάμε από εσένα.
        if (e.Labyrinth[i][j - 1].second != -1 && returnDistance(i, j - 1, k, l) < min)
        {
            destination = 'A';
            min = returnDistance(i, j - 1, k, l);
        }
        if (e.Labyrinth[i][j + 1].second != -1 && returnDistance(i, j + 1, k, l) < min)
        {
            destination = 'D';
            min = returnDistance(i, j + 1, k, l);
        }
        if (e.Labyrinth[i - 1][j].second != -1 && returnDistance(i - 1, j, k, l) < min)
        {
            destination = 'W';
            min = returnDistance(i - 1, j, k, l);
        }
        if (e.Labyrinth[i + 1][j].second != -1 && returnDistance(i + 1, j, k, l) < min)
        {
            destination = 'S';
            min = returnDistance(i + 1, j, k, l);
        }

        switch (destination)
        {
            // α) 'Άλλαξε τις καινούργιες συντεταγμένες
            // β) Κάνε update τις παλιές, και βάλτους δρόμο
            // γ) ενημέρωσε τις συντεταγμένες του τέρατος
        case 'A':
            if (e.Labyrinth[i][j - 1].first == 'P')
                e.killPotter = true;
            e.Labyrinth[i][j - 1].first = (S == "Traal") ? 'T' : 'G';
            e.Labyrinth[i][j - 1].second = '2';
            e.Labyrinth[i][j].first = ' ';
            e.Labyrinth[i][j].second = '0';
            (S == "Traal") ? e.TraalCoords.second-- : e.GnomeCoords.second--;
            break;
        case 'S':
            if (e.Labyrinth[i + 1][j].first == 'P')
                e.killPotter = true;

            e.Labyrinth[i + 1][j].first = (S == "Traal") ? 'T' : 'G';
            e.Labyrinth[i + 1][j].second = '2';

            e.Labyrinth[i][j].first = ' ';
            e.Labyrinth[i][j].second = '0';
            (S == "Traal") ? e.TraalCoords.first++ : e.GnomeCoords.first++;
            break;
        case 'D':
            if (e.Labyrinth[i][j + 1].first == 'P')
                e.killPotter = true;
            e.Labyrinth[i][j + 1].first = (S == "Traal") ? 'T' : 'G';
            e.Labyrinth[i][j + 1].second = '2';

            e.Labyrinth[i][j].first = ' ';
            e.Labyrinth[i][j].second = '0';
            (S == "Traal") ? e.TraalCoords.second++ : e.GnomeCoords.second++;
            break;
        case 'W':
            if (e.Labyrinth[i - 1][j].first == 'P')
                e.killPotter = true;

            e.Labyrinth[i - 1][j].first = (S == "Traal") ? 'T' : 'G';
            e.Labyrinth[i - 1][j].second = '2';

            e.Labyrinth[i][j].first = ' ';
            e.Labyrinth[i][j].second = '0';
            (S == "Traal") ? e.TraalCoords.first-- : e.GnomeCoords.first--;
            break;

        case 'Z':
            cout << "error at finding optimum solution" << endl;
            break;
        }
    }
};

class Potter : public Moving
{
public:
    void movePotter(Engine &e, char destination)
    {
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
            else if (e.Labyrinth[i][j - 1].second == 4)
            {
                cout << "Congratulations! You are free to graduate from the school!!!" << endl;
                e.foundPergamini = true;
                return;
            }
            else
            {
                e.PotterCoords.second--;
                if (e.Labyrinth[i][j - 1].second == 1)
                {
                    e.gemCounter++;
                    if (e.gemCounter == 10)
                        e.randomizePergamini();
                }
                e.Labyrinth[i][j - 1].first = 'P';
                e.Labyrinth[i][j - 1].second = '3';
                e.Labyrinth[i][j].first = ' ';
                e.Labyrinth[i][j].second = '0';
            }
            break;
        case 'W':
            if (e.Labyrinth[i - 1][j].second == -1)
                cout << "You can't walk into a wall. Please choose another move" << endl;
            else if (e.Labyrinth[i - 1][j].second == 4)
            {
                cout << "Congratulations! You are free to graduate from the school!!!" << endl;
                e.foundPergamini = true;

                return;
            }
            else
            {
                e.PotterCoords.first--;
                if (e.Labyrinth[i - 1][j].second == 1)
                {
                    e.gemCounter++;
                    if (e.gemCounter == 10)
                        e.randomizePergamini();
                }
                e.Labyrinth[i - 1][j].first = 'P';
                e.Labyrinth[i - 1][j].second = '3';
                e.Labyrinth[i][j].first = ' ';
                e.Labyrinth[i][j].second = '0';
            }

            break;
        case 'S':
            if (e.Labyrinth[i + 1][j].second == -1)
                cout << "You can't walk into a wall. Please choose another move" << endl;
            else if (e.Labyrinth[i + 1][j].second == 4)
            {
                cout << "Congratulations! You are free to graduate from the school!!!" << endl;
                e.foundPergamini = true;

                return;
            }
            else
            {
                e.PotterCoords.first++;
                if (e.Labyrinth[i + 1][j].second == 1)
                {
                    e.gemCounter++;
                    if (e.gemCounter == 10)
                        e.randomizePergamini();
                }
                e.Labyrinth[i + 1][j].first = 'P';
                e.Labyrinth[i + 1][j].second = '3';
                e.Labyrinth[i][j].first = ' ';
                e.Labyrinth[i][j].second = '0';
            }

            break;
        case 'D':
            if (e.Labyrinth[i][j + 1].second == -1)
                cout << "You can't walk into a wall. Please choose another move" << endl;
            else if (e.Labyrinth[i][j + 1].second == 4)
            {
                cout << "Congratulations! You are free to graduate from the school!!!" << endl;
                e.foundPergamini = true;

                return;
            }
            else
            {
                e.PotterCoords.second++;
                if (e.Labyrinth[i][j + 1].second == 1)
                {
                    e.gemCounter++;
                    if (e.gemCounter == 10)
                        e.randomizePergamini();
                }
                e.Labyrinth[i][j + 1].first = 'P';
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

class Gnome : public Moving
{
public:
    Gnome()
    {
        cout << "Gnome has been spawned" << endl;
    }
};

class Traal : public Moving
{
public:
    Traal()
    {
        cout << "Traal has been spawned" << endl;
    }
};