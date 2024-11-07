#pragma once
#include <Box2D/Box2D.h>
#include "SFMLRenderer.h"
#include "Avatar.h"


//CLASE PARA LOS RAGDOLLS
class Ragdoll {
private:
    //las partes del ragdoll
    b2Body* torso;
    b2Body* cabeza;
    b2Body* brazoD;
    b2Body* brazoI;
    b2Body* piernaD;
    b2Body* piernaI;

    //los joints que unen a todas las partes
    b2RevoluteJoint* jointHeadTorso;
    b2RevoluteJoint* jointRightArmTorso;
    b2RevoluteJoint* jointLeftArmTorso;
    b2RevoluteJoint* jointRightLegTorso;
    b2RevoluteJoint* jointLeftLegTorso;

    //AVATAR TORSO -- PRUEBA
    Avatar* avatarTorso;
    // Textura y sprite para el torso
    Texture torsoTexture; 
    Sprite torsoSprite;


    b2World* world;

public:
    //constructor y destructor
    Ragdoll(b2World* world, const b2Vec2& position);
    ~Ragdoll();

    //para actualizar y dibujar los sprites
    void Actualizar();
    void Dibujar(sf::RenderWindow& wnd);
    //aplicar el impulso del cañón sobre el ragdoll
    void applyImpulse(const b2Vec2& impulse);
    
};