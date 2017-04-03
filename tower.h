#ifndef TOWER_H
#define TOWER_H

#include <string>
#include "point.h"

class tower
{
public:
    tower();
    tower(int n, bool e);

    int get_hp_max();
    int get_hp_current();
    int get_range();
    int get_attack();
    point get_pos_avg();
    int get_rank();
    double get_risk();

    void set_hp_current(char value);
    void set_risk(double r);

    bool isEnemy = false;

private:
    int hp_max;
    int hp_current;
    int range;
    int attack;
    point pos[4];
    point pos_avg;
    int rank;
    double riskMultiplier;
    double risk;
};

#endif // TOWER_H
