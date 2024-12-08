#include "Character.h"

int paliers[palierCounts] = { 0, 10, 25, 40, 75, 95, 130 };

void InitializePlayer(Character& player)
{
    // INITIALISE LE JOUEUR ET MODIFIE DIRECTEMENT SES STATS, IMAGE POSITION ECT

   // sf::Sprite playerTexture;

   // InitializeSprite(playerTexture, "player.png", sf::Vector2f{ 400, 300 }, sf::Vector2f{ 0, 0 });

    sf::CircleShape circle;
    EditCircle(circle, sf::Color::Green, 50, { 175, 150 });   // Ennemi
    CharacterStats charaInfo = { 0, 0, 0, 0, 0, 0 ,0};
    player = { circle, charaInfo };
}

Character InitializeEnemy(Character player)
{
    // INITIALISER UN ENNEMI AVEC LE LEVEL DU PLAYER
    int level = player.Info.level;
    if (level <= 0) { level = 1; }
    int damage = (GetRandomRange(2, 5) * level);
    int baseLife = (GetRandomRange(2, 5) * level);
    int defense = (GetRandomRange(1, 3) * level);
    int citicals = (GetRandomRange(1, 3) * level);
    // STATS RANDOM DANS LA RANGE DU JOUEUR

 //   sf::Sprite EnemyTexture;
  //  InitializeSprite(EnemyTexture, "enemy.png", sf::Vector2f{ 400, 300 }, sf::Vector2f{ 0, 0 });


    sf::CircleShape circle;
    EditCircle(circle, sf::Color::Red, 50, { 525, 150 });   // Ennemi
    CharacterStats charaInfo = { level, 0, damage, citicals, defense, baseLife };
    Character Enemy = { circle, charaInfo };

    return Enemy;
}


//    palierLevel[7] = { 20, 40, 70, 110, 180, 260, 350 };