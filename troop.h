#ifndef TROOP_H
#define TROOP_H
#include <string>
#include "point.h"

class Troop
{
public:
    Troop();
    Troop(int n);

    std::string get_name();
    char get_id();
    int get_cost();
    int get_speed();
    int get_attack();
    int get_range();
    int get_hp_max();
    int get_hp_current();
    float get_riskMultiplier();
    float get_risk();
    point get_pos();

    void set_hp_current(char value);
    void set_risk(float value);
    void set_pos(int x, int y);

    bool isEnemy = false;

private:
    std::string name = "";
    char id;
    int cost;
    int speed;
    int attack;
    int range;
    int hp_max;
    int hp_current;
    float riskMultiplier;
    float risk;
    point pos;
};

#endif // TROOP_H
