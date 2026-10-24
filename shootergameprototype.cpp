#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;



bool RectRectCollision(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
{
	sf::FloatRect bounds1 = rect1.getGlobalBounds();
	sf::FloatRect bounds2 = rect2.getGlobalBounds();
	return bounds1.intersects(bounds2);
}

bool SpriteRectCollision(const sf::Sprite& sprite, const sf::RectangleShape& rect)
{
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	sf::FloatRect rectBounds = rect.getGlobalBounds();
	return spriteBounds.intersects(rectBounds);
}

void HandleCollisions(
	sf::Sprite aliens[], bool alive[], int totalAliens,
	sf::RectangleShape bullets[], bool status[], int totalBullets,
	sf::RectangleShape& player,
	sf::Sprite& boss, int& bossLives, bool& bossActive,
	sf::RectangleShape bossBullets[], bool bossBulletStatus[], int totalBossBullets,
	sf::Sprite& powerUp, bool& powerUpActive,
	int& score, int& lives, bool &shieldActive
)
{
	// Player bullets vs aliens
	for (int i = 0; i < totalBullets; i++)
	{
		if (!status[i]) continue;

		for (int j = 0; j < totalAliens; j++)
		{
			if (!alive[j]) continue;

			if (SpriteRectCollision(aliens[j], bullets[i]))
			{
				alive[j] = false;
				status[i] = false;
				score += 10;
			}
		}
	}

	// Player bullets vs boss
	if (bossActive)
	{
		for (int i = 0; i < totalBullets; i++)
		{
			if (!status[i]) continue;

			if (SpriteRectCollision(boss, bullets[i]))
			{
				status[i] = false;
				bossLives--;
				score += 50;

				if (bossLives <= 0)
				{
					bossActive = false;
				}
			}
		}
	}

	// Aliens vs player
	for (int j = 0; j < totalAliens; j++)
	{
		if (!alive[j]) continue;

		if (SpriteRectCollision(aliens[j], player))
		{
			alive[j] = false;
			if (shieldActive)				// agr shield active hai to life kam nai ho gi collsion p, mgr collision k baad shield khtam yani false ho jai gi
				shieldActive = false;
			else                            // agr shield nai hai to life collision p aik kaam ho jai gi
			lives -= 1;
		}
	}

	// Boss vs player
	if (bossActive && SpriteRectCollision(boss, player))                 // Yay code itna necessary nai cuz alien vertically move nai kra ra, is liay rakha hai k agr baad mai is ko bhi kahi nechay move krnay ka na kha jai    
	{
		lives -= 1;
		bossActive = false; // Boss ship sai takranay k baad mar jai ga 
	}

	// Boss bullets vs player
	for (int i = 0; i < totalBossBullets; i++)
	{
		if (!bossBulletStatus[i]) 
			continue;

		if (RectRectCollision(bossBullets[i], player))
		{    
			bossBulletStatus[i] = false;
			if (shieldActive)
				shieldActive = false;
			else
			lives -= 1;
		}
	}

	// Power-up vs player
	if (powerUpActive && SpriteRectCollision(powerUp, player))
	{
		powerUpActive = false;
		shieldActive = true;
		//lives += 1;
		score += 25;
	}
}

bool CheckAllAliensKilled(bool alive[], int totalAliens)
{
	for (int i = 0; i < totalAliens; i++)
	{
		if (alive[i])
		{
			return false;
		}
	}
	return true;
}

void LEVEL(sf::Sprite aliens[], bool alive[], int level, sf::Texture& alientexture)
{
	int total = 10 + (level - 1) * 10;
	if (total > 50)
		total = 50;

	for (int i = 0; i < total; i++)
	{
		aliens[i].setTexture(alientexture);
		aliens[i].setScale(0.2f, 0.2f);

		float x = rand() % 1860 + 50;
		float y = -(rand() % 250);
		aliens[i].setPosition(x, y);
		alive[i] = true;
	}

	for (int i = total; i < 50; i++)
	{
		alive[i] = false;
	}
}

void Alienmovement(sf::Sprite aliens[], bool alive[], float& alienspeed)
{
	for (int i = 0; i < 50; i++)
	{
		if (alive[i])
		{
			aliens[i].move(sf::Vector2f(0.f, alienspeed));

			float check = aliens[i].getPosition().y;
			if (check > 1080)
			{
				float x = rand() % 1900;
				float y = -(rand() % 250);
				aliens[i].setPosition(x, y);
			}
		}
	}
}

void DrawAliens(sf::RenderWindow& window, sf::Sprite aliens[], bool alive[])
{
	for (int i = 0; i < 50; i++)
	{
		if (alive[i])
			window.draw(aliens[i]);
	}
}

void InitializeBoss(sf::Sprite& boss, sf::Texture& bossTexture, int level)
{


	if (level == 1)
	{
		bossTexture.loadFromFile("boss5.png");

		boss.setTexture(bossTexture);
		boss.setScale(0.2f, 0.2f);
		boss.setPosition(1960 / 2.f - 60.f, 100.f);
	}
	else
	
	{
		if (level == 2)
			bossTexture.loadFromFile("boss2.png");
		else if (level == 3)
			bossTexture.loadFromFile("boss1.png");
		else if (level == 4)
			bossTexture.loadFromFile("boss3.png");
		else if (level == 5)
			bossTexture.loadFromFile("boss4.png");
		boss.setTexture(bossTexture);
		boss.setScale(0.5f, 0.5f);
		boss.setPosition(1960 / 2.f - 60.f, 100.f);
		
	}

	
}

void MoveBoss(sf::Sprite& boss, float& bossDirection, float bossSpeed)
{
	boss.move(bossDirection * bossSpeed, 0);

	float bossX = boss.getPosition().x;
	if (bossX < 50 || bossX > 1700)
	{
		bossDirection *= -1;
	}
}

void FireBossBullets(sf::RectangleShape bossBullets[], bool bossBulletStatus[], sf::Sprite& boss, sf::Clock& bossClock)
{
	if (bossClock.getElapsedTime().asSeconds() > 0.8f)
	{
		for (int i = 0; i < 50; i++)
		{
			if (!bossBulletStatus[i])
			{
				bossBullets[i].setFillColor(sf::Color::Red);
				bossBullets[i].setSize(sf::Vector2f(10.f, 20.f));

				sf::FloatRect bossBounds = boss.getGlobalBounds();
				bossBullets[i].setPosition(
					bossBounds.left + bossBounds.width / 2 - 4.f,
					bossBounds.top + bossBounds.height
				);

				bossBulletStatus[i] = true;
				bossClock.restart();
				break;
			}
		}
	}
}

void UpdateBossBullets(sf::RectangleShape bossBullets[], bool bossBulletStatus[], float speed)
{
	for (int i = 0; i < 50; i++)
	{
		if (bossBulletStatus[i])
		{
			bossBullets[i].move(0, speed);

			if (bossBullets[i].getPosition().y > 1080)
				bossBulletStatus[i] = false;
		}
	}
}

void DrawBossBullets(sf::RenderWindow& window, sf::RectangleShape bossBullets[], bool bossBulletStatus[])
{
	for (int i = 0; i < 50; i++)
	{
		if (bossBulletStatus[i])
			window.draw(bossBullets[i]);
	}
}

void SpawnPowerUp(sf::Sprite& powerUp, sf::Texture& powerUpTexture)   // shield aik hi count ho gi agr do ship lai leti hai
{
	powerUp.setTexture(powerUpTexture);
	powerUp.setScale(0.2f, 0.2f);

	float x = rand() % 1800 + 80;
	float y = -(rand() % 100);
	powerUp.setPosition(x, y);
}

void MovePowerUp(sf::Sprite& powerUp, float speed)
{
	powerUp.move(0, speed);

	if (powerUp.getPosition().y > 1080)
	{
		float x = rand() % 1800 + 80;
		float y = -(rand() % 500);
		powerUp.setPosition(x, y);
	}
}

void parallelexinitiaization(sf::RectangleShape parallexbullet[])
{
	for (int i = 0; i < 250; i++)
	{
		float x = rand() % 1860 + 50;
		float y = -(rand() % 1080);

		parallexbullet[i].setFillColor(sf::Color::Black);
		parallexbullet[i].setSize(sf::Vector2f(2.f, 5.f));
		parallexbullet[i].setPosition(x, y);
	}
}

void parallelexMovement(sf::RectangleShape parallexbullet[], float paralllexspeed)
{
	for (int i = 0; i < 250; i++)
	{
		parallexbullet[i].move(sf::Vector2f(0.f, paralllexspeed));
		float check = parallexbullet[i].getPosition().y;

		if (check > 1080)
		{
			float x = rand() % 1900 + 20;
			float y = -(rand() % 1080);
			parallexbullet[i].setPosition(x, y);
		}
	}
}

void parallexdisplay(sf::RectangleShape parallexbullet[], sf::RenderWindow& window)
{
	for (int i = 0; i < 250; i++)
	{
		window.draw(parallexbullet[i]);
	}
}

void firebullets(sf::RectangleShape bullets[], bool status[], sf::RectangleShape& player)
{
	for (int i = 0; i < 100; i++)
	{
		if (!status[i])
		{
			bullets[i].setFillColor(sf::Color::Black);
			bullets[i].setOutlineColor(sf::Color::Yellow);
			bullets[i].setOutlineThickness(3.f);
			bullets[i].setSize(sf::Vector2f(5.f, 15.f));
			bullets[i].setPosition(
				player.getPosition().x + 30.f, player.getPosition().y
			);

			status[i] = true;
			break;
		}
	}
}

void updatebullets(sf::RectangleShape bullets[], bool status[], float speed)
{
	for (int i = 0; i < 100; i++)
	{
		if (status[i])
		{
			bullets[i].move(0, -speed);
		}
		if (bullets[i].getPosition().y + bullets[i].getSize().y < 0)
			status[i] = false;
	}
}

void drawbullets(sf::RenderWindow& window, sf::RectangleShape bullets[], bool status[])
{
	for (int i = 0; i < 100; i++)
	{
		if (status[i])
			window.draw(bullets[i]);
	}
}

void handleinput(sf::RenderWindow& window, sf::RectangleShape& player, float speed)
{
	float WindowWidth = (float)window.getSize().x;
	float playerwidth = player.getSize().x;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (player.getPosition().x > 20)
		{
			player.move(-speed, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (player.getPosition().x + playerwidth < WindowWidth)
		{
			player.move(speed, 0);
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1960, 1080), "Alien Shooter");
	sf::RectangleShape player;
	sf::Texture Playertexture;

	if (!Playertexture.loadFromFile("ship.png"))
	{
		cout << "Error loading ship texture" << endl;
	}

	sf::Texture Alientexture;
	if (!Alientexture.loadFromFile("alien.png"))
	{
		cout << "Error loading alien texture" << endl;
	}

	sf::Texture BossTexture;
	if (!BossTexture.loadFromFile("boss1.png"))
	{
		cout << "Error loading boss texture" << endl;
	}

	sf::Texture PowerUpTexture;
	if (!PowerUpTexture.loadFromFile("life.png")) 
	{
		cout << "Error loading powerup texture" << endl;
	}

	player.setSize(sf::Vector2f(100.f, 100.f));
	player.setPosition(1960 / 2.f, 1000.f);
	player.setTexture(&Playertexture);

	float playerspeed = 4.f;
	int level = 1;
	const int MAX_LEVELS = 5;
	int lives = 3;
	int score = 0;
	bool shieldActive = false;

	float parallexspeed = 0.3f + 0.3f * (level);
	sf::RectangleShape parallexbullet[250];

	sf::Font font;
	if (!font.loadFromFile("ONEDAY.otf"))
	{
		cout << "Error loading font!" << endl;
	}

	sf::Text scoretext;
	scoretext.setFont(font);
	scoretext.setFillColor(sf::Color::Black);
	scoretext.setCharacterSize(36);
	scoretext.setPosition(15.f, 10.f);

	sf::Text livestext;
	livestext.setFont(font);
	livestext.setFillColor(sf::Color::Black);
	livestext.setCharacterSize(32);
	livestext.setPosition(15.f, 80.f);

	sf::Text leveltext;
	leveltext.setFont(font);
	leveltext.setFillColor(sf::Color::Black);
	leveltext.setCharacterSize(32);
	leveltext.setPosition(15.f, 140.f);

	sf::Text Shieldtext;
	Shieldtext.setFont(font);
	Shieldtext.setFillColor(sf::Color::Blue);
	Shieldtext.setCharacterSize(32);
	Shieldtext.setPosition(15.f, 80.f);
	Shieldtext.setString(" SHIELD ACTIVE!");
	int gamestate = 1; // 1=playing, 2=gameover, 3=paused, 4=won

	float alienspeed = 0.3f + 0.2f * (level);

	const int Maxbullets = 100;
	sf::RectangleShape bullets[Maxbullets];
	bool status[Maxbullets] = { false };

	const int maxaliens = 50;
	sf::Sprite Aliens[maxaliens];
	bool alive[maxaliens] = { false };

	// Boss variables
	sf::Sprite boss;
	int bossLives = 0;
	bool bossActive = false;
	bool bossSpawned = false;
	float bossDirection = 1.0f;
	float bossSpeed = 2.0f;
	sf::Clock bossShotClock;

	const int MaxBossBullets = 50;
	sf::RectangleShape bossBullets[MaxBossBullets];
	bool bossBulletStatus[MaxBossBullets] = { false };

	// Power-up variables
	sf::Sprite powerUp;
	bool powerUpActive = false;
	sf::Clock powerUpSpawnClock;

	parallelexinitiaization(parallexbullet);
	LEVEL(Aliens, alive, level, Alientexture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				// Pause/Unpause
				if (event.key.code == sf::Keyboard::P)
				{
					if (gamestate == 1)
						gamestate = 3; // Pause
					else if (gamestate == 3)
						gamestate = 1; // Resume
				}

				// Shooting
				if (gamestate == 1 && event.key.code == sf::Keyboard::Space)
					firebullets(bullets, status, player);

				// Restart after game over
				if (gamestate == 2 && event.key.code == sf::Keyboard::Space)
				{
					level = 1;
					lives = 3;
					score = 0;

					alienspeed = 0.3f + 0.2f * level;
					parallexspeed = 0.3f + 0.3f * level;

					bossActive = false;
					bossSpawned = false;
					powerUpActive = false;
					shieldActive = false;

					LEVEL(Aliens, alive, level, Alientexture);
					player.setPosition(1960 / 2.f, 1000.f);

					gamestate = 1;
				}

				// Continue after winning
				if (gamestate == 4 && event.key.code == sf::Keyboard::Enter)
				{
					level = 1;
					lives = 3;
					score = 0;

					alienspeed = 0.3f + 0.2f * level;
					parallexspeed = 0.3f + 0.3f * level;

					bossActive = false;
					bossSpawned = false;
					powerUpActive = false;
					shieldActive = false;
					LEVEL(Aliens, alive, level, Alientexture);
					player.setPosition(1960 / 2.f, 1000.f);

					gamestate = 1;
				}
			}
		}

		if (gamestate == 1)
		{
			Alienmovement(Aliens, alive, alienspeed);
			parallelexMovement(parallexbullet, parallexspeed);
			handleinput(window, player, playerspeed);
			updatebullets(bullets, status, 10.f);

			// Check if all aliens killed and spawn boss
			if (CheckAllAliensKilled(alive, maxaliens) && !bossSpawned)
			{
				bossActive = true;
				bossSpawned = true;
				bossLives = level + 1; // Level 1 boss has 2 lives, level 2 has 3, etc.
				InitializeBoss(boss, BossTexture, level);
				bossShotClock.restart();
			}

			// Boss behavior
			if (bossActive)
			{
				MoveBoss(boss, bossDirection, bossSpeed);
				FireBossBullets(bossBullets, bossBulletStatus, boss, bossShotClock);
			}

			UpdateBossBullets(bossBullets, bossBulletStatus, 5.f);

			// Power-up spawning
			if (!powerUpActive && powerUpSpawnClock.getElapsedTime().asSeconds() > 15.f)
			{
				SpawnPowerUp(powerUp, PowerUpTexture);
				powerUpActive = true;
				powerUpSpawnClock.restart();
			}

			if (powerUpActive)
			{
				MovePowerUp(powerUp, 2.f);
			}

			HandleCollisions(Aliens, alive, 50, bullets, status, 100, player,
				boss, bossLives, bossActive, bossBullets, bossBulletStatus, 50,
				powerUp, powerUpActive, score, lives,shieldActive);

			// Check if boss defeated
			if (bossSpawned && !bossActive)
			{
				level++;

				if (level > MAX_LEVELS)
				{
					gamestate = 4; // Game won!
				}
				else
				{
					alienspeed = 0.3f + 0.2f * level;
					parallexspeed = 0.3f + 0.3f * level;

					LEVEL(Aliens, alive, level, Alientexture);
					player.setPosition(1960 / 2.f, 1000.f);

					bossSpawned = false;
				}
			}

			if (lives <= 0)
			{
				gamestate = 2;
			}

			scoretext.setString("Score: " + to_string(score));
			livestext.setString("Lives: " + to_string(lives));
			leveltext.setString("Level: " + to_string(level));
		}

		window.clear(sf::Color::White);

		if (gamestate == 1)
		{
			parallexdisplay(parallexbullet, window);
			window.draw(player);
			drawbullets(window, bullets, status);
			DrawAliens(window, Aliens, alive);

			if (bossActive)
			{
				window.draw(boss);																	// draw aur display wla sab kuch window clear k baad ho ga

				DrawBossBullets(window, bossBullets, bossBulletStatus);
			}

			if (powerUpActive)
			{
				window.draw(powerUp);
			}
			if (shieldActive)
				window.draw(Shieldtext);
			else
				window.draw(livestext);

			window.draw(scoretext);
			window.draw(leveltext);
		}
		else if (gamestate == 2)
		{
			sf::Text Gameover;
			Gameover.setFillColor(sf::Color::Black);
			Gameover.setFont(font);
			Gameover.setCharacterSize(60);
			Gameover.setString("Game Over!\nFinal Score: " + to_string(score) + "\nPress Space to Restart");
			Gameover.setPosition(600.f, 400.f);

			parallexdisplay(parallexbullet, window);
			window.draw(Gameover);
		}
		else if (gamestate == 3)
		{
			parallexdisplay(parallexbullet, window);
			window.draw(player);
			drawbullets(window, bullets, status);
			DrawAliens(window, Aliens, alive);

			if (bossActive)
			{
				window.draw(boss);
			}

			if (powerUpActive)
			{
				window.draw(powerUp);
			}

			if (shieldActive)
			{
				window.draw(Shieldtext);
				
			}
			else
			{
				window.draw(livestext);
			}
			window.draw(scoretext);
			
			window.draw(leveltext);

			sf::Text pauseText;
			pauseText.setFillColor(sf::Color::Black);
			pauseText.setFont(font);
			pauseText.setCharacterSize(60);
			pauseText.setString("PAUSED\nPress P to Continue");
			pauseText.setPosition(700.f, 450.f);

			sf::RectangleShape pauseOverlay;
			pauseOverlay.setSize(sf::Vector2f(1960, 1080));
			pauseOverlay.setFillColor(sf::Color(255, 255, 255, 180));
			window.draw(pauseOverlay);
			window.draw(pauseText);
		}
		else if (gamestate == 4)
		{
			sf::Text winText;
			winText.setFillColor(sf::Color::Black);
			winText.setFont(font);
			winText.setCharacterSize(60);
			winText.setString("YOU WON!\nAll Levels Cleared!\nFinal Score: " + to_string(score) + "\n\nPress Enter to Play Again");
			winText.setPosition(500.f, 350.f);

			parallexdisplay(parallexbullet, window);
			window.draw(winText);
		}

		window.display();
	}

	return 0;
}