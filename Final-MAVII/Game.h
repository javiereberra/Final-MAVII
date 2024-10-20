#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Ragdoll.h"
#include "Avatar.h"
#include <list>

using namespace sf;

class Game
{
private:
	//propiedades de ventana
	int alto;
	int ancho;
	RenderWindow* wnd;
	Color clearColor;

	//objeto de Box2d
	b2World* phyWorld;
	SFMLRenderer* debugRender;

	//tiempo de frame
	float frameTime;
	int fps;

	//Textura y sprite para el fondo
	Texture* textura1;
	Sprite* fondo;
	Texture* textura2;
	Sprite* menuInfo;


	//cuerpo del cañon

	b2Body* cannon;

	//prueba con sprite
	b2Body* obstaPrueba;
	//avatar y su textura
	Avatar* m_Avatar;
	sf::Texture t;

	//variables para medir la escala
	float scaleX;
	float scaleY;

	//para gestionar los niveles
	int currentLevel;
	bool levelCompleted;

	//lista de ragdolls
	std::list<Ragdoll*> ragdolls;

	//contador de Ragdolls
	int contadorRagdolls;

public:

	Game(int ancho, int alto, std::string titulo);
	~Game(void);
	void InitPhysics();

	//main gameloop

	void loop();
	void Dibujar(); //realmente no se utiliza porque lo hace todo el sfmlrenderer pero lo dejamos para el final
	void Actualizar();
	void Eventos();
	void SetZoom();

	void Level1();
	void Level2();
	void Level3();

	void NextLevel();
	void ResetLevel();

	void MenuInicio();
	void MenuInfo();
	void MenuGameOver();

};