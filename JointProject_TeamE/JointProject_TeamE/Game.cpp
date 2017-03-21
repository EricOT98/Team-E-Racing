#include "Game.h"

#define MS_PER_UPDATE 10.0

Game::Game()
	: m_window(sf::VideoMode(800, 600, 32), "Joint Project Team E", sf::Style::Default),
	m_xboxController(CONTROLLER_ONE),
	m_reset(true)
{
	keyboardHandler = KeyboardHandler::GetInstance();
}

void Game::run()
{
	LevelLoader::load(m_level);
	g_resourceMgr.loadAssets(m_level);

	if (gl3wInit()) 
	{
		fprintf(stderr, "failed to initialize OpenGL\n");
		return;
	}
	if (!gl3wIsSupported(3, 2)) 
	{
		fprintf(stderr, "OpenGL 3.2 not supported\n");
		return;
	}
	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
		glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Maybe do shader loading in resource manager and pull them from there?
	m_crtShader.loadFromFile("Resources/Shaders/crt_shader.vert", "Resources/Shaders/crt_shader.frag");

	lightMapTexture.create(2000, 2000);
	lightmap.setTexture(lightMapTexture.getTexture());
	
	lightTexture = g_resourceMgr.textureHolder["CarLights"];
	lightTexture.setSmooth(true);
	
	light.setTexture(lightTexture);
	light.setTextureRect(sf::IntRect(0, 0, 512, 512));
	light.setOrigin(256.f, 256.f);
	m_player = new Player(m_xboxController);
	m_splashScreen = new SplashScreen();
	m_mainMenu = new MainMenu(m_reset);
	m_confirmationScreen = new ConfirmationScreen(m_window);
	m_difficultyScreen = new DifficultyScreen();
	m_displayOptions = new DisplayOptions();
	m_helpScreen = new HelpScreen();
	m_options = new Options();
	m_pauseScreen = new PauseScreen();
	m_soundOptions = new SoundOptions();
	m_trophyScreen = new TrophyScreen();
	m_upgradesScreen = new UpgradesScreen(m_level.m_carData, m_window.getSize().x);
	m_selectCarScreen = new SelectCarScreen(m_level.m_carData, m_player, m_window.getSize().x);
	m_selectCupScreen = new SelectCupScreen(m_level.m_enemyCarData, m_level.m_cupData, m_racers, m_window.getSize().x);
	m_track.setTrack(m_level);
	m_player->setPosition(m_track.getPlayerStartPosition() + sf::Vector2f(0.0f, 10.0f));
	m_player->setRotation(-90.0f);
	for (unsigned int i = 0; i <  m_track.getNumOfAICars(); i++)
	{
		AI *racer = new AI();
		racer->setWayPoints(m_level.m_waypoints);
		racer->setPosition(m_track.getAIStartPositions()->at(i) + sf::Vector2f(0.0f, 10.0f));
		m_racers.push_back(racer);
	}
	m_racers.push_back(m_player);
	m_screenManager.add(m_splashScreen);
	m_screenManager.add(m_mainMenu);
	m_screenManager.add(m_confirmationScreen);
	m_screenManager.add(m_difficultyScreen);
	m_screenManager.add(m_displayOptions);
	m_screenManager.add(m_helpScreen);
	m_screenManager.add(m_options);
	m_screenManager.add(m_pauseScreen);
	m_screenManager.add(m_soundOptions);
	m_screenManager.add(m_trophyScreen);
	m_screenManager.add(m_upgradesScreen);
	m_screenManager.add(m_selectCarScreen);
	m_screenManager.add(m_selectCupScreen);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	timeSinceLastUpdate = clock.restart();

	while (m_window.isOpen())
	{
		processEvents();

		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timeSinceLastUpdate.asMilliseconds());
			timeSinceLastUpdate = sf::Time::Zero;
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

void Game::processGameEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_window.close();
	}

	if (event.key.code >= 0 && event.key.code < sf::Keyboard::Key::KeyCount)
	{
		if (event.type == event.KeyPressed)
		{
			if (!KeyboardHandler::GetInstance()->m_keysUp[event.key.code])
			{
				KeyboardHandler::GetInstance()->m_keysDown[event.key.code] = true;
			}
		}
		else if (event.type == event.KeyReleased)
		{
			KeyboardHandler::GetInstance()->m_keysDown[event.key.code] = false;
			KeyboardHandler::GetInstance()->m_keysUp[event.key.code] = false;
		}
	}
}

void Game::update(double dt)
{
	if (m_screenManager.getState())
	{
		m_screenManager.update(m_xboxController);
	}
	else
	{
		if (m_reset)
		{
			resetGame();
		}
		m_track.update(m_racers);
		for (Racer *racer : m_racers)
			racer->update(dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			m_screenManager.setActive(GameState::MainMenu);
			m_window.setView(m_window.getDefaultView());
		}
	}
}

void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	if (m_screenManager.getState())
	{
		m_screenManager.render(m_window);
	}
	else
	{
		lightMapTexture.clear(sf::Color(50, 50, 80));
		for (Racer *racer : m_racers)
		{
			light.setScale(racer->m_spotLight.m_size);
			light.setColor(racer->m_spotLight.m_color);
			light.setPosition(racer->m_spotLight.m_position);
			
			lightMapTexture.draw(light, sf::RenderStates(sf::BlendAdd));
		}
		lightMapTexture.display();

		raceView.setCenter(m_player->getPosition());
		raceView.setSize(m_window.getView().getSize());
		m_window.setView(raceView);
		m_track.render(m_window);
		for (Racer *racer : m_racers)
			racer->render(m_window);

		lightmap.setPosition(0, 0);
		m_window.draw(lightmap, sf::RenderStates(sf::BlendMultiply));

#if 0
		// DEBUG(Darren): Debug drawing the AI nodes
		for (Waypoint waypoint : m_level.m_waypoints)
		{
			sf::CircleShape circle(5.0f);
			circle.setPosition(waypoint.m_position);
			circle.setFillColor(sf::Color::Blue);

			m_window.draw(circle);
		}
#endif
	}

	m_window.display();
}

void Game::resetGame()
{
	m_reset = false;
	m_transitionInGame = true;
	// Code Here...
}

void Game::applyShader(sf::RenderTarget &output)
{
	sf::Vector2f outputSize = static_cast<sf::Vector2f>(output.
		getSize());
	sf::VertexArray vertices(sf::TrianglesStrip, 4);
	vertices[0] = sf::Vertex(sf::Vector2f(0, 0),
		sf::Vector2f(0, 1));
	vertices[1] = sf::Vertex(sf::Vector2f(outputSize.x, 0),
		sf::Vector2f(1, 1));
	vertices[2] = sf::Vertex(sf::Vector2f(0, outputSize.y),
		sf::Vector2f(0, 0));
	vertices[3] = sf::Vertex(sf::Vector2f(outputSize),
		sf::Vector2f(1, 0));
	sf::Texture tex;
	tex.create(outputSize.x, outputSize.y);
	//m_crtShader.setParameter("screenTexture", )
	sf::RenderStates states;
	states.shader = &m_crtShader;
	states.blendMode = sf::BlendNone;
	output.draw(vertices, states);
}
