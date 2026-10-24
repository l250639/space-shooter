//#include<iostream>
//#include<SFML/Graphics.hpp>
//#include<fstream>
//
//using namespace std;
//
//// Save/Load functions - MODIFIED SIGNATURES
//void SaveHighScore(int score)
//{
//	ofstream file("highscore.txt");
//	if (file.is_open())
//	{
//		file << score;
//		file.close();
//	}
//}
//
//int LoadHighScore()
//{
//	ifstream file("highscore.txt");
//	int score = 0;
//	if (file.is_open())
//	{
//		file >> score;
//		file.close();
//	}
//	return score;
//}
//
//// MODIFIED: Added bool shieldActive
//void SaveGame(int level, int lives, int score, float playerX, float playerY, bool bossActive, int bossLives, bool shieldActive)
//{
//	ofstream file("savegame.txt");
//	if (file.is_open())
//	{
//		file << level << endl;
//		file << lives << endl;
//		file << score << endl;
//		file << playerX << endl;
//		file << playerY << endl;
//		file << bossActive << endl;
//		file << bossLives << endl;
//		file << shieldActive << endl; // ADDED
//		file.close();
//	}
//}
//
//// MODIFIED: Added bool& shieldActive
//bool LoadGame(int& level, int& lives, int& score, float& playerX, float& playerY, bool& bossActive, int& bossLives, bool& shieldActive)
//{
//	ifstream file("savegame.txt");
//	if (file.is_open())
//	{
//		file >> level;
//		file >> lives;
//		file >> score;
//		file >> playerX;
//		file >> playerY;
//		file >> bossActive;
//		file >> bossLives;
//		file >> shieldActive; // ADDED
//		file.close();
//		return true;
//	}
//	return false;
//}
//
//bool RectRectCollision(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
//{
//	sf::FloatRect bounds1 = rect1.getGlobalBounds();
//	sf::FloatRect bounds2 = rect2.getGlobalBounds();
//	return bounds1.intersects(bounds2);
//}
//
//bool SpriteRectCollision(const sf::Sprite& sprite, const sf::RectangleShape& rect)
//{
//	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
//	sf::FloatRect rectBounds = rect.getGlobalBounds();
//	return spriteBounds.intersects(rectBounds);
//}
//
//// MODIFIED: Added bool& shieldActive
//void HandleCollisions(
//	sf::Sprite aliens[], bool alive[], int totalAliens,
//	sf::RectangleShape bullets[], bool status[], int totalBullets,
//	sf::RectangleShape& player,
//	sf::Sprite& boss, int& bossLives, bool& bossActive,
//	sf::RectangleShape bossBullets[], bool bossBulletStatus[], int totalBossBullets,
//	sf::Sprite& powerUp, bool& powerUpActive,
//	int& score, int& lives, bool& shieldActive // ADDED
//)
//{
//	// Player bullets vs aliens
//	for (int i = 0; i < totalBullets; i++)
//	{
//		if (!status[i]) continue;
//
//		for (int j = 0; j < totalAliens; j++)
//		{
//			if (!alive[j]) continue;
//
//			if (SpriteRectCollision(aliens[j], bullets[i]))
//			{
//				alive[j] = false;
//				status[i] = false;
//				score += 10;
//			}
//		}
//	}
//
//	// Player bullets vs boss
//	if (bossActive)
//	{
//		for (int i = 0; i < totalBullets; i++)
//		{
//			if (!status[i]) continue;
//
//			if (SpriteRectCollision(boss, bullets[i]))
//			{
//				status[i] = false;
//				bossLives--;
//				score += 50;
//
//				if (bossLives <= 0)
//				{
//					bossActive = false;
//				}
//			}
//		}
//	}
//
//	// Aliens vs player
//	for (int j = 0; j < totalAliens; j++)
//	{
//		if (!alive[j]) continue;
//
//		if (SpriteRectCollision(aliens[j], player))
//		{
//			alive[j] = false;
//			if (shieldActive) // MODIFIED: Check shield
//				shieldActive = false;
//			else
//				lives -= 1; // MODIFIED: Only lose life if no shield
//		}
//	}
//
//	// Boss vs player
//	if (bossActive && SpriteRectCollision(boss, player))
//	{
//		if (shieldActive) // MODIFIED: Check shield
//			shieldActive = false;
//		else
//			lives -= 1; // MODIFIED: Only lose life if no shield
//		bossActive = false;
//	}
//
//	// Boss bullets vs player
//	for (int i = 0; i < totalBossBullets; i++)
//	{
//		if (!bossBulletStatus[i]) continue;
//
//		if (RectRectCollision(bossBullets[i], player))
//		{
//			bossBulletStatus[i] = false;
//			if (shieldActive) // MODIFIED: Check shield
//				shieldActive = false;
//			else
//				lives -= 1; // MODIFIED: Only lose life if no shield
//		}
//	}
//
//	// Power-up vs player
//	if (powerUpActive && SpriteRectCollision(powerUp, player))
//	{
//		powerUpActive = false;
//		shieldActive = true; // MODIFIED: Grant shield instead of life
//		score += 25;
//	}
//}
//
//bool CheckAllAliensKilled(bool alive[], int totalAliens)
//{
//	for (int i = 0; i < totalAliens; i++)
//	{
//		if (alive[i])
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//void LEVEL(sf::Sprite aliens[], bool alive[], int level, sf::Texture& alientexture)
//{
//	int total = 10 + (level - 1) * 10;
//	if (total > 50)
//		total = 50;
//
//	for (int i = 0; i < total; i++)
//	{
//		aliens[i].setTexture(alientexture);
//		aliens[i].setScale(0.2f, 0.2f);
//
//		float x = rand() % 1860 + 50;
//		float y = -(rand() % 250);
//		aliens[i].setPosition(x, y);
//		alive[i] = true;
//	}
//
//	for (int i = total; i < 50; i++)
//	{
//		alive[i] = false;
//	}
//}
//
//void Alienmovement(sf::Sprite aliens[], bool alive[], float& alienspeed)
//{
//	for (int i = 0; i < 50; i++)
//	{
//		if (alive[i])
//		{
//			aliens[i].move(sf::Vector2f(0.f, alienspeed));
//
//			float check = aliens[i].getPosition().y;
//			if (check > 1080)
//			{
//				float x = rand() % 1900;
//				float y = -(rand() % 50);
//				aliens[i].setPosition(x, y);
//			}
//		}
//	}
//}
//
//void DrawAliens(sf::RenderWindow& window, sf::Sprite aliens[], bool alive[])
//{
//	for (int i = 0; i < 50; i++)
//	{
//		if (alive[i])
//			window.draw(aliens[i]);
//	}
//}
//
//void InitializeBoss(sf::Sprite& boss, sf::Texture& bossTexture, int level)
//{
//	if (level == 1)
//	{
//		bossTexture.loadFromFile("boss5.png");
//		boss.setTexture(bossTexture);
//		boss.setScale(0.2f, 0.2f);
//		boss.setPosition(1960 / 2.f - 60.f, 100.f);
//	}
//	else
//	{
//		if (level == 2)
//			bossTexture.loadFromFile("boss2.png");
//		else if (level == 3)
//			bossTexture.loadFromFile("boss1.png");
//		else if (level == 4)
//			bossTexture.loadFromFile("boss3.png");
//		else if (level == 5)
//			bossTexture.loadFromFile("boss4.png");
//		boss.setTexture(bossTexture);
//		boss.setScale(0.5f, 0.5f);
//		boss.setPosition(1960 / 2.f - 60.f, 100.f);
//	}
//}
//
//void MoveBoss(sf::Sprite& boss, float& bossDirection, float bossSpeed)
//{
//	boss.move(bossDirection * bossSpeed, 0);
//
//	float bossX = boss.getPosition().x;
//	if (bossX < 50 || bossX > 1700)
//	{
//		bossDirection *= -1;
//	}
//}
//
//void FireBossBullets(sf::RectangleShape bossBullets[], bool bossBulletStatus[], sf::Sprite& boss, sf::Clock& bossClock)
//{
//	if (bossClock.getElapsedTime().asSeconds() > 0.8f)
//	{
//		for (int i = 0; i < 50; i++)
//		{
//			if (!bossBulletStatus[i])
//			{
//				bossBullets[i].setFillColor(sf::Color::Red);
//				bossBullets[i].setSize(sf::Vector2f(10.f, 20.f));
//
//				sf::FloatRect bossBounds = boss.getGlobalBounds();
//				bossBullets[i].setPosition(
//					bossBounds.left + bossBounds.width / 2 - 4.f,
//					bossBounds.top + bossBounds.height
//				);
//
//				bossBulletStatus[i] = true;
//				bossClock.restart();
//				break;
//			}
//		}
//	}
//}
//
//void UpdateBossBullets(sf::RectangleShape bossBullets[], bool bossBulletStatus[], float speed)
//{
//	for (int i = 0; i < 50; i++)
//	{
//		if (bossBulletStatus[i])
//		{
//			bossBullets[i].move(0, speed);
//
//			if (bossBullets[i].getPosition().y > 1080)
//				bossBulletStatus[i] = false;
//		}
//	}
//}
//
//void DrawBossBullets(sf::RenderWindow& window, sf::RectangleShape bossBullets[], bool bossBulletStatus[])
//{
//	for (int i = 0; i < 50; i++)
//	{
//		if (bossBulletStatus[i])
//			window.draw(bossBullets[i]);
//	}
//}
//
//void SpawnPowerUp(sf::Sprite& powerUp, sf::Texture& powerUpTexture)
//{
//	powerUp.setTexture(powerUpTexture);
//	powerUp.setScale(0.2f, 0.2f);
//
//	float x = rand() % 1800 + 80;
//	float y = -(rand() % 100);
//	powerUp.setPosition(x, y);
//}
//
//void MovePowerUp(sf::Sprite& powerUp, float speed)
//{
//	powerUp.move(0, speed);
//
//	if (powerUp.getPosition().y > 1080)
//	{
//		float x = rand() % 1800 + 80;
//		float y = -(rand() % 500);
//		powerUp.setPosition(x, y);
//	}
//}
//
//void parallelexinitiaization(sf::RectangleShape parallexbullet[])
//{
//	for (int i = 0; i < 250; i++)
//	{
//		float x = rand() % 1860 + 50;
//		float y = -(rand() % 1080);
//
//		parallexbullet[i].setFillColor(sf::Color::Black);
//		parallexbullet[i].setSize(sf::Vector2f(2.f, 5.f));
//		parallexbullet[i].setPosition(x, y);
//	}
//}
//
//void parallelexMovement(sf::RectangleShape parallexbullet[], float paralllexspeed)
//{
//	for (int i = 0; i < 250; i++)
//	{
//		parallexbullet[i].move(sf::Vector2f(0.f, paralllexspeed));
//		float check = parallexbullet[i].getPosition().y;
//
//		if (check > 1080)
//		{
//			float x = rand() % 1900 + 20;
//			float y = -(rand() % 1080);
//			parallexbullet[i].setPosition(x, y);
//		}
//	}
//}
//
//void parallexdisplay(sf::RectangleShape parallexbullet[], sf::RenderWindow& window)
//{
//	for (int i = 0; i < 250; i++)
//	{
//		window.draw(parallexbullet[i]);
//	}
//}
//
//void firebullets(sf::RectangleShape bullets[], bool status[], sf::RectangleShape& player)
//{
//	for (int i = 0; i < 100; i++)
//	{
//		if (!status[i])
//		{
//			bullets[i].setFillColor(sf::Color::Black);
//			bullets[i].setOutlineColor(sf::Color::Yellow);
//			bullets[i].setOutlineThickness(3.f);
//			bullets[i].setSize(sf::Vector2f(5.f, 15.f));
//			bullets[i].setPosition(
//				player.getPosition().x + 30.f, player.getPosition().y
//			);
//
//			status[i] = true;
//			break;
//		}
//	}
//}
//
//void updatebullets(sf::RectangleShape bullets[], bool status[], float speed)
//{
//	for (int i = 0; i < 100; i++)
//	{
//		if (status[i])
//		{
//			bullets[i].move(0, -speed);
//		}
//		if (bullets[i].getPosition().y + bullets[i].getSize().y < 0)
//			status[i] = false;
//	}
//}
//
//void drawbullets(sf::RenderWindow& window, sf::RectangleShape bullets[], bool status[])
//{
//	for (int i = 0; i < 100; i++)
//	{
//		if (status[i])
//			window.draw(bullets[i]);
//	}
//}
//
//void handleinput(sf::RenderWindow& window, sf::RectangleShape& player, float speed)
//{
//	float WindowWidth = (float)window.getSize().x;
//	float playerwidth = player.getSize().x;
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//	{
//		if (player.getPosition().x > 20)
//		{
//			player.move(-speed, 0);
//		}
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//	{
//		if (player.getPosition().x + playerwidth < WindowWidth)
//		{
//			player.move(speed, 0);
//		}
//	}
//}
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(1960, 1080), "Alien Shooter");
//	sf::RectangleShape player;
//	sf::Texture Playertexture;
//
//	if (!Playertexture.loadFromFile("ship.png"))
//	{
//		cout << "Error loading ship texture" << endl;
//	}
//
//	sf::Texture Alientexture;
//	if (!Alientexture.loadFromFile("alien.png"))
//	{
//		cout << "Error loading alien texture" << endl;
//	}
//
//	sf::Texture BossTexture;
//	if (!BossTexture.loadFromFile("boss1.png"))
//	{
//		cout << "Error loading boss texture" << endl;
//	}
//
//	sf::Texture PowerUpTexture;
//	if (!PowerUpTexture.loadFromFile("life.png"))
//	{
//		cout << "Error loading powerup texture" << endl;
//	}
//
//	player.setSize(sf::Vector2f(100.f, 100.f));
//	player.setPosition(1960 / 2.f, 1000.f);
//	player.setTexture(&Playertexture);
//
//	float playerspeed = 4.f;
//	int level = 1;
//	const int MAX_LEVELS = 5;
//	int lives = 3;
//	int score = 0;
//
//	float parallexspeed = 0.3f + 0.3f * (level);
//	sf::RectangleShape parallexbullet[250];
//
//	sf::Font font;
//	if (!font.loadFromFile("ONEDAY.otf"))
//	{
//		cout << "Error loading font!" << endl;
//	}
//
//	sf::Text scoretext;
//	scoretext.setFont(font);
//	scoretext.setFillColor(sf::Color::Black);
//	scoretext.setCharacterSize(36);
//	scoretext.setPosition(15.f, 10.f);
//
//	sf::Text livestext;
//	livestext.setFont(font);
//	livestext.setFillColor(sf::Color::Black);
//	livestext.setCharacterSize(32);
//	livestext.setPosition(15.f, 80.f);
//
//	// ADDED: Text object for shield status
//	sf::Text shieldText;
//	shieldText.setFont(font);
//	shieldText.setFillColor(sf::Color::Blue);
//	shieldText.setCharacterSize(32);
//	shieldText.setString("SHIELD ACTIVE!");
//	shieldText.setPosition(15.f, 80.f);
//
//	sf::Text leveltext;
//	leveltext.setFont(font);
//	leveltext.setFillColor(sf::Color::Black);
//	leveltext.setCharacterSize(32);
//	leveltext.setPosition(15.f, 140.f);
//
//	// Game states: 0=main menu, 1=playing, 2=gameover, 3=paused, 4=won, 5=instructions
//	int gamestate = 0;
//	int menuSelection = 0; // 0=Start, 1=Load, 2=Instructions, 3=Exit
//	int highScore = LoadHighScore();
//
//	float alienspeed = 0.3f + 0.2f * (level);
//
//	const int Maxbullets = 100;
//	sf::RectangleShape bullets[Maxbullets];
//	bool status[Maxbullets] = { false };
//
//	const int maxaliens = 50;
//	sf::Sprite Aliens[maxaliens];
//	bool alive[maxaliens] = { false };
//
//	// Boss variables
//	sf::Sprite boss;
//	int bossLives = 0;
//	bool bossActive = false;
//	bool bossSpawned = false;
//	float bossDirection = 1.0f;
//	float bossSpeed = 2.0f;
//	sf::Clock bossShotClock;
//
//	const int MaxBossBullets = 50;
//	sf::RectangleShape bossBullets[MaxBossBullets];
//	bool bossBulletStatus[MaxBossBullets] = { false };
//
//	// Power-up variables
//	sf::Sprite powerUp;
//	bool powerUpActive = false;
//	sf::Clock powerUpSpawnClock;
//	bool shieldActive = false; // ADDED: Shield state variable
//
//	parallelexinitiaization(parallexbullet);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//
//			if (event.type == sf::Event::KeyPressed)
//			{
//				// Main Menu Navigation
//				if (gamestate == 0)
//				{
//					if (event.key.code == sf::Keyboard::Up)
//					{
//						menuSelection--;
//						if (menuSelection < 0) menuSelection = 3;
//					}
//					else if (event.key.code == sf::Keyboard::Down)
//					{
//						menuSelection++;
//						if (menuSelection > 3) menuSelection = 0;
//					}
//					else if (event.key.code == sf::Keyboard::Enter)
//					{
//						if (menuSelection == 0) // Start New Game
//						{
//							level = 1;
//							lives = 3;
//							score = 0;
//							alienspeed = 0.3f + 0.2f * level;
//							parallexspeed = 0.3f + 0.3f * level;
//							bossActive = false;
//							bossSpawned = false;
//							powerUpActive = false;
//							shieldActive = false; // ADDED: Initialize shield
//							LEVEL(Aliens, alive, level, Alientexture);
//							player.setPosition(1960 / 2.f, 1000.f);
//							gamestate = 1;
//						}
//						else if (menuSelection == 1) // Load Game
//						{
//							float playerX, playerY;
//							// MODIFIED: Added shieldActive to LoadGame call
//							if (LoadGame(level, lives, score, playerX, playerY, bossActive, bossLives, shieldActive))
//							{
//								alienspeed = 0.3f + 0.2f * level;
//								parallexspeed = 0.3f + 0.3f * level;
//								LEVEL(Aliens, alive, level, Alientexture);
//								player.setPosition(playerX, playerY);
//								powerUpActive = false;
//								bossSpawned = bossActive;
//								if (bossActive)
//								{
//									InitializeBoss(boss, BossTexture, level);
//								}
//								gamestate = 1;
//							}
//						}
//						else if (menuSelection == 2) // Instructions
//						{
//							gamestate = 5;
//						}
//						else if (menuSelection == 3) // Exit
//						{
//							window.close();
//						}
//					}
//				}
//				// Instructions screen
//				else if (gamestate == 5)
//				{
//					if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
//					{
//						gamestate = 0;
//					}
//				}
//				// Pause/Unpause
//				else if (gamestate == 1 && event.key.code == sf::Keyboard::P)
//				{
//					gamestate = 3;
//				}
//				else if (gamestate == 3)
//				{
//					if (event.key.code == sf::Keyboard::P)
//					{
//						gamestate = 1;
//					}
//					else if (event.key.code == sf::Keyboard::S)
//					{
//						// MODIFIED: Added shieldActive to SaveGame call
//						SaveGame(level, lives, score, player.getPosition().x, player.getPosition().y, bossActive, bossLives, shieldActive);
//					}
//					else if (event.key.code == sf::Keyboard::M)
//					{
//						gamestate = 0;
//						menuSelection = 0;
//					}
//				}
//				// Shooting
//				else if (gamestate == 1 && event.key.code == sf::Keyboard::Space)
//				{
//					firebullets(bullets, status, player);
//				}
//				// Restart after game over
//				else if (gamestate == 2 && event.key.code == sf::Keyboard::Space)
//				{
//					level = 1;
//					lives = 3;
//					score = 0;
//					alienspeed = 0.3f + 0.2f * level;
//					parallexspeed = 0.3f + 0.3f * level;
//					bossActive = false;
//					bossSpawned = false;
//					powerUpActive = false;
//					shieldActive = false; // ADDED: Initialize shield
//					LEVEL(Aliens, alive, level, Alientexture);
//					player.setPosition(1960 / 2.f, 1000.f);
//					gamestate = 1;
//				}
//				// Continue after winning
//				else if (gamestate == 4 && event.key.code == sf::Keyboard::Enter)
//				{
//					gamestate = 0;
//					menuSelection = 0;
//				}
//			}
//		}
//
//		// Update parallax in all states
//		parallelexMovement(parallexbullet, 0.5f);
//
//		if (gamestate == 1) // Playing
//		{
//			Alienmovement(Aliens, alive, alienspeed);
//			handleinput(window, player, playerspeed);
//			updatebullets(bullets, status, 10.f);
//
//			// Check if all aliens killed and spawn boss
//			if (CheckAllAliensKilled(alive, maxaliens) && !bossSpawned)
//			{
//				bossActive = true;
//				bossSpawned = true;
//				bossLives = level + 1;
//				InitializeBoss(boss, BossTexture, level);
//				bossShotClock.restart();
//			}
//
//			// Boss behavior
//			if (bossActive)
//			{
//				MoveBoss(boss, bossDirection, bossSpeed);
//				FireBossBullets(bossBullets, bossBulletStatus, boss, bossShotClock);
//			}
//
//			UpdateBossBullets(bossBullets, bossBulletStatus, 5.f);
//
//			// Power-up spawning
//			if (!powerUpActive && powerUpSpawnClock.getElapsedTime().asSeconds() > 15.f)
//			{
//				SpawnPowerUp(powerUp, PowerUpTexture);
//				powerUpActive = true;
//				powerUpSpawnClock.restart();
//			}
//
//			if (powerUpActive)
//			{
//				MovePowerUp(powerUp, 2.f);
//			}
//
//			// MODIFIED: Added shieldActive to HandleCollisions call
//			HandleCollisions(Aliens, alive, 50, bullets, status, 100, player,
//				boss, bossLives, bossActive, bossBullets, bossBulletStatus, 50,
//				powerUp, powerUpActive, score, lives, shieldActive);
//
//			// Check if boss defeated
//			if (bossSpawned && !bossActive)
//			{
//				level++;
//
//				if (level > MAX_LEVELS)
//				{
//					if (score > highScore)
//					{
//						highScore = score;
//						SaveHighScore(highScore);
//					}
//					gamestate = 4;
//				}
//				else
//				{
//					alienspeed = 0.3f + 0.2f * level;
//					parallexspeed = 0.3f + 0.3f * level;
//					LEVEL(Aliens, alive, level, Alientexture);
//					player.setPosition(1960 / 2.f, 1000.f);
//					bossSpawned = false;
//				}
//			}
//
//			if (lives <= 0)
//			{
//				if (score > highScore)
//				{
//					highScore = score;
//					SaveHighScore(highScore);
//				}
//				gamestate = 2;
//			}
//
//			// MODIFIED: Display text handling
//			scoretext.setString("Score: " + to_string(score));
//
//			// Update livestext only if shield is not active
//			if (!shieldActive)
//			{
//				livestext.setString("Lives: " + to_string(lives));
//			}
//			// Note: shieldText is statically set to "SHIELD ACTIVE!"
//
//			leveltext.setString("Level: " + to_string(level));
//		}
//
//		window.clear(sf::Color::White);
//
//		if (gamestate == 0) // Main Menu
//		{
//			parallexdisplay(parallexbullet, window);
//
//			// ... (Menu display logic remains the same)
//			sf::Text title;
//			title.setFont(font);
//			title.setFillColor(sf::Color::Black);
//			title.setCharacterSize(80);
//			title.setString("ALIEN SHOOTER");
//			title.setPosition(600.f, 150.f);
//
//			sf::Text option1, option2, option3, option4;
//
//			option1.setFont(font);
//			option1.setCharacterSize(40);
//			option1.setString("Start New Game");
//			option1.setPosition(750.f, 350.f);
//
//			option2.setFont(font);
//			option2.setCharacterSize(40);
//			option2.setString("Load Saved Game");
//			option2.setPosition(750.f, 430.f);
//
//			option3.setFont(font);
//			option3.setCharacterSize(40);
//			option3.setString("Instructions");
//			option3.setPosition(750.f, 510.f);
//
//			option4.setFont(font);
//			option4.setCharacterSize(40);
//			option4.setString("Exit");
//			option4.setPosition(750.f, 590.f);
//
//			if (menuSelection == 0)
//			{
//				option1.setFillColor(sf::Color::Red);
//				option1.setCharacterSize(45);
//			}
//			else
//				option1.setFillColor(sf::Color::Black);
//
//			if (menuSelection == 1)
//			{
//				option2.setFillColor(sf::Color::Red);
//				option2.setCharacterSize(45);
//			}
//			else
//				option2.setFillColor(sf::Color::Black);
//
//			if (menuSelection == 2)
//			{
//				option3.setFillColor(sf::Color::Red);
//				option3.setCharacterSize(45);
//			}
//			else
//				option3.setFillColor(sf::Color::Black);
//
//			if (menuSelection == 3)
//			{
//				option4.setFillColor(sf::Color::Red);
//				option4.setCharacterSize(45);
//			}
//			else
//				option4.setFillColor(sf::Color::Black);
//
//			sf::Text controls;
//			controls.setFont(font);
//			controls.setFillColor(sf::Color(50, 50, 50));
//			controls.setCharacterSize(24);
//			controls.setString("Use UP/DOWN arrows to navigate | Press ENTER to select");
//			controls.setPosition(550.f, 900.f);
//
//			sf::Text highScoreText;
//			highScoreText.setFont(font);
//			highScoreText.setFillColor(sf::Color::Black);
//			highScoreText.setCharacterSize(30);
//			highScoreText.setString("High Score: " + to_string(highScore));
//			highScoreText.setPosition(800.f, 800.f);
//
//			window.draw(title);
//			window.draw(option1);
//			window.draw(option2);
//			window.draw(option3);
//			window.draw(option4);
//			window.draw(controls);
//			window.draw(highScoreText);
//		}
//		else if (gamestate == 1) // Playing
//		{
//			parallexdisplay(parallexbullet, window);
//			window.draw(player);
//			drawbullets(window, bullets, status);
//			DrawAliens(window, Aliens, alive);
//
//			if (bossActive)
//			{
//				window.draw(boss);
//				DrawBossBullets(window, bossBullets, bossBulletStatus);
//			}
//
//			if (powerUpActive)
//			{
//				window.draw(powerUp);
//			}
//
//			window.draw(scoretext);
//			window.draw(leveltext);
//
//			// MODIFIED: Draw either lives or shield status
//			if (shieldActive)
//			{
//				window.draw(shieldText);
//			}
//			else
//			{
//				window.draw(livestext);
//			}
//		}
//		else if (gamestate == 2) // Game Over
//		{
//			sf::Text Gameover;
//			Gameover.setFillColor(sf::Color::Black);
//			Gameover.setFont(font);
//			Gameover.setCharacterSize(60);
//			Gameover.setString("Game Over!\nFinal Score: " + to_string(score) + "\nHigh Score: " + to_string(highScore) + "\n\nPress Space to Restart");
//			Gameover.setPosition(550.f, 350.f);
//
//			parallexdisplay(parallexbullet, window);
//			window.draw(Gameover);
//		}
//		else if (gamestate == 3) // Paused
//		{
//			parallexdisplay(parallexbullet, window);
//			window.draw(player);
//			drawbullets(window, bullets, status);
//			DrawAliens(window, Aliens, alive);
//
//			if (bossActive)
//			{
//				window.draw(boss);
//			}
//
//			if (powerUpActive)
//			{
//				window.draw(powerUp);
//			}
//
//			window.draw(scoretext);
//			window.draw(leveltext);
//
//			// MODIFIED: Draw either lives or shield status
//			if (shieldActive)
//			{
//				window.draw(shieldText);
//			}
//			else
//			{
//				window.draw(livestext);
//			}
//
//			sf::Text pauseText;
//			pauseText.setFillColor(sf::Color::Black);
//			pauseText.setFont(font);
//			pauseText.setCharacterSize(50);
//			pauseText.setString("PAUSED\n\nPress P to Continue\nPress S to Save Game\nPress M for Main Menu");
//			pauseText.setPosition(600.f, 350.f);
//
//			sf::RectangleShape pauseOverlay;
//			pauseOverlay.setSize(sf::Vector2f(1960, 1080));
//			pauseOverlay.setFillColor(sf::Color(255, 255, 255, 180));
//			window.draw(pauseOverlay);
//			window.draw(pauseText);
//		}
//		else if (gamestate == 4) // Won
//		{
//			sf::Text winText;
//			winText.setFillColor(sf::Color::Black);
//			winText.setFont(font);
//			winText.setCharacterSize(60);
//			winText.setString("YOU WON!\nAll Levels Cleared!\n\nFinal Score: " + to_string(score) + "\nHigh Score: " + to_string(highScore) + "\n\nPress Enter for Main Menu");
//			winText.setPosition(450.f, 300.f);
//
//			parallexdisplay(parallexbullet, window);
//			window.draw(winText);
//		}
//		else if (gamestate == 5) // Instructions
//		{
//			parallexdisplay(parallexbullet, window);
//
//			sf::Text instructionTitle;
//			instructionTitle.setFont(font);
//			instructionTitle.setFillColor(sf::Color::Black);
//			instructionTitle.setCharacterSize(60);
//			instructionTitle.setString("INSTRUCTIONS");
//			instructionTitle.setPosition(650.f, 80.f);
//
//			sf::Text instructions;
//			instructions.setFont(font);
//			instructions.setFillColor(sf::Color::Black);
//			instructions.setCharacterSize(30);
//			instructions.setString(
//				"CONTROLS:\n"
//				"  - LEFT/RIGHT Arrow Keys: Move your ship\n"
//				"  - SPACE: Fire bullets\n"
//				"  - P: Pause game\n"
//				"  - S (while paused): Save game\n\n"
//				"OBJECTIVE:\n"
//				"  - Destroy all aliens to face the boss\n"
//				"  - Defeat the boss to advance to next level\n"
//				"  - Complete all 5 levels to win!\n\n"
//				"LIVES SYSTEM:\n"
//				"  - You start with 3 lives\n"
//				"  - Lose a life when hit by aliens or boss\n"
//				"  - Collect power-ups for a SHIELD (one hit protection)\n" // MODIFIED INSTRUCTION
//				"  - Power-ups: 25 points + SHIELD\n" // MODIFIED INSTRUCTION
//				"  - Aliens: 10 points | Boss hits: 50 points\n"
//				"  - Beat your high score!"
//			);
//			instructions.setPosition(250.f, 200.f);
//
//			sf::Text backText;
//			backText.setFont(font);
//			backText.setFillColor(sf::Color(100, 100, 100));
//			backText.setCharacterSize(28);
//			backText.setString("Press ENTER or ESC to return to Main Menu");
//			backText.setPosition(550.f, 950.f);
//
//			window.draw(instructionTitle);
//			window.draw(instructions);
//			window.draw(backText);
//		}
//
//		window.display();
//	}
//
//	return 0;
//}