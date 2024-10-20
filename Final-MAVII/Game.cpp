#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>

//constructor que define ventana, frames, la escala e inicia f�sicas
Game::Game(int ancho, int alto, std::string titulo)
{
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom();
	InitPhysics();

	//Textura y Sprite del fondo del nivel
	textura1 = new Texture;
	fondo = new Sprite;
	textura1->loadFromFile("menuInicio.png");
	fondo->setTexture(*textura1);

	textura2 = new Texture;
	menuInfo = new Sprite;
	textura2->loadFromFile("menuInfo.jpg");
	menuInfo->setTexture(*textura2);

	MenuInicio();

	currentLevel = 1;
	levelCompleted = false;

	contadorRagdolls = 0;
}

//el cl�sico gameloop
void Game::loop()
{
	while (wnd->isOpen())
	{
		wnd->clear(clearColor);
		Eventos();
		//GESTION DE NIVELES//
		switch (currentLevel)
		{
		case 1:
			Level1();
			break;
		case 2:
			Level2();
			break;
		case 3:
			Level3();
			break;
		default:
			std::cout << "No hay m�s niveles." << std::endl;
			wnd->close();
			break;
		}

		//Actualizar();
		//Dibujar();
		wnd->display();

	}
}

void Game::Level1()
{
	// L�gica de actualizaci�n del nivel 1
	Actualizar(); // Actualiza las f�sicas del mundo, objetos, etc.

	// Dibujar objetos del nivel 1
	Dibujar(); // Aqu� dibujas los objetos del nivel, ragdolls, etc.

	// Condici�n para pasar al siguiente nivel
	if (contadorRagdolls >= 5) {
		levelCompleted = true;
		NextLevel(); // Pasamos al siguiente nivel
	}
}

void Game::Level2()
{
	// L�gica de actualizaci�n del nivel 2
	Actualizar();
	// Dibujar objetos del nivel 2
	Dibujar();

	// Condici�n para pasar al siguiente nivel
	if (contadorRagdolls >= 10) {
		levelCompleted = true;
		NextLevel();
	}
}

// M�todo para el tercer nivel
void Game::Level3()
{
	// L�gica de actualizaci�n del nivel 3
	Actualizar();
	Dibujar();

	if (contadorRagdolls >= 15) {
		std::cout << "�Felicidades, has completado el juego!" << std::endl;
		wnd->close();
	}
}

void Game::NextLevel()
{
	if (levelCompleted) {
		currentLevel++; // Incrementamos el nivel actual
		ResetLevel(); // Reiniciar los par�metros del nuevo nivel
	}
}

void Game::ResetLevel()
{
	
	// Aqu� puedes restablecer el estado de los objetos para el nuevo nivel
	InitPhysics(); // Por ejemplo, reiniciar las f�sicas
	SetZoom();     // Reajustar la c�mara si es necesario
	levelCompleted = false; // Restablecer la bandera de nivel completado


	//para limpiar los ragdolls
	for (auto& ragdoll : ragdolls) {
		delete ragdoll;  // Eliminar cada ragdoll de la memoria
	}
	ragdolls.clear();
}

//actualiza el phyworld
void Game::Actualizar()
{
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();

}
//para dibujar objetos, no se usa pero lo dejamos para cuando hagamos el final con los sprites
void Game::Dibujar()
{
	m_Avatar->Actualizar();
	m_Avatar->Dibujar(*wnd);
	

	for (auto& ragdoll : ragdolls) {
		ragdoll->Actualizar(); // Llama a la funci�n que actualiza el sprite del torso
	}

	for (auto& ragdoll : ragdolls) {
		ragdoll->Dibujar(*wnd); // Llama a la funci�n que dibuja el sprite del torso
	}

}

void Game::Eventos()
{

	//fijar la posici�n del ca�on
	b2Vec2 cannonPosition(6.0f, 93.0f);

	//sacar la posici�n del cursor del mouse y pasarla a la escala de box2d
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*wnd);
	sf::Vector2f worldMousePosition = wnd->mapPixelToCoords(mousePosition);
	b2Vec2 mouseWorldPosition(mousePosition.x * scaleX, mousePosition.y * scaleY);

	//establecer la distancia entre el cursor y el ca�on
	b2Vec2 displacement = mouseWorldPosition - cannonPosition;
	//obtener el �ngulo del vector
	float angle = atan2(displacement.y, displacement.x);


	// Calcular la distancia entre el ca�on y el cursor
	float distance = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
	//crear la potencia del ca�on en base a la distancia del cursor
	float fuerza = distance * 15;



	//pasar el angulo a grados - por si fuera necesario m�s adelante//
	float angleInDegrees = angle * 180.0f / b2_pi;


	//el ca�on rota al �ngulo en que se encuentra el cursor
	cannon->SetTransform(b2Vec2(6.0f, 93.0f), angle);

	//la mitad aproximada de la longitud del ca�on para obtener la punta
	float cannonLargo = 5.5f;

	//obtener la posici�n de la punta del ca�on ajustandola al angulo de rotaci�n
	b2Vec2 cannonTipPosition(
		cannonPosition.x + cannonLargo * cos(angle),
		cannonPosition.y + cannonLargo * sin(angle)
	);

	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close();
			break;
		case Event::MouseButtonPressed:
			if (ragdolls.size() >= 5) {
				// Eliminar el primer ragdoll si ya hay 5 ragdolls
				delete ragdolls.front();
				ragdolls.pop_front();
			}
			//crear el ragdoll en la punta del ca�on
			Ragdoll* ragdoll = new Ragdoll(phyWorld, cannonTipPosition);
			//aplicar el impulso basado en la fuerza que est� afectada por la distancia del cursor y el �ngulo
			b2Vec2 impulse(fuerza * cos(angleInDegrees * b2_pi / 180.0f), fuerza * sin(angleInDegrees * b2_pi / 180.0f));
			//se aplica el impulso
			ragdoll->applyImpulse(impulse);
			ragdolls.push_back(ragdoll);
			contadorRagdolls++;
			break;
					

		}
	}



}

//fijamos la escala
void Game::SetZoom()
{
	View camera;
	camera.setSize(100.0f, 100.0f);
	camera.setCenter(50.0f, 50.0f);
	wnd->setView(camera);

	//obtenemos la escala para usarla con el cursor
	sf::Vector2f viewSize = camera.getSize();
	sf::Vector2u windowSize = wnd->getSize();
	scaleX = viewSize.x / windowSize.x;
	scaleY = viewSize.y / windowSize.y;
}

void Game::InitPhysics()
{
	//inicializamos el mundo
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	//Crear el render y setear banderas
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);

	//creamos un piso paredes y techo
	b2Body* piso = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	piso->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	b2Body* paredI = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	paredI->SetTransform(b2Vec2(00.0f, 50.0f), 0.0f);

	b2Body* paredD = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	paredD->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	b2Body* techo = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	techo->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);

	//creamos dos obst�culos est�ticos
	b2Body* obstaculo1 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 20, 5);
	obstaculo1->SetTransform(b2Vec2(60.0f, 60.0f), 0.0f);

	b2Body* obstaculo2 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 20, 10);
	obstaculo2->SetTransform(b2Vec2(80.0f, 80.0f), 0.0f);

	//creamos dos obst�culos din�micos
	b2Body* obstaculo3 = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 10, 0.1f, 0.1f, 0.1f);
	obstaculo3->SetTransform(b2Vec2(80.0f, 70.0f), 0.0f);

	b2Body* obstaculo4 = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 10, 0.1f, 0.1f, 0.1f);
	obstaculo4->SetTransform(b2Vec2(55.0f, 53.0f), 0.0f);


	//creamos la base del ca�on
	b2Body* cannon_base = Box2DHelper::CreateCircularStaticBody(phyWorld, 2);
	cannon_base->SetTransform(b2Vec2(6.0f, 93.0f), 0.0f);

	//creamos el ca�on
	cannon = Box2DHelper::CreateRectangularStaticBody(phyWorld, 11, 1.2f);

	//creamos el bloqueprueba
	obstaPrueba	= Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 10, 0.1f, 0.1f, 0.1f);
	obstaPrueba->SetTransform(b2Vec2(40.0f, 40.0f), 0.0f);

	//asignamos la textura al sprite y al avatar
	t.loadFromFile("block.png");
	sf::Sprite* s = new sf::Sprite(t);
	
	m_Avatar = new Avatar(obstaPrueba, s);


}


void Game::MenuInicio() {




	wnd->setView(wnd->getDefaultView());

	// Mostrar el men�
	while (wnd->isOpen()) {
		sf::Event event;
		while (wnd->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				wnd->close();
				return;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Num1) {
					// Opci�n para iniciar el juego
					SetZoom();
					MenuInfo();
					return;  // Salimos del men� y continuamos con el juego
				}
				else if (event.key.code == sf::Keyboard::Num2) {
					// Opci�n para salir
					wnd->close();
					return;
				}
			}
		}

		// Dibujar el men�
		wnd->clear(sf::Color::Black);
		wnd->draw(*fondo);
		wnd->display();
	}
	
}


void Game::MenuInfo() {




	wnd->setView(wnd->getDefaultView());

	// Mostrar el men�
	while (wnd->isOpen()) {
		sf::Event event;
		while (wnd->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				wnd->close();
				return;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					// Opci�n para continuar el juego
					SetZoom();
					return;  // Salimos del men� y continuamos con el juego
				}
			}
		}

		// Dibujar el men�
		wnd->clear(sf::Color::Black);
		wnd->draw(*menuInfo);
		wnd->display();
	}

}

//destructor de game
Game::~Game(void) {
	for (auto& ragdoll : ragdolls) {
		delete ragdoll;
	}
	delete phyWorld;
	delete debugRender;
}