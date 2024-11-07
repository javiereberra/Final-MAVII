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

	//cuerpo de las CAJAS ?con sprite?
	b2Body* caja1;
	b2Body* caja2;
	b2Body* caja3;


	//avatar y textura de cajas
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

	//contador de Ragdolls y texto
	int contadorRagdolls;
	Font* fuente;
	Text* textContador;

	//sprites y texturas para cajas correctas e incorrectas
	Sprite* cajaCorrecta1;
	Sprite* cajaCorrecta2;
	Sprite* cajaCorrecta3;
	Texture* cajaCorrectaTx;
	Texture* cajaIncorrectaTx;

public:
	//constructor y destructor
	Game(int ancho, int alto, std::string titulo);
	~Game(void);
	//iniciar físicas
	void InitPhysics();

	//main gameloop, dibujar, eventos y el setzoom para escalar la vista

	void loop();
	void Dibujar();
	void Actualizar();
	void Eventos();
	void SetZoom();

	//metodos para los tres niveles
	void Level1();
	void Level2();
	void Level3();

	//avanzar de nivel y resetear nivel
	void NextLevel();
	void ResetLevel();

	//menú de inicio, menú de informacion del juego
	void MenuInicio();
	void MenuInfo();
	//NO LO USÉ TODAVIA
	void MenuGameOver();

	//para comprobar si las cajas están en la zona correcta
	bool CajaEnZona1(b2Body* caja1);
	bool CajaEnZona2(b2Body* caja2);
	bool CajaEnZona3(b2Body* caja3);

	//para cambiar los sprites cuando las cajas están correctas
	void CajasCorrectas();

};