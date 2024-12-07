#include "Main.h"

Character Player;
Character Enemy;

sf::Text lifePlayerText;
sf::Text currentLifePlayerText;
sf::Text lifeEnemyText;
sf::Text currentLifeEnemyText;


void main()
{
    Initalization();
}

void Initalization() 
{
    sf::Font arialFont;
    std::string fontArial = GetDirectories("Assets") + "arial.ttf";
    arialFont.loadFromFile(fontArial);

    InitializePlayer(Player);

    WriteText(arialFont, lifePlayerText, currentLifePlayerText, "Life : ", { 40.0f, 40.0f }, { 0.5f, 0.5f }, Player.Info.actualLife, Player.Info.baseLife);
    WriteText(arialFont, lifeEnemyText, currentLifeEnemyText, "Life Enemy : ", { 500.0f, 40.0f }, { 0.5f, 0.5f }, Enemy.Info.actualLife, Enemy.Info.baseLife);

    CreateUI();
    DisplaySFML();
    NewRound();
}

void CreateUI(){
    sf::RectangleShape carre;
    sf::RectangleShape Attck1;
    sf::RectangleShape Attck2;
    CreateRect(carre, 760, 560, sf::Color::Black, sf::Color::White, 10.0f, { 20.0f, 20.0f });
    CreateRect(Attck1, 150.0f, 75.0f, sf::Color::Blue, sf::Color::White, 5.0f, { 150.0f, 450.0f });
    CreateRect(Attck2, 150.0f, 75.0f, sf::Color::Blue, sf::Color::White, 5.0f, { 500.0f, 450.0f });
}

void WriteText(sf::Font fontUsed, sf::Text textLife, sf::Text currentLife, std::string life, sf::Vector2f positionText, sf::Vector2f scale, int currentHealth, int maxhealth)
{
    textLife.setFont(fontUsed);
    textLife.setString(life);
    textLife.setPosition(positionText);
    textLife.setScale(scale);
    currentLife.setFont(fontUsed);
    currentLife.setString(std::to_string(currentHealth) + "/" + std::to_string(maxhealth));
    currentLife.setPosition(positionText.x + 80.0f, positionText.y);
    currentLife.setScale(scale);
}

void DisplaySFML()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "ChronoSpacer");
    // Initialise everything below
    // Game loop

    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Process any input event here
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(Player.circleChara);
        window.draw(Enemy.circleChara);
        // Whatever I want to draw goes here
        window.display();
    }

}

void NewRound()
{
    // L'ENNEMI A ETE TUE ON LANCE UN NOUVEAU TOUR
    Enemy = InitializeEnemy(Player);
    ResetRound();
}

void AttackEnemy()
{
    Player.InflictDamage(Enemy);
}
void DefendPlayer() 
{
    Player.Defend();
}

void ResetRound()
{
    // ON RESET LES ACTIONS
    Enemy.isDefending = false;
    Player.isDefending = false;
    PlayerRound();
}

void PlayerRound() 
{
    int index = 0;
    bool spacePressed = false;


    if (index == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!spacePressed) {
            Enemy.GetDamage();
            spacePressed = true;
        }
    }
    else {
        spacePressed = false;
    }

    if (index == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!spacePressed) {
            Player.Defend();
            spacePressed = true;
        }
    }
    else {
        spacePressed = false;
    }
}

void IARound() 
{
    // C'est a L'IA DE JOUER - DEFENDRE OU ATTAQUER

    int randomAction = GetRandomRange(1, 5);
    if (randomAction > 1 && randomAction < 3) 
    {
        Enemy.InflictDamage(Player);
    }
    else 
    {
        Enemy.Defend();
    }

    ResetRound();
}


