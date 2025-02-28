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
	Sprite* factoryLevel1;
	Texture* textura6;
	Sprite* factoryLevel2;
	Texture* textura7;
	Sprite* factoryLevel3;

	Texture* textura4;
	Sprite* menuGameOver;

	Texture* textura5;
	Sprite* menuVictory;

	//cuerpo del ca�on y su avatar
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

		
	//cuerpo, avatar y textura de columna
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

	//cuerpo, avatar y textura las tres plataformas del LEVEL1
	b2Body* plataforma1;
	Avatar* m_AvatarPlatf1;

	Texture platText;

	b2Body* plataforma2;
	Avatar* m_AvatarPlatf2;

	b2Body* plataforma3;
	Avatar* m_AvatarPlatf3;

	b2Body* plataforma4;
	Avatar* m_AvatarPlatf4;

	b2Body* plataforma5;
	Avatar* m_AvatarPlatf5;

	//cuerpo, avatares de pulley joint del LEVEL2
	b2Body* ascensor1Base;
	Avatar* m_AvatarAscensBase1;
	b2Body* ascensor1Col;
	Avatar* m_AvatarAscensCol1;
	b2Body* ascensor1Col2;
	Avatar* m_AvatarAscensCol12;


	b2Body* ascensor2;
	Avatar* m_AvatarAscens2;

	b2Body* paredDMedio;
	Avatar* m_AvatarParedDMedio;

	b2Body* planoInclinado;
	Avatar* m_AvatarPlanoInclinado;
	Texture planoInc;

	//cuerpo y avatares de las poleas y cargas del LEVEL3

	b2Body* polea1;
	Avatar* m_AvatarPolea1;

	b2Body* polea2;
	Avatar* m_AvatarPolea2;
	Texture poleaText;

	b2Body* carga1;
	Avatar* m_AvatarCarga1;

	b2Body* carga2;
	Avatar* m_AvatarCarga2;

	b2Body* planoInclinado2;
	Avatar* m_AvatarPlanoInclinado2;

	b2Body* columnaLevel3;
	Avatar* m_AvatarColLev3;



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
	int ragdollsRestantes;
	Font* fuente;
	Text* textContador;

	//sprites y texturas para cajas correctas e incorrectas
	Sprite* cajaCorrecta1;
	Sprite* cajaCorrecta2;
	Sprite* cajaCorrecta3;
	Texture* cajaCorrectaTx;
	Texture* cajaIncorrectaTx;


	//posiciones de las cajas
	float box1positionX;
	float box2positionX;
	float box3positionX;
	float box2positionY;

public:
	//constructor y destructor
	Game(int ancho, int alto, std::string titulo);
	~Game(void);
	//iniciar f�sicas base y de cada nivel
	void InitPhysics();
	void InitPhysicsLevel1();
	void InitPhysicsLevel2();
	void InitPhysicsLevel3();
	

	//gameloop, dibujar, actualizar, eventos y el setzoom para escalar la vista

	void loop();
	void Dibujar();
	void Actualizar();
	void Eventos();
	void SetZoom();

	//metodos para los tres niveles
	void Level1();
	void Level2();
	void Level3();

	//m�todos para avanzar de nivel, resetear nivel y ajustar posiciones de las cajas
	void NextLevel();
	void ResetLevel();
	void Posiciones();

	//men� de inicio, men� de informacion del juego
	void MenuInicio();
	void MenuInfo();
	//men� de victoria y game over
	void MenuGameOver();
	void MenuVictory();

	//para comprobar si las cajas est�n en la zona del contenedor
	bool CajaEnZona1(b2Body* caja1);
	bool CajaEnZona2(b2Body* caja2);
	bool CajaEnZona3(b2Body* caja3);

	//para cambiar los sprites cuando las cajas est�n correctas
	void CajasCorrectas();

};