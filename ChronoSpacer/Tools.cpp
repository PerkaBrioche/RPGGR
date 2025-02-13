#include "Tools.h"


std::string GetAppPath()
{
	// RETOURNE LE FICHIER ACTUEL DU PROJET

	char cExeFilePath[256];
	GetModuleFileNameA(NULL, cExeFilePath, 256);
	std::string exeFilePath = cExeFilePath;
	int exeNamePos = exeFilePath.find_last_of("\\/");
	std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
	return appPath;
}

std::string GetDirectories(std::string dname)
{
	// RETOURNE UN FICHIER PRECIS AVEC UN NOM EN PARAMETRES EX : "Assets" VA RETOURNE LE FICHER ASSETS DANS LE FICHIER DU PROJET 

	std::string appPath = GetAppPath();
	appPath = appPath + dname + "\\";
	return appPath;
}

void InitializeSprite(sf::Sprite& targerImage, std::string assetName, sf::Vector2f targetScale, sf::Vector2f targetPosition)
{
	// INITIALISE LE SPRITE D'UN CHARACTER COMPLEMENT DU INITIALISE PLAYER OU ENNEMY
	sf::Texture targetTexture;
	sf::Vector2u targetize;

	targetTexture.loadFromFile(GetDirectories("Assets") + assetName);
	targerImage.setTexture(targetTexture);
	targetize = targetTexture.getSize();
	targerImage.setOrigin(sf::Vector2f(targetize.x / 2.0f, targetize.y / 2.0f));
	targerImage.setScale(targetScale);
	targerImage.setPosition(targetPosition);
}

int GetRandomRange(int min, int max)
{
	// RETOURNE UN INT ENTRE UNE RANGE

	return min + rand() % ((max + 1) - min);
}

void EditCircle(sf::CircleShape& circle, sf::Color color, float taille, sf::Vector2f circlePosition)
{	
	circle.setRadius(taille);
	circle.setFillColor(color);
	circle.setPosition(circlePosition);
}

void CreateRect(sf::RectangleShape& carre, float longueur, float hauteur, sf::Color fillColor, sf::Color colorOutline, float tailleOutline, sf::Vector2f squarePosition) {

	sf::Vector2f rec = sf::Vector2f(longueur, hauteur);
	carre.setSize(rec);
	carre.setPosition(squarePosition);
	carre.setFillColor(fillColor);
	carre.setOutlineColor(colorOutline);
	carre.setOutlineThickness(tailleOutline);
}

int Clamp(int value, int min, int max)
{
	if (value < min) { return min; }
	if (value > max) { return max; }
	return value;
}

void AugmenterPercentageAttack(int& actualPercentage, sf::Text& txt)
{
	int randomValue = GetRandomRange(5, 20);
	actualPercentage = Clamp(actualPercentage + randomValue, 0, 100);
	txt.setString(std::to_string(actualPercentage) + "%");
}

void ResetPercentage(int& actualPercentage, sf::Text& txt)
{
	actualPercentage = 0;
	txt.setString(std::to_string(actualPercentage) + "%");
}

bool TryPercentage(int actualPercentage) 
{
	int random = GetRandomRange(0, 101);
	if (random < actualPercentage) { return true; } return false;
}

void EndOfGame() 
{

}

void SetBarUI(sf::RectangleShape& fillBar, sf::RectangleShape& backgroundBar, sf::Color bgColor, sf::Color fillbarColor, sf::Vector2f position, sf::Vector2f scale) 
{
	// Rectangle de fond (piste du slider)

	backgroundBar.setSize(scale);
	backgroundBar.setFillColor(bgColor);
	backgroundBar.setPosition(position);

	// Rectangle de remplissage (jauge de progression)

	fillBar.setSize({ 0, scale.y });
	fillBar.setFillColor(fillbarColor);
	fillBar.setPosition(position);
}

void UpdateBarUI(int newPercentage, float progress, float maxProgress, sf::RectangleShape& fillBar, sf::RectangleShape& backgroundBar)
{
	progress = newPercentage;
	progress = std::max(0.0f, std::min(progress, maxProgress));

	fillBar.setSize({ progress * (backgroundBar.getSize().x /100) , backgroundBar.getSize().y});

	std::cout << newPercentage << std::endl;
	std::cout << progress << std::endl;
	std::cout << maxProgress << std::endl;
	std::cout << backgroundBar.getSize().y << std::endl;

}