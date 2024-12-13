#include "Main.h"

Character Player;
Character Enemy;

sf::Text textLifePlayer;
sf::Text textLevelPlayer;
sf::Text textLifeEnemy;
sf::Text Attack;
sf::Text Defense;
sf::Text nbrEnemy;
sf::Text textPercentageAttack;
sf::Text textXPWon;
sf::Font arialFont;

sf::RectangleShape but_Action_Attack;
sf::RectangleShape but_Action_Defense;

bool isPlayerTurn;
int indexButton;
int percentageAttack = 0;

int indexEnemy = 0;

std::list<Particle> particles;

sf::RectangleShape backgroundBar;
sf::RectangleShape fillBar;
float progress = 0;
float maxProgress = 100;

const sf::Color colorTextBar = sf::Color::Yellow;

bool animatingPlayer = false;
bool returningPlayer = false;
float maxDistancePlayer = 50.f;
float velocityPlayer = 200.f;
float traveledDistancePlayer = 0.f;
sf::Vector2f startPositionPlayer(175.f, 150.f); // Position de d�part

bool animatingEnemy = false;
bool returningEnemy = false;
float maxDistance = 50.f;
float velocity = 200.f;
float traveledDistanceEnemy  = 0.f;
sf::Vector2f startPositionEnemy(525.f, 150.f); // Position de d�part

bool IsFading;

float deltaTime;
static float currentAlpha = 255;

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
        deltaTime = clock.restart().asSeconds();
        if (isPlayerTurn)
        {
            //DoAnimation(Enemy.circleChara, deltaTime, startPositionEnemy, velocity, traveledDistanceEnemy, maxDistance, animatingEnemy, returningEnemy);
            //DoAnimation(Player.circleChara, deltaTime, startPositionPlayer, velocityPlayer, traveledDistancePlayer, maxDistancePlayer, animatingPlayer, returningPlayer);
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
        if (IsFading) 
        {
            if (currentAlpha > 0)
            {
                currentAlpha -= 100 * deltaTime;
                if (currentAlpha < 0)
                {
                    currentAlpha = 0;
                }

                sf::Color currentColor = textXPWon.getFillColor();
                currentColor.a = static_cast<sf::Uint8>(currentAlpha);
                textXPWon.setFillColor(currentColor);
            }
            else 
            {
                IsFading = false;
            }
        }
        UpdateParticles(particles, deltaTime);
        RenderGame(window);
    }
}

void WaitFor(float seconds)
{
    float timer = seconds;
    while (timer > 0) 
    {
        std::cout << timer << std::endl;
        timer -= deltaTime;
    }
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
        int xpWon = GetRandomRange(range - 3, range + 2);
        Player.ReceiveXp(xpWon);
        PopUpXp(xpWon);
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
    window.draw(textXPWon);
    window.draw(backgroundBar);
    window.draw(fillBar);
    window.draw(textPercentageAttack);
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
    SetBarUI(fillBar, backgroundBar, sf::Color::White, sf::Color::Red, { 470, 300}, {210, 30});
    textPercentageAttack = EditText(std::to_string(percentageAttack) + "%", { 420, 295 }, { 1, 1 });
    textPercentageAttack.setFillColor(colorTextBar);
    std::string fontArialPath = GetDirectories("Assets") + "arial.ttf";
    if (arialFont.loadFromFile(fontArialPath))
    {
        textLifePlayer.setFont(arialFont);
        textLevelPlayer.setFont(arialFont);
        textLifeEnemy.setFont(arialFont);
        Attack.setFont(arialFont);
        Defense.setFont(arialFont);
        nbrEnemy.setFont(arialFont);
        textPercentageAttack.setFont(arialFont);
        textXPWon.setFont(arialFont);
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
    textXPWon = EditText("", { 350, 100.f }, { 1, 1 });
    Attack = EditText("Attack", { 160, 457 }, { 1.5f, 1.5f });
    Defense = EditText("Defense", { 506, 465 }, {1.25f, 1.25f});
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
    ResetPercentage(percentageAttack, textPercentageAttack);
    indexEnemy++;
    Enemy = InitializeEnemy(Player);
    AugmenterPercentageAttack(percentageAttack, textPercentageAttack);
    UpdateBarUI(percentageAttack, progress, maxProgress, fillBar, backgroundBar);
    std::cout << "A new enemy has appeared!" << std::endl;
    std::cout << "Enemy stats: Life = " << Enemy.Info.actualLife << ", Damage = " << Enemy.Info.damage << std::endl;
    ResetRound();
    UpdateLifeTexts();
}

void AttackEnemy()
{
    Player.InflictDamage(Enemy);
    TriggerParticules(Enemy);
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
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Exemple : bouton de d�fense
    {
        but_Action_Defense.setOutlineColor(sf::Color::Red);
        but_Action_Attack.setOutlineColor(sf::Color::White);
        indexButton = 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && indexButton == 1)
    {
        std::cout << "PLAYER ATTACK" << std::endl;
        //BeginMovement(Enemy.circleChara, startPositionEnemy, velocity, traveledDistanceEnemy, maxDistance, animatingEnemy, returningEnemy, false);
        //BeginMovement(Player.circleChara, startPositionPlayer, velocityPlayer, traveledDistancePlayer, maxDistancePlayer, animatingPlayer, returningPlayer, false);
        AttackEnemy();
        isPlayerTurn = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && indexButton == 2)
    {
        std::cout << "PLAYER DEFEND" << std::endl;
        DefendPlayer();
        isPlayerTurn = false;
    }
}

void IARound()
{
    WaitFor(1);

    if (Enemy.isDefending)
    {
        Enemy.isDefending = false;
    }
    std::cout << "IA TURN" << std::endl;
    // C'est a L'IA DE JOUER - DEFENDRE OU ATTAQUER
    if (isPlayerTurn) { return; }


    int randomAction = GetRandomRange(0, 4);

    if (TryPercentage(percentageAttack))
    {
        Enemy.InflictDamage(Player);
        ResetPercentage(percentageAttack, textPercentageAttack);
        TriggerParticules(Player);
    }
    else 
    {
        AugmenterPercentageAttack(percentageAttack, textPercentageAttack);
        if (randomAction >= 0 && randomAction <= 2)
        {
            // DO NOTHING
        }
        else {
            Enemy.Defend();
        }
    }
    WaitFor(1);

    UpdateBarUI(percentageAttack, progress, maxProgress, fillBar, backgroundBar);
    UpdateLifeTexts();

    ResetRound();
    CheckLife();
}

void TriggerParticules(struct Character Chara) {
    if (Chara.isDefending) {
        InstanceParticule(particles, 4, { Chara.circleChara.getPosition() }, sf::Color::Red, 25, 35, 10, 1);
    }
    else 
    {
        InstanceParticule(particles, 10, { Chara.circleChara.getPosition() }, sf::Color::Red, 25, 35, 10, 1);
    }
}

void PopUpXp(int xp) 
{
    sf::Color TargetColor(0, 255, 0, 255);
    textXPWon.setFillColor(TargetColor);
    textXPWon.setString("XP WON : " + std::to_string(xp));
    currentAlpha = 255;
    IsFading = true;
}

