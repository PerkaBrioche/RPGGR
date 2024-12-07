#include "Character.h"
#include "Main.h"

int paliers[palierCounts] = { 20, 40, 70, 110, 180, 260, 350 };

void InitializePlayer(Character& player)
{
    // INITIALISE LE JOUEUR ET MODIFIE DIRECTEMENT SES STATS, IMAGE POSITION ECT

   // sf::Sprite playerTexture;

   // InitializeSprite(playerTexture, "player.png", sf::Vector2f{ 400, 300 }, sf::Vector2f{ 0, 0 });

    sf::CircleShape circle;
    EditCircle(circle, sf::Color::Green, 50, {200, 200});

    CharacterStats charaInfo = { 0, 0, 5, 10 };
    player = { circle, charaInfo };
}

Character InitializeEnemy(Character player)
{
    // INITIALISER UN ENNEMI AVEC LE LEVEL DU PLAYER
    int level = player.Info.level;
    int damage = (GetRandomRange(2, 5) * level);
    int baseLife = (GetRandomRange(4, 8) * level);
    // STATS RANDOM DANS LA RANGE DU JOUEUR

 //   sf::Sprite EnemyTexture;
  //  InitializeSprite(EnemyTexture, "enemy.png", sf::Vector2f{ 400, 300 }, sf::Vector2f{ 0, 0 });


    sf::CircleShape circle;
    EditCircle(circle, sf::Color::Red, 50, { 150, 200 });
    CharacterStats charaInfo = { level, 0, damage, baseLife };
    Character Enemy = { circle, charaInfo };

    return Enemy;
}





//    palierLevel[7] = { 20, 40, 70, 110, 180, 260, 350 };