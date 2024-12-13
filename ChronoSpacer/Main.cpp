#include "Main.h"

Character Player;
Character Enemy;

sf::Text textLifePlayer;
sf::Text textLevelPlayer;
sf::Text textLifeEnemy;
sf::Text Attack;
sf::Text Defense;
sf::Text nbrEnemy;
sf::Font arialFont;

sf::RectangleShape but_Action_Attack;
sf::RectangleShape but_Action_Defense;

bool isPlayerTurn;
int indexButton;

int indexEnemy = 0;

std::list<Particle> particles;

bool animatingPlayer = false;
bool returningPlayer = false;
float maxDistancePlayer = 50.f;
float velocityPlayer = 200.f;
float traveledDistancePlayer = 0.f;
sf::Vector2f startPositionPlayer(175.f, 150.f); // Position de départ

bool animatingEnemy = false;
bool returningEnemy = false;
float maxDistance = 50.f;
float velocity = 200.f;
float traveledDistanceEnemy  = 0.f;
sf::Vector2f startPositionEnemy(525.f, 150.f); // Position de départ

int main()
{
    Initalization();
    InitializePlayer(Player);
    Player.Info = LaunchStats();
    Update();
}

void Update()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG");
    CreateUI();
    NewRound();
    sf::Clock clock;
    clock.restart();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        float deltaTime = clock.restart().asSeconds();
        if (isPlayerTurn)
        {
            DoAnimation(Enemy.circleChara, deltaTime, startPositionEnemy, velocity, traveledDistanceEnemy, maxDistance, animatingEnemy, returningEnemy);
            DoAnimation(Player.circleChara, deltaTime, startPositionPlayer, velocityPlayer, traveledDistancePlayer, maxDistancePlayer, animatingPlayer, returningPlayer);
            PlayerRound();
        }
        else
        {
            IARound();
        }
        if (clock.getElapsedTime().asSeconds() > 0.8f)
        {
            clock.restart();
        }
        UpdateParticles(particles, deltaTime);
        RenderGame(window);
    }
}

void WaitFor(float milliseconds)
{
    Sleep(milliseconds);
    CheckLife();
}

void CheckLife() 
{
    std::cout << "CHECK LIFE" << std::endl;

    if (Player.Info.actualLife <= 0) 
    {
        std::cout << "PLAYER DEFEATED" << std::endl;
        return;
    }
    if (Enemy.Info.actualLife <= 0)
    {
        std::cout << "ENEMY DEFEATED" << std::endl;
        int range = Enemy.Info.baseLife;
        Player.ReceiveXp(GetRandomRange(range - 3, range + 2));

        NewRound();

        return;
    }

}

void RenderGame(sf::RenderWindow& window)
{
    window.clear();
    window.draw(Player.circleChara);
    window.draw(Enemy.circleChara);
    window.draw(Enemy.circleChara);
    window.draw(but_Action_Attack);
    window.draw(but_Action_Defense);
    window.draw(textLifePlayer);
    window.draw(textLevelPlayer);
    window.draw(textLifeEnemy);
    window.draw(Attack);
    window.draw(Defense);
    window.draw(nbrEnemy);


    for (const Particle& particle : particles)
    {
        window.draw(particle.shape);
    }
    window.display();
}

void Initalization() 
{

    std::string fontArialPath = GetDirectories("Assets") + "arial.ttf";
    if (arialFont.loadFromFile(fontArialPath))
    {
        textLifePlayer.setFont(arialFont);
        textLevelPlayer.setFont(arialFont);
        textLifeEnemy.setFont(arialFont);
        Attack.setFont(arialFont);
        Defense.setFont(arialFont);
        nbrEnemy.setFont(arialFont);
    }
    std::cout << "END INITIALIZATION" << std::endl;
}

void UpdateLifeTexts()
{
    textLifePlayer.setString("Life : " + std::to_string(Player.Info.actualLife));
    textLevelPlayer.setString("Level : " + std::to_string(Player.Info.level));
    textLifeEnemy.setString("Life : " + std::to_string(Enemy.Info.actualLife));
    nbrEnemy.setString("Enemy " + std::to_string(indexEnemy));
}

void CreateUI(){
    textLifePlayer = EditText("Life : " + Player.Info.actualLife, { 200.f, 100.f }, { 0.5f, 0.5f });
    textLevelPlayer = EditText("Level : " + Player.Info.level, { 195.f, 80.f }, { 0.5f, 0.5f });
    textLifeEnemy = EditText("Life : " + Enemy.Info.actualLife, { 550.f, 100.f }, { 0.5f, 0.5f });
    Attack = EditText("Attack", { 200.f, 400.f }, { 0.5f, 0.5f });
    Defense = EditText("Defense", { 550.f, 400.f }, { 0.5f, 0.5f });
    nbrEnemy = EditText("Enemy " + std::to_string(indexEnemy), { 540.f, 50.f }, { 0.6f, 0.6f });
    CreateRect(but_Action_Attack, 150.0f, 75.0f, sf::Color::Blue, sf::Color::White, 5.0f, { 150.0f, 450.0f });
    CreateRect(but_Action_Defense, 150.0f, 75.0f, sf::Color::Blue, sf::Color::White, 5.0f, { 500.0f, 450.0f });
}

sf::Text EditText(std::string string, sf::Vector2f positionText, sf::Vector2f scale)
{
   // if (arialFont.loadFromFile() { std::cerr << "arial not found" << std::endl; return; }
    sf::Text textToModify;
    textToModify.setFont(arialFont);
    textToModify.setString(string);
    textToModify.setPosition(positionText);
    textToModify.setScale(scale);
    return textToModify;
}

void NewRound()
{
    // L'ENNEMI A ETE TUE ON LANCE UN NOUVEAU TOUR
    indexEnemy++;
    Enemy = InitializeEnemy(Player);
    std::cout << "A new enemy has appeared!" << std::endl;
    std::cout << "Enemy stats: Life = " << Enemy.Info.actualLife << ", Damage = " << Enemy.Info.damage << std::endl;
    ResetRound();
    UpdateLifeTexts();
}

void AttackEnemy()
{
    Player.InflictDamage(Enemy);
    InstanceParticule(particles, 10, { 575,190 }, sf::Color::White, 25, 35, 5, 1);
    UpdateLifeTexts();
}

void DefendPlayer() 
{
    Player.Defend();
}

void ResetRound()
{
    if (Player.isDefending)
    {
        Player.isDefending = false;
    }
    // ON RESET LES ACTIONS
    isPlayerTurn = true;
}

void PlayerRound()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Exemple : bouton d'attaque
    {
        but_Action_Attack.setOutlineColor(sf::Color::Red);
        but_Action_Defense.setOutlineColor(sf::Color::White);
        indexButton = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Exemple : bouton de défense
    {
        but_Action_Defense.setOutlineColor(sf::Color::Red);
        but_Action_Attack.setOutlineColor(sf::Color::White);
        indexButton = 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && indexButton == 1)
    {
        std::cout << "PLAYER ATTACK" << std::endl;
        BeginMovement(Enemy.circleChara, startPositionEnemy, velocity, traveledDistanceEnemy, maxDistance, animatingEnemy, returningEnemy, false);
        //BeginMovement(Player.circleChara, startPositionPlayer, velocityPlayer, traveledDistancePlayer, maxDistancePlayer, animatingPlayer, returningPlayer, false);
        AttackEnemy();
        isPlayerTurn = false;
        WaitFor(1000);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && indexButton == 2)
    {
        std::cout << "PLAYER DEFEND" << std::endl;
        DefendPlayer();
        isPlayerTurn = false;
        WaitFor(1000);
    }
}

void IARound()
{
    if (Enemy.isDefending)
    {
        Enemy.isDefending = false;
    }
    std::cout << "IA TURN" << std::endl;
    // C'est a L'IA DE JOUER - DEFENDRE OU ATTAQUER
    if (isPlayerTurn) { return; }
    int randomAction = GetRandomRange(1, 8);
    if (randomAction >= 1 && randomAction <= 3)
    {
        std::cout << "IA INFLICT DAMAGE" << std::endl;
        Enemy.InflictDamage(Player);
        BeginMovement(Player.circleChara, startPositionPlayer, velocityPlayer, traveledDistancePlayer, maxDistancePlayer, animatingPlayer, returningPlayer, true);

        InstanceParticule(particles, 10, { 215,190 }, sf::Color::White, 25, 35, 5, 1);
        UpdateLifeTexts();
    }
    else if (randomAction >= 4 && randomAction <= 6)
    {
        std::cout << "DEFEND" << std::endl;
        Enemy.Defend();
    }
    else
    {
        std::cout << "ENEMY DO NOTHING" << std::endl;
    }
    WaitFor(1000);
    ResetRound();

}


