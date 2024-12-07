#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tools.h"
#include <algorithm>
#include "Main.h"
const int palierCounts = 7; // Constante, pas besoin d'extern ici.
extern int paliers[palierCounts]; // Déclaration du tableau.

struct Character;
struct CharacterStats;

void DefinePalierLevel(int* p);
int GetDamage();

struct CharacterStats
{
    int level;
    int defense;
    int experience;
    int damage;
    int baseLife;
    int actualLife = baseLife;
};

struct Character
{
    //sf::Sprite characterTexture;

    sf::CircleShape circleChara;
    CharacterStats Info;
    bool isDefending = false;
    bool isEnemy = true;
    int GetDamage()
    {
        return Info.damage * Info.level;
    }

    void ReceiveDamage(int damage)
    {
        if (isDefending)
        {
            damage = Clamp(damage - Info.defense, 0, damage);
        }
        Info.actualLife -= damage;
        if (Info.actualLife < 0) Info.actualLife = 0;
    }

    void Defend() 
    {
        isDefending = true;
    }

    void ReceiveXp(int xp)
    {
        Info.experience += xp;
        CheckIfLevelUp();
    }

    void InflictDamage(Character& enemy)
    {
        enemy.ReceiveDamage(GetDamage());
    }

    void CheckIfLevelUp()
    {
        if (Info.level >= palierCounts) return;

        if (Info.experience >= paliers[Info.level])
        {
            Info.experience = 0;
            Info.level++;
            Info.damage += 5;
            Info.defense += 3;
            Info.actualLife = Info.baseLife;
        }
    }
};

int GetDamage(Character chara);
void ReceiveDamage(int damage);
void ReceiveXp(int xp);
void CheckIfLevelUp();

void InitializePlayer(Character& player);
Character InitializeEnemy(Character player);
