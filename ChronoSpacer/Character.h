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
    int experience;
    int damage;
    int criticals;
    int defense;
    int baseLife;
    int actualLife = baseLife;
};


struct Character
{
    sf::CircleShape circleChara;
    CharacterStats Info;
    bool isDefending = false;
    bool isEnemy = true;

    void ReceiveDamage(int damage)
    {
        std::cout << "RECEIVE DAMAGE : " << damage << std::endl;

        if (isDefending)
        {
            damage = Clamp(damage - Info.defense, 0, damage);
            std::cout << "DEFEND AND TANK : " << Info.defense << "DAMAGE LEFT : " << damage << std::endl;
            PlayParticles(4, circleChara.getPosition(), sf::Color::Cyan);
        }
        else 
        {
            PlayParticles(10, circleChara.getPosition(), sf::Color::Red);
        }
        Info.actualLife -= damage;
        if (Info.actualLife <= 0)
        { 
            Info.actualLife = 0;
        };
    }

    void Defend() 
    {
        isDefending = true;
    }

    void ReceiveXp(int xp)
    {
        std::cout << "RECEIVE XP : " << xp << std::endl;
        Info.experience += xp;
        CheckIfLevelUp();
    }

    void InflictDamage(Character& enemy)
    {
        int pourcentage = GetRandomRange(0, 100);
        if (pourcentage < Info.criticals) 
        {
            enemy.ReceiveDamage(Info.damage *2);
            std::cout << "CRITIAL HIT" << std::endl;
            return;
        }
        enemy.ReceiveDamage(Info.damage);
    }

    void CheckIfLevelUp()
    {
        if (Info.level >= palierCounts) return;

        if (Info.experience >= paliers[Info.level])
        {
            std::cout << "LEVEL UP " << std::endl;

            Info.experience = 0;
            Info.level++;
            Info.baseLife += GetRandomRange(3, 5);
            Info.damage += GetRandomRange(3,5);
            Info.defense += GetRandomRange(3, 5);
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
