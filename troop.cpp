#include "troop.h"

//Constructors
Troop::Troop()
{
    name = "";
    faction = "";
    id = 0;
    cost = 0;
    speed = 0;
    attack = 0;
    range = 0;
    hp_max = 0;
    riskMultiplier = 0;

    set_hp_current(hp_max);
    set_risk(riskMultiplier * hp_current);

}

Troop::Troop(std::string str, std::string f, int n, int c, int s, int a, int r, int h) {
    name = str;
    faction = f;
    id = n;
    cost = c;
    speed = s;
    attack = a;
    range = r;
    hp_max = h;
    riskMultiplier = attack * speed / range;

    set_hp_current(hp_max);
    set_risk(riskMultiplier * hp_current);
}

//getters
std::string Troop::get_name() {
    return name;
}

std::string Troop::get_faction() {
    return faction;
}

int Troop::get_id() {
    return id;
}

int Troop::get_cost() {
    return cost;
}

int Troop::get_speed() {
    return speed;
}

int Troop::get_attack() {
    return attack;
}

int Troop::get_range() {
    return range;
}

int Troop::get_hp_max() {
    return hp_max;
}

int Troop::get_hp_current() {
    return hp_current;
}

float Troop::get_riskMultiplier() {
    return riskMultiplier;
}

float Troop::get_risk() {
    return risk;
}

point Troop::get_pos() {
    return pos;
}

//setters
void Troop::set_hp_current(int value) {
    hp_current = value;
    set_risk(riskMultiplier * hp_current);
}

void Troop::set_risk(float value) {
    risk = value;
}

void Troop::set_pos(int x, int y) {
    pos.x = x;
    pos.y = y;
}
