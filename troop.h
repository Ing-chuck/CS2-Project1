#ifndef TROOP_H
#define TROOP_H
#include <string>
#include "point.h"

class Troop
{
public:
    Troop();
    Troop(std::string str, std::string f, int n, int c, int s, int a, int r, int h);

    std::string get_name();
    std::string get_faction();
    int get_id();
    int get_cost();
    int get_speed();
    int get_attack();
    int get_range();
    int get_hp_max();
    int get_hp_current();
    float get_riskMultiplier();
    float get_risk();
    point get_pos();

    void set_hp_current(int value);
    void set_risk(float value);
    void set_pos(int x, int y);

private:
    std::string name;
    std::string faction;
    int id;
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
