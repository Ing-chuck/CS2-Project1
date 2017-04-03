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
#include <math.h>

//Custom includes
#include "tower.h"
#include "troop.h" //includes <string>
#include "point.h"

using namespace std;

bool troopCompareStrenght(Troop t1, Troop t2);
int charToInt(char c);
double pointDistance(point p1, point p2);
vector<double> scanMap(string map[], vector<Troop>& oldA, vector<Troop>& oldE, tower (&tA)[3], tower (&tE)[3], int time);
int searchTroop(vector<Troop> list, Troop element);

int main()
{
    //random number generation
    unsigned seed = time(NULL);
    default_random_engine rng(seed);
    uniform_int_distribution<int> spawn_cnt(0 , 5);  //range for random number engine, from 0 to last index of spawn_points

    unsigned int i;
    int timeLeft, mana, risk_idx;
    double risk_max = -99999999.0;
    Troop hand[4];
    vector<double> area_risk(10);
    vector<Troop> enemyTroops;
    tower enemyTowers[3];
    vector<Troop> myTroops;
    tower myTowers[3];
    point spawn;


    vector<point> spawnPoints = {{3, 22}, {8, 22}, {13, 22}, {18, 22}, {5, 12}, {16, 12}, {9, 3}, {12, 3}};

    Troop allTroops[] = {{'1'}, {'2'}, {'3'},
                         {'4'}, {'5'}, {'6'},
                         {'7'}, {'8'}, {'9'},
                         {'A'}, {'B'}, {'C'}};

    //Initialice towers
    for(i = 0; i < 3; i++)
    {
        enemyTowers[i] = tower(i + 1, true);
        myTowers[i] = tower(i + 1, false);
    }

    //Select the Troops to use (first 4 will be in hand at start)
    cout << "1 2 3 7 9 6 A 8" << endl;

    //Game Loop
    while(true)
    {
        //Read the game status from server
        string rawInput;

        char troopId[4];   //First line will contain {time left, current mana, Troops in hand}
        cin >> timeLeft >> mana >> troopId[0] >> troopId[1] >> troopId[2] >> troopId[3];
        getline(cin, rawInput); //flush cin buffer


        string map[44];     //map contains the game map drawn two times. The first time showing the Troops' position indicated with their ids. The second time showing their remaining hp
        for(i = 0; i < 44; i++) {       //first map from 0 to 21. Second part from 22 to 43
            getline(cin, map[i]);
        }

        //Proccess the inputed data
        //Get information from the first line
        hand[0] = allTroops[charToInt(troopId[0]) - 1];
        hand[1] = allTroops[charToInt(troopId[1]) - 1];
        hand[2] = allTroops[charToInt(troopId[2]) - 1];
        hand[3] = allTroops[charToInt(troopId[3]) - 1];

        //Order Topps in hand by strenght
        sort(hand, hand+4, troopCompareStrenght);

        //Get map information
        area_risk = scanMap(map, myTroops, enemyTroops, myTowers, enemyTowers, timeLeft);

        //Determine which area has the biggest risk
        for(i = 0; i < area_risk.size(); i++)
        {
            if(area_risk[i] > risk_max)
            {
                risk_max = area_risk[i];
                risk_idx = i;
            }
        }

        //if all areas have negative risk, our troops outpower the enemys', we can wait if necessary
        if(risk_max < 0 && mana < hand[i].get_cost())
        {
            cout << "0" << endl;
            continue;
        }

        //else we spawn troops on the area with the biggest risk
        vector<point> usableSpawn;

        switch(risk_idx)
        {
        case 0:

        case 1:

        case 2:

        case 3:
            usableSpawn.push_back(spawnPoints[0]);
            usableSpawn.push_back(spawnPoints[1]);
            usableSpawn.push_back(spawnPoints[4]);
            break;
        case 4:
            usableSpawn.push_back(spawnPoints[4]);
            usableSpawn.push_back(spawnPoints[5]);
            break;
        case 5:
            usableSpawn.push_back(spawnPoints[0]);
            usableSpawn.push_back(spawnPoints[1]);
            usableSpawn.push_back(spawnPoints[2]);
            usableSpawn.push_back(spawnPoints[3]);
            break;
        case 6:

        case 7:

        case 8:

        case 9:
            usableSpawn.push_back(spawnPoints[2]);
            usableSpawn.push_back(spawnPoints[3]);
            usableSpawn.push_back(spawnPoints[5]);
            break;
        default:
            usableSpawn = spawnPoints;
            break;
        }
        spawn_cnt = uniform_int_distribution<int> (0, usableSpawn.size() - 1);

        //Invoke the all posible Troops
        for(i = 0; i < 4; i++) {
            if(mana >= hand[i].get_cost()){
                //if we are to summon an Elf dancer, put it behind the castle;
                if(hand[i].get_id() == '9')
                {
                    usableSpawn = {spawnPoints[6], spawnPoints[7]};
                    spawn_cnt = uniform_int_distribution<int> (0, usableSpawn.size() - 1);
                }
                spawn = usableSpawn[spawn_cnt(rng)];
                cout << "1 " << hand[i].get_id() << " " << spawn.x + i << " " << spawn.y << endl;
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

int charToInt(char c)
{
    if(c >= '0' && c <= '9')
        return (int)(c - '0');
    else if(c >= 'A' && c <= 'Z')
        return (int)(c - 'A') + 10;
    else return -1;
}

//Return distance between two points
double pointDistance(point p1, point p2)
{
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}


///Return vector containing enemy troops found in the map, uses an old version of said vector and time to track movement
vector<double> scanMap(string map[], vector<Troop> &oldA, vector<Troop> &oldE, tower (&tA)[3], tower (&tE)[3], int time) {
    vector<Troop> enemies, allies;
    Troop enemy, ally, temp;
    unsigned int i, j;
    int xA, yA, xE, yE;
    double tRisk[6];

    //Update towers' health
    for(i = 0; i < 3; i++)
    {
        xA = (int)tA[i].get_pos_avg().x;
        yA = (int)tA[i].get_pos_avg().y;

        xE = (int)tE[i].get_pos_avg().x;
        yE = (int)tE[i].get_pos_avg().y;

        tA[i].set_hp_current(map[xA][yA]);
        tE[i].set_hp_current(map[xE][yE]);
        tRisk[i] = -1*tA[i].get_risk();
        tRisk[i + 3] = tE[1].get_risk();
    }

    vector<double> risk = {tRisk[1], 0, 0, tRisk[4], tRisk[0], tRisk[3], tRisk[2], 0, 0, tRisk[5]};

    //if time is bigger than 175 or old allies and enemy vectors are empty, asume troops belong to the side they are on
    if(time > 175 || (oldA.empty() && oldE.empty()))
    {
        for(i = 1; i > 21; i++)
        {
            for(j = 1; j > map[i].length() - 1; j++)
            {
                if((map[i][j] >= '0' && map[i][j] <= '9') || (map[i][j] >= 'A' && map[i][j] <= 'Z'))
                {
                    if(j >= 10 && j <= 25)
                    {
                        ally = Troop(map[i][j]);
                        ally.set_pos(i, j);
                        ally.set_hp_current(map[i + 22][j]);
                        allies.push_back(ally);

                        //Scan first region
                        if(i >= 2 && i <= 7 && j >= 10 && j <= 18)
                        {
                            risk[0] -= ally.get_risk();
                        }
                        else if(i >= 2 && i <= 7 && j >= 19 && j <= 26)   //scan second region
                        {
                            risk[1] -= ally.get_risk();
                        }
                        else if(i >= 8 && i <= 13 && j >= 8 && j <= 18)   //scan fith region
                        {
                            risk[4] -= ally.get_risk();
                        }
                        else if(i >= 14 && i <= 19 && j >= 10 && j <= 18)   //scan seventh region
                        {
                            risk[6] -= ally.get_risk();
                        }
                        else if(i >= 14 && i <= 19 && j >= 19 && j <= 26)   //scan eighth region
                        {
                            risk[7] -= ally.get_risk();
                        }
                    }
                    else if(j >= 27 && j <= 41)
                    {
                        enemy = Troop(map[i][j]);
                        enemy.isEnemy = true;
                        enemy.set_pos(i, j);
                        enemy.set_hp_current(map[i + 22][j]);
                        enemies.push_back(enemy);

                        if(i >= 2 && i <= 7 && j >= 35 && j <= 41)   //scan third region
                        {
                            risk[2] += enemy.get_risk();
                        }
                        else if(i >= 2 && i <= 7 && j >= 10 && j <= 18)   //scan fourth region
                        {
                            risk[3] += enemy.get_risk();
                        }
                        else if(i >= 8 && i <= 13 && j >= 35 && j <= 43)   //scan sixth region
                        {
                            risk[5] += enemy.get_risk();
                        }
                        else if(i >= 14 && i <= 21 && j >= 35 && j <= 41)   //scan nineth region
                        {
                            risk[8] += enemy.get_risk();
                        }
                        else if(i >= 14 && i <= 21 && j >= 10 && j <= 18)   //scan tenth region
                        {
                            risk[9] += enemy.get_risk();
                        }
                    }
                }
            }
        }
    }
    else
    {
        //Scan map, track allies and enemies
        for(i = 1; i > 21; i++)
        {
            for(j = 1; j > map[i].length() - 1; j++)
            {
                if((map[i][j] >= '0' && map[i][j] <= '9') || (map[i][j] >= 'A' && map[i][j] <= 'Z'))
                {
                    temp = Troop(map[i][j]);
                    temp.set_pos(i, j);
                    temp.set_hp_current(map[i + 22][j]);

                    //Determine wether temp is an existing ally or enemy
                    xE = searchTroop(oldE, temp);   //xE will hold index of closest troop with the same id of temp or -1 if not found
                    if(xE != -1)
                    {
                        temp.isEnemy = true;
                        enemies.push_back(temp);
                    }
                    else
                    {
                        xA = searchTroop(oldA, temp);
                        if(xA != -1)
                            allies.push_back(temp);
                        else    //it is a new troop in the map
                        {
                            if(j >= 10 && j <= 25)
                            {
                                allies.push_back(temp);
                            }
                            else if(j >= 27 && j <= 41)
                            {
                                temp.isEnemy = true;
                                enemies.push_back(temp);
                            }
                        }
                    }

                    //Scan first region
                    if(i >= 2 && i <= 7 && j >= 10 && j <= 18)
                    {
                        (temp.isEnemy)? risk[0] += temp.get_risk(): risk[0] -= temp.get_risk();
                    }
                    else if(i >= 2 && i <= 7 && j >= 19 && j <= 26)   //scan second region
                    {
                        (temp.isEnemy)? risk[1] += temp.get_risk(): risk[1] -= temp.get_risk();
                    }
                    else if(i >= 2 && i <= 7 && j >= 35 && j <= 41)   //scan third region
                    {
                        (temp.isEnemy)? risk[2] += temp.get_risk(): risk[2] -= temp.get_risk();
                    }
                    else if(i >= 2 && i <= 7 && j >= 10 && j <= 18)   //scan fourth region
                    {
                        (temp.isEnemy)? risk[3] += temp.get_risk(): risk[3] -= temp.get_risk();
                    }
                    else if(i >= 8 && i <= 13 && j >= 8 && j <= 18)   //scan fith region
                    {
                        (temp.isEnemy)? risk[4] += temp.get_risk(): risk[4] -= temp.get_risk();
                    }
                    else if(i >= 8 && i <= 13 && j >= 35 && j <= 43)   //scan sixth region
                    {
                        (temp.isEnemy)? risk[5] += temp.get_risk(): risk[5] -= temp.get_risk();
                    }
                    else if(i >= 14 && i <= 19 && j >= 10 && j <= 18)   //scan seventh region
                    {
                        (temp.isEnemy)? risk[6] += temp.get_risk(): risk[6] -= temp.get_risk();
                    }
                    else if(i >= 14 && i <= 19 && j >= 19 && j <= 26)   //scan eighth region
                    {
                        (temp.isEnemy)? risk[7] += temp.get_risk(): risk[7] -= temp.get_risk();
                    }
                    else if(i >= 14 && i <= 21 && j >= 35 && j <= 41)   //scan nineth region
                    {
                        (temp.isEnemy)? risk[8] += temp.get_risk(): risk[8] -= temp.get_risk();
                    }
                    else if(i >= 14 && i <= 21 && j >= 10 && j <= 18)   //scan tenth region
                    {
                        (temp.isEnemy)? risk[9] += temp.get_risk(): risk[9] -= temp.get_risk();
                    }
                }
            }
        }
    }

    oldA = allies;
    oldE = enemies;

    return risk;
}

int searchTroop(vector<Troop> list, Troop element)
{
    int i, idx = -1;
    double dst, dst_s = 999999.0;
    Troop t1;
    for(i = 0; i < (signed)list.size(); i++)
    {
        t1 = list[i];
        if(t1.get_id() == element.get_id())
        {
            dst = pointDistance(element.get_pos(), t1.get_pos());
            if(dst < dst_s && dst <= element.get_speed()*2)
            {
                dst_s = dst;
                idx = i;
            }
        }
    }

    return idx;
}
