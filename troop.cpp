#include "troop.h"

//Constructors
Troop::Troop()
{
    id = 0;
    cost = 0;
    speed = 0;
    attack = 0;
    range = 0;
    hp_max = 0;
    riskMultiplier = 0;

    set_hp_current(hp_max);

}

Troop::Troop(int n) {
    id = n;

    switch(id)    {
    case '1':   name = "Human Knight";
                cost = 5;
                speed = 3;
                attack = 50;
                range = 3;
                hp_max = 1500;
                break;
    case '2':   name = "Human Priest";
                cost = 3;
                speed = 2;
                attack = 50;
                range = 5;
                hp_max = 700;
                break;
    case '3':    name = "Human Assassin";
                 cost = 4;
                 speed = 4;
                 attack = 150;
                 range = 3;
                 hp_max = 500;
                 break;
    case '4':   name = "Elf Giant";
                cost = 7;
                speed = 2;
                attack = 10;
                range = 2;
                hp_max = 3000;
                break;
    case '5':   name = "Elf Wisp";
                cost = 1;
                speed = 3;
                attack = 10;
                range = 4;
                hp_max = 300;
                break;
    case '6':   name = "Elf Archer";
                cost = 4;
                speed = 3;
                attack = 100;
                range = 5;
                hp_max = 300;
                break;
    case '7':   name = "Undead Samurai";
                cost = 9;
                speed = 1;
                attack = 100;
                range = 2;
                hp_max = 2500;
                break;
    case '8':   name = "Sgram";
                cost = 5;
                speed = 1;
                attack = 200;
                range = 2;
                hp_max = 1500;
                break;
    case '9':   name = "Elf Dancer";
                cost = 5;
                speed = 3;
                attack = 1;
                range = 0;
                hp_max = 1000;
                break;
    case 'A':   name = "Human Piper";
                cost = 5;
                speed = 3;
                attack = 2;
                range = 3;
                hp_max = 200;
                break;
    case 'B':   name = "Undead Alchemist";
                cost = 5;
                speed = 2;
                attack = 3;
                range = 5;
                hp_max = 800;
                break;
    case 'C':   name = "Human Rifleman";
                cost = 8;
                speed = 2;
                attack = 100;
                range = 7;
                hp_max = 500;
                break;
    default:    name = "Unknown";
                cost = 0;
                speed = 0;
                attack = 0;
                range = 0;
                hp_max = 0;
                break;
    }

    riskMultiplier = attack * (speed + range) / 100;

    set_hp_current(hp_max);
}

//getters
std::string Troop::get_name() {
    return name;
}

char Troop::get_id() {
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
void Troop::set_hp_current(char value) {
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

void Troop::set_risk(float value) {
    risk = value;
}

void Troop::set_pos(int x, int y) {
    pos.x = x;
    pos.y = y;
}
