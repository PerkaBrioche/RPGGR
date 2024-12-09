#include "ChooseStats.h"

CharacterStats playerStats = { 1, 0, 1, 1, 1, 1 };
bool statValidate = false;

 int StatsToApply = 10;
 using namespace std;

 sf::Text textStats;
 sf::Text textStatsLeft;

 sf::Text playGame;

 sf::Text textStatLife;
 sf::Text textStatStrengh;
 sf::Text textStatDefense;
 sf::Text textStatCriticals;


struct CharacterStats LaunchStats()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG");
    sf::RectangleShape AddLife, AddStrengh, AddDefense, AddCriticals, ValidateStats;
    CreateRect(AddLife, 150, 50 , sf::Color::Blue, sf::Color::White, 2.0f, { 25, 275 });
    CreateRect(AddStrengh, 150, 50, sf::Color::Green, sf::Color::White, 2.0f, {225, 275 });
    CreateRect(AddDefense, 150, 50, sf::Color::Green, sf::Color::White, 2.0f, {425, 275 });
    CreateRect(AddCriticals, 150, 50, sf::Color::Green, sf::Color::White, 2.0f, {625, 275 });
    CreateRect(ValidateStats, 150, 100, sf::Color::Green, sf::Color::White, 2.0f, {350, 400});



    // Textes dans les boutons
    // Affichage du menu principal
    textStats = EditText("Choose your stats", {250, 35}, {1.2f, 1.2f});
    playGame = EditText("Validate", { 360, 425}, {1.2f, 1.2f});
    textStatLife = EditText("Life +", { 30, 283 }, {0.8f, 0.8f});
    textStatStrengh = EditText("Strengh +", { 230, 283 }, {0.8f, 0.8f});
    textStatDefense = EditText("Defense +", { 430, 283 }, {0.8f, 0.8f});
    textStatCriticals = EditText("Criticals +", { 630, 283 }, {0.8f, 0.8f});

    while (window.isOpen())
    {
        if (statValidate)
        { 
            break; 
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || statValidate)
            {
                window.close();
            }

            // Gestion des clics sur les boutons
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (ValidateStats.getGlobalBounds().contains(mousePos))
                {
                    window.close();
                    statValidate = true;
                    break;
                }
                if (StatsToApply > 0) 
                {

                    if (AddLife.getGlobalBounds().contains(mousePos))
                    {
                        std::cout << "ALED" << std::endl;
                        playerStats.actualLife++;
                        StatsToApply--;
                    }
                    if (AddStrengh.getGlobalBounds().contains(mousePos))
                    {
                        playerStats.damage++;
                        StatsToApply--;
                    }
                    if (AddDefense.getGlobalBounds().contains(mousePos))
                    {
                        playerStats.defense++;
                        StatsToApply--;
                    }
                    if (AddCriticals.getGlobalBounds().contains(mousePos))
                    {
                        playerStats.criticals++;
                        StatsToApply--;
                    }
                }
            }
        }
        textStatsLeft = EditText(to_string(StatsToApply), { 375, 80 }, { 1.7f, 1.7f });

        // Dessiner le menu
        window.clear();
        window.draw(AddLife);
        window.draw(AddStrengh);
        window.draw(AddDefense);
        window.draw(AddCriticals);
        window.draw(ValidateStats);
        window.draw(textStatsLeft);
        window.draw(textStats);
        window.draw(textStatLife);
        window.draw(textStatStrengh);
        window.draw(textStatDefense);
        window.draw(textStatCriticals);
        window.draw(playGame);
        window.display();
    }
    Validate();
    return playerStats;
}

void Validate() 
{
  //  Update();
}
