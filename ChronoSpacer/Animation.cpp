#include "Animation.h"


float traveledDistance = 0.f;


void BeginMovement(sf::CircleShape& square, const sf::Vector2f& startPosition, float& velocity, float& maxDistance, bool& animating, bool& returning) {
    if (!animating) {
        animating = true;
        returning = false;
        traveledDistance = 0.f;
        square.setPosition(startPosition);
    }
}


void DoAnimation(sf::CircleShape& square, float deltaTime, const sf::Vector2f& startPosition, float& velocity, float& maxDistance, bool& animating, bool& returning) {
    if (animating) {
        // Calcul de la direction actuelle
        float direction = returning ? -1.f : 1.f;

        // Calcul du d�placement
        float moveDistance = velocity * deltaTime * direction;
        square.move(moveDistance, 0.f);
        traveledDistance += moveDistance;

        // V�rification des limites
        if (!returning && traveledDistance >= maxDistance) {
            returning = true; // D�but du retour
        }
        else if (returning && traveledDistance <= 0.f) {
            animating = false;  // Fin de l'animation
            returning = false;
            square.setPosition(startPosition); // R�initialisation
        }
    }
}



