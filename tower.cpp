#include "tower.h"

tower::tower()
{
    rank = 0;
    hp_max = 0;
    hp_current = 0;
    attack = 0;
    range = 0;
    pos_avg.x = (pos[0].x + pos[1].x + pos[2].x + pos[3].x) / 4;
    pos_avg.y = (pos[0].y + pos[1].y + pos[2].y + pos[3].y) / 4;

    riskMultiplier = attack * range / 100;

    set_hp_current(hp_max);
}

tower::tower(int n, bool e)
{
    rank = n;
    isEnemy = e;

    switch(rank)
    {
    case 1:
        hp_max = 5000;
        hp_current = hp_max;
        attack = 50;
        range = 5;
        pos[0] = point(8, 3); pos[1] = point(8, 8); pos[2] = point(13, 3); pos[3] = point(13, 8);
        break;
     case 2:
        hp_max = 4000;
        hp_current = hp_max;
        attack = 40;
        range = 5;
        pos[0] = point(3, 7);pos[1] = point(3, 10); pos[2] = point(6, 7); pos[3] = point(6, 10);
        break;
    case 3:
        hp_max = 4000;
        hp_current = hp_max;
        attack = 40;
        range = 5;
        pos[0] = point(15, 7); pos[1] = point(15, 10); pos[2] = point(18, 7); pos[3] = point(18, 10);
        break;
    default:
        hp_max = 0;
        hp_current = 0;
        attack = 0;
        range = 0;
        break;
    }

    int offset;
    if(isEnemy && rank == 1)
        offset = 40;
    else
        offset = 34;

    for(int i = 0; i < 4 && isEnemy; i++)
        pos[i].y += offset;

    pos_avg.x = (pos[0].x + pos[1].x + pos[2].x + pos[3].x) / 4;
    pos_avg.y = (pos[0].y + pos[1].y + pos[2].y + pos[3].y) / 4;

    riskMultiplier = attack * range / 100;

    set_hp_current(hp_max);
}

int tower::get_hp_max()
{
    return hp_max;
}

int tower::get_hp_current()
{
    return hp_current;
}

int tower::get_attack()
{
    return attack;
}

int tower::get_range()
{
    return range;
}

int tower::get_rank()
{
    return rank;
}

point tower::get_pos_avg()
{
    return pos_avg;
}

void tower::set_hp_current(char value)
{
    switch(value)
    {
    case '1':
        hp_current = hp_max * 5 / 100;
        break;
    case '2':
        hp_current = hp_max * 15 / 100;
        break;
    case '3':
        hp_current = hp_max * 25 / 100;
        break;
    case '4':
        hp_current = hp_max * 35 / 100;
        break;
    case '5':
        hp_current = hp_max * 45 / 100;
        break;
    case '6':
        hp_current = hp_max * 55 / 100;
        break;
    case '7':
        hp_current = hp_max * 65 / 100;
        break;
    case '8':
        hp_current = hp_max * 75 / 100;
        break;
    case '9':
        hp_current = hp_max * 85 / 100;
        break;
    case 'A':
        hp_current = hp_max * 100 / 100;
        break;
    default:
        hp_current = 0;
        break;
    }

    set_risk(riskMultiplier * hp_current);
}

double tower::get_risk()
{
    return risk;
}

void tower::set_risk(double r)
{
    risk = r;
}
