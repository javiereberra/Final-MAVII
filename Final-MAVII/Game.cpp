#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>

//constructor 
Game::Game(int ancho, int alto, std::string titulo)
{
	//definimos la ventana y el framerate
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;

	//fuente y texto para el texto que cuenta los ragdolls
	fuente = new Font;
	textContador = new Text;
	fuente->loadFromFile("assets/arial.ttf");
	textContador->setFont(*fuente);
	textContador->setCharacterSize(15);
	textContador->setPosition(5, 5);
	textContador->setString("CONTADOR DE RAGDOLLS:" + std::to_string(contadorRagdolls));

	//textura y sprites de los íconos de cajas correctas e incorrectas
	cajaCorrectaTx = new Texture;
	cajaCorrectaTx->loadFromFile("assets/block.png");
	cajaIncorrectaTx = new Texture;
	cajaIncorrectaTx->loadFromFile("assets/block2.png");

	cajaCorrecta1 = new Sprite;
	cajaCorrecta1->setTexture(*cajaIncorrectaTx);
	cajaCorrecta1->setPosition(80,0.5);
	
	cajaCorrecta2 = new Sprite;
	cajaCorrecta2->setTexture(*cajaIncorrectaTx);
	cajaCorrecta2->setPosition(85, 0.5);

	cajaCorrecta3 = new Sprite;
	cajaCorrecta3->setTexture(*cajaIncorrectaTx);
	cajaCorrecta3->setPosition(90, 0.5);

	//aplicar la escala
	SetZoom();
	//iniciar físicas
	InitPhysics();

	//Textura y Sprite del menú inicio y el menú de información
	textura1 = new Texture;
	fondo = new Sprite;
	textura1->loadFromFile("assets/menuInicio.png");
	fondo->setTexture(*textura1);

	textura2 = new Texture;
	menuInfo = new Sprite;
	textura2->loadFromFile("assets/menuInfo.jpg");
	menuInfo->setTexture(*textura2);

	//ejecutar primero el menú inicio
	MenuInicio();

	//Establecer el nivel y su condición de incompleto
	currentLevel = 1;
	levelCompleted = false;
	//Establecer el contador de ragdolls en cero
	contadorRagdolls = 0;

		

}
//-------------------------------------------------------------------------------SEGUIR COMENTANDO
//el clásico gameloop
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
			std::cout << "No hay más niveles." << std::endl;
			wnd->close();
			break;
		}

		//Actualizar();
		//Dibujar();
		wnd->display();

	}
}

bool Game::CajaEnZona1(b2Body* caja1) {
	// Obtener la posición de la caja en el mundo de Box2D
	b2Vec2 pos = caja1->GetPosition();

	// Verificar si la posición de la caja está dentro de los límites de la zona (80, 80) a (100, 100)
	if (pos.x >= 80 && pos.x <= 96 && pos.y >= 72 && pos.y <= 95) {
		return true; // Está dentro de la zona
	}

	return false; // Fuera de la zona
}

bool Game::CajaEnZona2(b2Body* caja2) {
	// Obtener la posición de la caja en el mundo de Box2D
	b2Vec2 pos = caja2->GetPosition();

	// Verificar si la posición de la caja está dentro de los límites de la zona (80, 80) a (100, 100)
	if (pos.x >= 80 && pos.x <= 96 && pos.y >= 72 && pos.y <= 95) {
		return true; // Está dentro de la zona
	}

	return false; // Fuera de la zona
}

bool Game::CajaEnZona3(b2Body* caja3) {
	// Obtener la posición de la caja en el mundo de Box2D
	b2Vec2 pos = caja3->GetPosition();

	// Verificar si la posición de la caja está dentro de los límites de la zona (80, 80) a (100, 100)
	if (pos.x >= 80 && pos.x <= 96 && pos.y >= 72 && pos.y <= 95) {
		return true; // Está dentro de la zona
	}

	return false; // Fuera de la zona
}

void Game::Level1()
{
	// Lógica de actualización del nivel 1
	Actualizar(); // Actualiza las físicas del mundo, objetos, etc.

	// Dibujar objetos del nivel 1
	Dibujar(); // Aquí dibujas los objetos del nivel, ragdolls, etc.

	// Condición para pasar al siguiente nivel
	if (contadorRagdolls >= 10) {
		levelCompleted = true;
		NextLevel(); // Pasamos al siguiente nivel
	}
}

void Game::Level2()
{
	// Lógica de actualización del nivel 2
	Actualizar();
	// Dibujar objetos del nivel 2
	Dibujar();

	// Condición para pasar al siguiente nivel
	if (contadorRagdolls >= 20) {
		levelCompleted = true;
		NextLevel();
	}
}

// Método para el tercer nivel
void Game::Level3()
{
	// Lógica de actualización del nivel 3
	Actualizar();
	Dibujar();

	if (contadorRagdolls >= 30) {
		std::cout << "¡Felicidades, has completado el juego!" << std::endl;
		wnd->close();
	}
}

void Game::NextLevel()
{
	if (levelCompleted) {
		currentLevel++; // Incrementamos el nivel actual
		ResetLevel(); // Reiniciar los parámetros del nuevo nivel
	}
}

void Game::ResetLevel()
{
	
	// Aquí puedes restablecer el estado de los objetos para el nuevo nivel
	InitPhysics(); // Por ejemplo, reiniciar las físicas
	SetZoom();     // Reajustar la cámara si es necesario
	levelCompleted = false; // Restablecer la bandera de nivel completado


	//para limpiar los ragdolls
	for (auto& ragdoll : ragdolls) {
		delete ragdoll;  // Eliminar cada ragdoll de la memoria
	}
	ragdolls.clear();
}
void Game::CajasCorrectas() 
{
	if (CajaEnZona1(caja1)) {
		cajaCorrecta1->setTexture(*cajaCorrectaTx);
	}
	else {
		cajaCorrecta1->setTexture(*cajaIncorrectaTx);
	}

	if (CajaEnZona2(caja2)) {
		cajaCorrecta2->setTexture(*cajaCorrectaTx);
	}
	else {
		cajaCorrecta2->setTexture(*cajaIncorrectaTx);
	}

	if (CajaEnZona3(caja3)) {
		cajaCorrecta3->setTexture(*cajaCorrectaTx);
	}
	else {
		cajaCorrecta3->setTexture(*cajaIncorrectaTx);
	}
}

//actualiza el phyworld
void Game::Actualizar()
{
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();

	textContador->setString("CONTADOR DE RAGDOLLS:" + std::to_string(contadorRagdolls));

	CajasCorrectas();
	

}
//para dibujar objetos, no se usa pero lo dejamos para cuando hagamos el final con los sprites
void Game::Dibujar()
{
	m_Avatar1->Actualizar();
	m_Avatar1->Dibujar(*wnd);
	m_Avatar2->Actualizar();
	m_Avatar2->Dibujar(*wnd);
	m_Avatar3->Actualizar();
	m_Avatar3->Dibujar(*wnd);
	

	for (auto& ragdoll : ragdolls) {
		ragdoll->Actualizar(); // Llama a la función que actualiza el sprite del torso
	}

	for (auto& ragdoll : ragdolls) {
		ragdoll->Dibujar(*wnd); // Llama a la función que dibuja el sprite del torso
	}

	wnd->draw(*textContador);
	wnd->draw(*cajaCorrecta1);
	wnd->draw(*cajaCorrecta2);
	wnd->draw(*cajaCorrecta3);

}

void Game::Eventos()
{

	//fijar la posición del cañon
	b2Vec2 cannonPosition(6.0f, 93.0f);

	//sacar la posición del cursor del mouse y pasarla a la escala de box2d
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*wnd);
	sf::Vector2f worldMousePosition = wnd->mapPixelToCoords(mousePosition);
	b2Vec2 mouseWorldPosition(mousePosition.x * scaleX, mousePosition.y * scaleY);

	//establecer la distancia entre el cursor y el cañon
	b2Vec2 displacement = mouseWorldPosition - cannonPosition;
	//obtener el ángulo del vector
	float angle = atan2(displacement.y, displacement.x);


	// Calcular la distancia entre el cañon y el cursor
	float distance = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
	//crear la potencia del cañon en base a la distancia del cursor
	float fuerza = distance * 15;



	//pasar el angulo a grados - por si fuera necesario más adelante//
	float angleInDegrees = angle * 180.0f / b2_pi;


	//el cañon rota al ángulo en que se encuentra el cursor
	cannon->SetTransform(b2Vec2(6.0f, 93.0f), angle);

	//la mitad aproximada de la longitud del cañon para obtener la punta
	float cannonLargo = 5.5f;

	//obtener la posición de la punta del cañon ajustandola al angulo de rotación
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
		{
			if (ragdolls.size() >= 5) {
				// Eliminar el primer ragdoll si ya hay 5 ragdolls
				delete ragdolls.front();
				ragdolls.pop_front();
			}
			//crear el ragdoll en la punta del cañon
			Ragdoll* ragdoll = new Ragdoll(phyWorld, cannonTipPosition);
			//aplicar el impulso basado en la fuerza que está afectada por la distancia del cursor y el ángulo
			b2Vec2 impulse(fuerza * cos(angleInDegrees * b2_pi / 180.0f), fuerza * sin(angleInDegrees * b2_pi / 180.0f));
			//se aplica el impulso
			ragdoll->applyImpulse(impulse);
			ragdolls.push_back(ragdoll);
			contadorRagdolls++;
			break;
		}
		// COMPROBAR LAS POSICIONES //
		case Event::KeyPressed:
			if (evt.key.code == sf::Keyboard::Space) {
				// Obtener la posición del objeto obstaPrueba en el mundo de Box2D
				b2Vec2 position = caja1->GetPosition();

				// Imprimir la posición en consola
				std::cout << "obstaPrueba está en posición: (" << position.x << ", " << position.y << ")" << std::endl;

				std::cout << "Posición del cursor: (" << worldMousePosition.x << ", " << worldMousePosition.y << ")" << std::endl;
			}
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
	textContador->setScale(scaleX, scaleY);
	cajaCorrecta1->setScale(0.4 * scaleX, 0.4 * scaleY);
	cajaCorrecta2->setScale(0.4 * scaleX, 0.4 * scaleY);
	cajaCorrecta3->setScale(0.4 * scaleX, 0.4 * scaleY);
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

	//creamos dos obstáculos estáticos
	b2Body* obstaculo1 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 12, 2);
	obstaculo1->SetTransform(b2Vec2(60.0f, 20.0f), 0.0f);

	b2Body* obstaculo2 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 12, 2);
	obstaculo2->SetTransform(b2Vec2(60.0f, 40.0f), 0.0f);

	b2Body* obstaculo3 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 12, 2);
	obstaculo3->SetTransform(b2Vec2(60.0f, 60.0f), 0.0f);

	b2Body* obstaculo4 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 2, 20);
	obstaculo4->SetTransform(b2Vec2(80.0f, 90.0f), 0.0f);


	
	//creamos la base del cañon
	b2Body* cannon_base = Box2DHelper::CreateCircularStaticBody(phyWorld, 2);
	cannon_base->SetTransform(b2Vec2(6.0f, 93.0f), 0.0f);

	//creamos el cañon
	cannon = Box2DHelper::CreateRectangularStaticBody(phyWorld, 11, 1.2f);

	//creamos las cajas
	caja1	= Box2DHelper::CreateRectangularDynamicBody(phyWorld, 7, 7, 0.1f, 0.1f, 0.1f);
	caja1->SetTransform(b2Vec2(60.0f, 30.0f), 0.0f);

	//creamos dos obstàculos dinámicos
	caja2 = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 7, 7, 0.1f, 0.1f, 0.1f);
	caja2->SetTransform(b2Vec2(60.0f, 10.0f), 0.0f);

	caja3 = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 7, 7, 0.1f, 0.1f, 0.1f);
	caja3->SetTransform(b2Vec2(60.0f, 50.0f), 0.0f);

	//asignamos la textura al sprite y al avatar
	t.loadFromFile("assets/block.png");
	sf::Sprite* s = new sf::Sprite(t);
	
	
	m_Avatar1 = new Avatar(caja1, s);
	m_Avatar2 = new Avatar(caja2, s);
	m_Avatar3 = new Avatar(caja3, s);


}


void Game::MenuInicio() {




	wnd->setView(wnd->getDefaultView());

	// Mostrar el menú
	while (wnd->isOpen()) {
		sf::Event event;
		while (wnd->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				wnd->close();
				return;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Num1) {
					// Opción para iniciar el juego
					SetZoom();
					MenuInfo();
					return;  // Salimos del menú y continuamos con el juego
				}
				else if (event.key.code == sf::Keyboard::Num2) {
					// Opción para salir
					wnd->close();
					return;
				}
			}
		}

		// Dibujar el menú
		wnd->clear(sf::Color::Black);
		wnd->draw(*fondo);
		wnd->display();
	}
	
}


void Game::MenuInfo() {




	wnd->setView(wnd->getDefaultView());

	// Mostrar el menú
	while (wnd->isOpen()) {
		sf::Event event;
		while (wnd->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				wnd->close();
				return;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					// Opción para continuar el juego
					SetZoom();
					return;  // Salimos del menú y continuamos con el juego
				}
			}
		}

		// Dibujar el menú
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