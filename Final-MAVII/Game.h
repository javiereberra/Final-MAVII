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


	//cuerpo del ca�on

	b2Body* cannon;

	//CAJAS con sprite
	b2Body* caja1;
	b2Body* caja2;
	b2Body* caja3;


	//avatar y su textura
	Avatar* m_Avatar1;
	Avatar* m_Avatar2;
	Avatar* m_Avatar3;
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
	Font* fuente;
	Text* textContador;

	//CAJAS CORRECTAS
	Sprite* cajaCorrecta1;
	Sprite* cajaCorrecta2;
	Sprite* cajaCorrecta3;
	Texture* cajaCorrectaTx;
	Texture* cajaIncorrectaTx;

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
	//NO LO US� TODAVIA
	void MenuGameOver();

	bool CajaEnZona1(b2Body* caja1);
	bool CajaEnZona2(b2Body* caja2);
	bool CajaEnZona3(b2Body* caja3);

};