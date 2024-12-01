#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Ragdoll.h"
#include "Avatar.h"
#include <list>

using namespace sf;
// CLASE JUEGO //

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

	//Textura y sprite para los fondos de menuinicio y menuinfo
	Texture* textura1;
	Sprite* fondo;
	Texture* textura2;
	Sprite* menuInfo;

	Texture* textura3;
	Sprite* factory;


	//cuerpo del cañon
	b2Body* cannon;
	Avatar* m_AvatarCannon;
	Texture canonText;

	b2Body* BaseCannon;
	Avatar* m_AvatarBaseCannon;
	Texture BaseCanonText;

	//cuerpo, avatar y textura piso
	b2Body* piso;
	Avatar* m_AvatarPiso;
	Texture pi;

	//cuerpo, avatar y textura techo
	b2Body* techo;
	Avatar* m_AvatarTecho;
	Texture te;
	//cuerpo, avatar y textura pared Izquierda
	b2Body* paredI;
	Avatar* m_AvatarParedI;
	Texture pz;
	//cuerpo, avatar y textura pared Derecha
	b2Body* paredD;
	Avatar* m_AvatarParedD;
	Texture pd;

	//cuerpo, avatar y textura las tres plataformas
	b2Body* plataforma1;
	Avatar* m_AvatarPlatf1;

	Texture platText;

	b2Body* plataforma2;
	Avatar* m_AvatarPlatf2;
	
	b2Body* plataforma3;
	Avatar* m_AvatarPlatf3;
	

	//cuerpo, avatar y textura de la columna
	b2Body* columna1;
	Avatar* m_AvatarCol1;
	Texture col1;


	//cuerpo de las CAJAS con sprite
	b2Body* caja1;
	b2Body* caja2;
	b2Body* caja3;


	//avatar y textura de cajas
	Avatar* m_Avatar1;
	Avatar* m_Avatar2;
	Avatar* m_Avatar3;
	Texture t;

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


	//PRUEBA POSICIONES DE CAJA
	float box1positionX;

public:
	//constructor y destructor
	Game(int ancho, int alto, std::string titulo);
	~Game(void);
	//iniciar físicas
	void InitPhysics();
	void InitPhysicsLevel1();
	void InitPhysicsLevel2();
	void InitPhysicsLevel3();
	

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