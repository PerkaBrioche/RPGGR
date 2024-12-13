#include "Main.h"

enum GameStep {
    InitRound,
    PlayerSelect,
    PlayerAnim,
    EnemeySelect,
    EnemeyAnim,
    GameOver,
};

GameStep step = GameStep::InitRound;
Character Player;
Character Enemy;

sf::Text textLifePlayer;
sf::Text textLevelPlayer;
sf::Text textLifeEnemy;
sf::Text Attack;
sf::Text Defense;
sf::Text nbrEnemy;
sf::Text textPercentageAttack;
sf::Font arialFont;

sf::RectangleShape but_Action_Attack;
sf::RectangleShape but_Action_Defense;


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
float maxDistancePlayer = 300.f;
float velocityPlayer = 800.f;
float traveledDistancePlayer = 0.f;
sf::Vector2f startPositionPlayer(175.f, 150.f); // Position de d�part

bool animatingEnemy = false;
bool returningEnemy = false;
float maxDistance = 80.f;
float velocity = 100.f;
float traveledDistanceEnemy  = 0.f;
sf::Vector2f startPositionEnemy(525.f, 150.f); // Position de d�part

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

        if (step==GameStep::GameOver) {
            return;
        }
        else if (step == GameStep::InitRound) {
            ResetRound();
            step = GameStep::PlayerSelect;
        }
 
        else if (step==GameStep::PlayerSelect)
        {
           
         bool hasPlayed= PlayerRound();
         if (hasPlayed) {
             step = GameStep::PlayerAnim;
         }
        }
        else if (step == GameStep::PlayerAnim) {
            DoAnimation(Enemy.circleChara, deltaTime, startPositionEnemy, velocity, traveledDistanceEnemy, maxDistance, animatingEnemy, returningEnemy);
            DoAnimation(Player.circleChara, deltaTime, startPositionPlayer, velocityPlayer, traveledDistancePlayer, maxDistancePlayer, animatingPlayer, returningPlayer);
            if (animatingPlayer == false && animatingEnemy == false) {
                step = GameStep::EnemeySelect;
            }
           
        }
        else if (step == GameStep::EnemeySelect) {
            IARound();
            step = GameStep::EnemeyAnim;
        }
     
        else if(step==GameStep::EnemeyAnim)
        {
            DoAnimation(Enemy.circleChara, deltaTime, startPositionEnemy, velocity, traveledDistanceEnemy, maxDistance, animatingEnemy, returningEnemy);
            DoAnimation(Player.circleChara, deltaTime, startPositionPlayer, velocityPlayer, traveledDistancePlayer, maxDistancePlayer, animatingPlayer, returningPlayer);
            if (animatingPlayer == false && animatingEnemy == false) {
                step = GameStep::InitRound;
            }
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
        step = GameStep::GameOver;
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
    percentageAttack = 0;
    indexEnemy++;
    Enemy = InitializeEnemy(Player);
    AugmenterPercentageAttack(percentageAttack);
    UpdateBarUI(percentageAttack, progress, maxProgress, fillBar, backgroundBar);
    std::cout << "A new enemy has appeared!" << std::endl;
    std::cout << "Enemy stats: Life = " << Enemy.Info.actualLife << ", Damage = " << Enemy.Info.damage << std::endl;
    ResetRound();
    UpdateLifeTexts();
}

void AttackEnemy()
{
    Player.InflictDamage(Enemy);
    CheckLife();
    UpdateLifeTexts();
}

void DefendPlayer() 
{
    Player.Defend();
    CheckLife();
}

void ResetRound()
{
    if (Player.isDefending)
    {
        Player.isDefending = false;
    }
    // ON RESET LES ACTIONS
  
}



bool PlayerRound()
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
        maxDistancePlayer = 300.f;
        velocityPlayer = 800.f;
        maxDistance = 80.f;
        velocity = 100.f;
        std::cout << "PLAYER ATTACK" << std::endl;
        BeginMovement(Enemy.circleChara, startPositionEnemy, velocity, traveledDistanceEnemy, maxDistance, animatingEnemy, returningEnemy, false);
        BeginMovement(Player.circleChara, startPositionPlayer, velocityPlayer, traveledDistancePlayer, maxDistancePlayer, animatingPlayer, returningPlayer, false);
        AttackEnemy();
        return true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && indexButton == 2)
    {
        std::cout << "PLAYER DEFEND" << std::endl;
        DefendPlayer();
        return true;
    }
    return false;
}

void IARound()
{
    if (Enemy.isDefending)
    {
        Enemy.isDefending = false;
    }
    std::cout << "IA TURN" << std::endl;
    // C'est a L'IA DE JOUER - DEFENDRE OU ATTAQUER
    maxDistancePlayer = 80.f;
    velocityPlayer = 100.f;
    maxDistance = 300.f;
    velocity = 800.f;

    BeginMovement(Enemy.circleChara, startPositionEnemy, velocity, traveledDistanceEnemy, maxDistance, animatingEnemy, returningEnemy, true);
    BeginMovement(Player.circleChara, startPositionPlayer, velocityPlayer, traveledDistancePlayer, maxDistancePlayer, animatingPlayer, returningPlayer, true);
    int randomAction = GetRandomRange(0, 4);

    if (TryPercentage(percentageAttack))
    {
        Enemy.InflictDamage(Player);
    
        ResetPercentage(percentageAttack);
        CheckLife();
    }
    else 
    {
        AugmenterPercentageAttack(percentageAttack);
        if (randomAction >= 0 && randomAction <= 2)
        {
            // DO NOTHING
        }
        else {
            Enemy.Defend();
        }
    }


    UpdateBarUI(percentageAttack, progress, maxProgress, fillBar, backgroundBar);
    textPercentageAttack.setString(std::to_string(percentageAttack) + "%");


}

void PlayParticles(int numberPart, sf::Vector2f pos, sf::Color color ) 
{
    InstanceParticule(particles, numberPart, { pos }, color, 25, 35, 5, 1);
}

