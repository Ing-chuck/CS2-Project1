//#define USEDEBUG

#ifdef USEDEBUG
#define D(x)    cout << x << endl
#define printMap    for(i = 0; i < 44; i++) {   for(j = 0; j < 52; j++) cout << map[i][j];  cout << endl;}
#else
#define D(x)
#define printMap
#endif

//Standard includes
#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <time.h>

//Custom includes
#include "troop.h" //includes <string>
#include "point.h"

using namespace std;

int main()
{
    //random number generation
    unsigned seed = time(NULL);
    default_random_engine rng(seed);
    uniform_int_distribution<int> spawn_cnt(0, 5);  //range for random number engine, from 0 to last index of spawn_points

    int i, j;
    int timeLeft;
    int mana;
    Troop hand[4];
    vector<Troop> enemyTroops;
    vector<Troop> myTroops;
    point spawn;

    point spawnPoints[] = {{3, 22}, {8, 22}, {13, 22}, {18, 22}, {5, 4}, {16, 4}};

    Troop allTroops[] = {{"Knight", "Human", 1, 5, 3, 50, 3, 1500}, {"Priest", "Human", 2, 3, 2, 50, 5, 700}, {"Assassin", "Human", 3, 4, 4, 150, 3, 500},
                         {"Rock Giant", "Elf", 4, 7, 2, 10, 2, 3000}, {"Wisp", "Elf", 5, 1, 3, 10, 4, 300}, {"Archer", "Elf", 6, 4, 3, 100, 5, 300},
                         {"Samurai", "Undead", 7, 9, 1, 100, 2, 2500}, {"Sgram", "Siege", 8, 5, 1, 200, 2, 1500}};

    //Change this line if more troops are addded
    //vector<Troop> deck (allTroops, allTroops + sizeof(allTroops)/sizeof(allTroops[0]));

    //Select the Troops to use (first 4 will be in hand at start)
    cout << "1 2 3 4 5 6 7 8" << endl;

    //Game Loop
    do
    {
        //Read the game status from server
        string rawInput;

        int troopIdx[4];   //First line will contain {time left, current mana, Troops in hand}
        cin >> timeLeft >> mana >> troopIdx[0] >> troopIdx[1] >> troopIdx[2] >> troopIdx[3];


        char map[44][53];     //map contains the game map drawn two times. The first time showing the Troops' position indicated with their ids. The second time showing their remaining hp
        for(i = 0; i < 44; i++) {       //first map from 0 to 21. Second part from 22 to 43
            getline(cin, rawInput);
            for(j = 0; j < (signed)rawInput.length() && j < 53; j++) {
                map[i][j] = rawInput[j];
                j++;
            }
        }

        D("");
        printMap

        //Proccess the inputed data
        //Get information from the first line
        hand[0] = allTroops[troopIdx[0] - 1];
        hand[1] = allTroops[troopIdx[1] - 1];
        hand[2] = allTroops[troopIdx[2] - 1];
        hand[3] = allTroops[troopIdx[3] - 1];
/*
        //Get map information
        enemyTroops = trackEnemies(map, enemyTroops, timeLeft);
        myTroops = trackAllies(map, myTroops, timeLeft);
*/
        //Order Topps in hand by strenght
        for(i = 1; i < 4; i++) {
            Troop x = hand[i];
            j = i - 1;
            while(j >= 0 && x.get_risk() > hand[j].get_risk()) {
                hand[j+1] = hand[j];
                j--;
            }
            hand[j] = x;
        }

        //Invoke the all posible Troops
        for(i = 0; i < 4; i++) {
            if(mana > hand[i].get_cost()){
                spawn = spawnPoints[spawn_cnt(rng)];
                cout << "1 " << hand[i].get_id() << " " << spawn.x << " " << spawn.y << endl;
                mana -= hand[i].get_cost();
            }
        }

        cout << "0" << endl;

    }while(timeLeft > 0);

    return 0;
}
/*
///Return vector containing enemy troops found in the map, uses an old version of said vector and time to track movement
vector<Troop> trackEnemies(vector<vector<string>> map, vector<Troop> old, int time) {
    return old;
}

///Return vector containing friendly troops found in the map, uses an old version of said vector and time to track movement
vector<Troop> trackAllies(vector<vector<string>> map, vector<Troop> old, int time) {
    return old;
}
*/
