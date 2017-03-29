#define USEDEBUG

#ifdef USEDEBUG
#define D(x)    cout << x << endl
#define printMap    for(i = 0; i < 44; i++) {   for(j = 0; j < 52; j++) cout << map[i][j];  cout << endl;}
#define printHand   for(i = 0; i < 4; i++)  cout << hand[i].get_id(); cout << endl;
#else
#define D(x)
#define printMap
#define printHand
#endif

//Standard includes
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <random>
#include <time.h>

//Custom includes
#include "troop.h" //includes <string>
#include "point.h"

using namespace std;

bool troopCompareStrenght(Troop t1, Troop t2);

int main()
{
    //random number generation
    unsigned seed = time(NULL);
    default_random_engine rng(seed);
    uniform_int_distribution<int> spawn_cnt(0, 5);  //range for random number engine, from 0 to last index of spawn_points

    int i;
    int timeLeft;
    int mana;
    Troop hand[4];
    vector<Troop> enemyTroops;
    vector<Troop> myTroops;
    point spawn;

    point spawnPoints[] = {{3, 22}, {8, 22}, {13, 22}, {18, 22}, {5, 12}, {16, 12}};

    Troop allTroops[] = {{1, 5, 3, 50, 3, 1500}, {2, 3, 2, 50, 5, 700}, {3, 4, 4, 150, 3, 500},
                         {4, 7, 2, 10, 2, 3000}, {5, 1, 3, 10, 4, 300}, {6, 4, 3, 100, 5, 300},
                         {7, 9, 1, 100, 2, 2500}, {8, 5, 1, 200, 2, 1500}};

    //Change this line if more troops are addded
    //vector<Troop> deck (allTroops, allTroops + sizeof(allTroops)/sizeof(allTroops[0]));

    //Select the Troops to use (first 4 will be in hand at start)
    cout << "1 2 3 4 5 6 7 8" << endl;

    //Game Loop
    while(true)
    {
        //Read the game status from server
        string rawInput;

        int troopIdx[4];   //First line will contain {time left, current mana, Troops in hand}
        cin >> timeLeft >> mana >> troopIdx[0] >> troopIdx[1] >> troopIdx[2] >> troopIdx[3];
        getline(cin, rawInput); //flush cin buffer


        string map[44];     //map contains the game map drawn two times. The first time showing the Troops' position indicated with their ids. The second time showing their remaining hp
        for(i = 0; i < 44; i++) {       //first map from 0 to 21. Second part from 22 to 43
            getline(cin, rawInput);
            map[i] = rawInput;
        }

        //Proccess the inputed data
        //Get information from the first line
        hand[0] = allTroops[troopIdx[0] - 1];
        hand[1] = allTroops[troopIdx[1] - 1];
        hand[2] = allTroops[troopIdx[2] - 1];
        hand[3] = allTroops[troopIdx[3] - 1];

        //Order Topps in hand by strenght
        sort(hand, hand+4, troopCompareStrenght);
/*
        //Get map information
        enemyTroops = trackEnemies(map, enemyTroops, timeLeft);
        myTroops = trackAllies(map, myTroops, timeLeft);
*/

        //Invoke the all posible Troops
        for(i = 0; i < 4; i++) {
            if(mana >= hand[i].get_cost()){
                spawn = spawnPoints[spawn_cnt(rng)];
                cout << "1 " << hand[i].get_id() << " " << spawn.x << " " << spawn.y << endl;
                mana -= hand[i].get_cost();
            }
        }

        cout << "0" << endl;

    }

    return 0;
}

//returns true if t1 is stronger than t2
bool troopCompareStrenght(Troop t1, Troop t2)
{
    return t1.get_risk() > t2.get_risk();
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
