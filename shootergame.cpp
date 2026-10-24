//#include<iostream>
//#include<SFML/Graphics.hpp>
//
//using namespace std;
//
//bool CircleRectCollision(const sf::CircleShape& circle, const sf::RectangleShape& rect)
//{
//
//	float cx = circle.getPosition().x + circle.getRadius();  // center X
//	float cy = circle.getPosition().y + circle.getRadius();  // center Y
//	float r = circle.getRadius();
//
//	float rx = rect.getPosition().x;
//	float ry = rect.getPosition().y;
//	float rw = rect.getSize().x;
//	float rh = rect.getSize().y;
//
//
//	float closestX = std::max(rx, std::min(cx, rx + rw));
//	float closestY = std::max(ry, std::min(cy, ry + rh));
//
//
//	float dx = cx - closestX;
//	float dy = cy - closestY;
//
//
//	return (dx * dx + dy * dy) <= (r * r);
//}
//
//void HandleCollisions(
//	sf::CircleShape aliens[], bool alive[], int totalAliens,
//	sf::RectangleShape bullets[], bool status[], int totalBullets,
//	sf::RectangleShape& player,
//	int& score, int& lives
//)
//{
//
//	for (int i = 0; i < totalBullets; i++)
//	{
//		if (!status[i]) continue;
//
//		for (int j = 0; j < totalAliens; j++)
//		{
//			if (!alive[j]) continue;
//
//			if (CircleRectCollision(aliens[j], bullets[i]))
//			{
//				alive[j] = false;
//				status[i] = false;
//				score += 10;
//			}
//		}
//	}
//
//
//	for (int j = 0; j < totalAliens; j++)
//	{
//		if (!alive[j]) continue;
//
//		if (CircleRectCollision(aliens[j], player))
//		{
//			alive[j] = false;
//			lives -= 1;
//		}
//	}
//}
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
//void LEVEL(sf::CircleShape aliens[], bool alive[], int level, sf::Texture& alientexture)   // alien idhar initilaize hai
//{
//	int total = 10 + (level - 1) * 10;
//	if (total > 50)
//		total = 50;
//	for (int i = 0; i < 50; i++)      // to initialize each single alive alien
//	{
//		aliens[i].setRadius(20.f);
//		aliens[i].setTexture(&alientexture);
//		aliens[i].setOutlineColor(sf::Color::Blue);
//		aliens[i].setOutlineThickness(2.f);
//		float x = rand() % 1860 + 50;		// the value of x axis can be  for rand [0,1860] and adding fifity gives [50,1910] size of screen is[0,1960]
//		float y = -(rand() % 250);          // agr random negative value ho gi to har alien alag time p nechay ai ga  
//		aliens[i].setPosition(x, y);
//		alive[i] = true;						// yay alien abhi zinda hai
//	}
//
//	// agr koi chota level ho jisy mai aliens less hai max 50 sai to baki jo extra aliens hai un ko dead declare kr do ga start mai
//	for (int i = total; i < 50; i++)
//	{
//		alive[i] = false;
//	}
//}
//
//void Alienmovement(sf::CircleShape aliens[], bool alive[], float& alienspeed)
//{
//	float check;
//	for (int i = 0; i < 50; i++)				// chunke mai xtra aliens ko pehlay fals ekr chuka ho to yay par total p fark nai paray ga 
//	{
//		if (alive[i])
//		{
//			aliens[i].move(sf::Vector2f(0.f, alienspeed));
//			
//
//
//			check = aliens[i].getPosition().y;
//			if (check > 1080)
//			{
//				float x, y;
//				y = -(rand() % 50);
//				x = rand() % 1900;
//				aliens[i].setPosition(x, y);
//				// yani agr screen cross kr li hai to us ko dobara sai opar sai random position p generate krwao
//			}
//		}
//
//	}
//}
//void DrawAliens(sf::RenderWindow& window, sf::CircleShape aliens[], bool alive[])
//{
//	for (int i = 0; i < 50; i++)
//	{
//		if (alive[i])
//			window.draw(aliens[i]);
//	}
//}
//
//void parallelexinitiaization(sf::RectangleShape parallexbullet[])
//{
//
//	for (int i = 0; i < 250; i++)
//	{
//		float x, y;
//		x = rand() % 1860 + 50;
//		y = -(rand() % 1080);
//
//		parallexbullet[i].setFillColor(sf::Color::Black);
//		parallexbullet[i].setSize(sf::Vector2f(2.f, 5.f));
//
//		parallexbullet[i].setPosition(x, y);
//
//
//
//	}
//}
//void parallelexMovement(sf::RectangleShape parallexbullet[], float paralllexspeed)
//{
//	float x, y, check;
//	for (int i = 0; i < 250; i++)
//
//	{
//		parallexbullet[i].move(sf::Vector2f(0.f, paralllexspeed));
//		check = parallexbullet[i].getPosition().y;
//		if (check > 1080)
//		{
//			float x, y;
//			y = -(rand() % 1080);
//			x = rand() % 1900 + 20;
//			parallexbullet[i].setPosition(x, y);
//			// yani agr screen cross kr li hai to us ko dobara sai opar sai random position p generate krwao
//		}
//	}
//}
//void parallexdisplay(sf::RectangleShape parallexbullet[], sf::RenderWindow& window)
//{
//	for (int i = 0; i < 250; i++)
//	{
//		window.draw(parallexbullet[i]);
//	}
//}
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
//
//				player.getPosition().x + 30.f, player.getPosition().y
//			);
//
//			status[i] = true;
//			break;
//		}
//
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
//
//	}
//}
//void drawbullets(sf::RenderWindow& window, sf::RectangleShape bullets[], bool status[])
//
//{
//	for (int i = 0; i < 100; i++)
//	{
//
//		if (status[i])
//			window.draw(bullets[i]);
//	}
//}
//
//void handleinput(sf::RenderWindow& window, sf::RectangleShape& player, float speed)
//{
//
//	float WindowWidth = (float)window.getSize().x;  // calculates width of window
//	float playerwidth = player.getSize().x;    // player width
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  // player.getPosition().x gives the left point coordinate
//	{
//		if (player.getPosition().x > 20)               // calculate the  right point of player if<0 then out o bound hence ignore  
//		{
//			player.move(-speed, 0);						// (x,y) x = x-axis and y= y-axis, since already defined spped no need for putting value manually
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
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(1960, 1080), "My Game");
//	sf::RectangleShape player;
//	sf::Texture Playertexture;
//
//	if (!Playertexture.loadFromFile("ship.png"))
//	{
//		cout << "Error" << endl;
//	}
//
//	sf::Texture Alientexture;
//
//	if (!Alientexture.loadFromFile("alien.png"))
//	{
//		cout << "Error" << endl;
//	}
//	player.setSize(sf::Vector2f(80.f, 80.f));				// (width,height)
//	player.setPosition(1960 / 2.f, 1000.f);
//	player.setTexture(&Playertexture);
//
//	float playerspeed = 5.f;
//	float level = 1;
//	int lives = 3;
//	int score = 0;
//
//	
//
//	float parallexspeed = 0.3f + 0.3f * (level);
//	sf::RectangleShape parallexbullet[250];
//	sf::Font font;
//
//	if (!font.loadFromFile("ONEDAY.otf"))
//	{
//		cout << "Error loading font!" << endl;
//	}
//
//	sf::Text scoretext;
//	scoretext.Bold;
//	scoretext.setFont(font);
//	scoretext.setFillColor(sf::Color::Black);
//	scoretext.setCharacterSize(36);
//	scoretext.setPosition(15.f, 10.f);
//
//
//	sf::Text livestext;
//	livestext.setFont(font);
//	livestext.setFillColor(sf::Color::Black);
//	livestext.setCharacterSize(32);
//	livestext.setPosition(15.f, 80.f);
//	int gamestate = 1; // 1== game chal ri hai  2= game khtam ho gi hai ya lives 0 ho gi hai
//
//
//
//	float alienspeed = 0.3f + 0.2f * (level);			//pehlay level int that jo k alien speed ko 0 kr deta tha
//
//
//	const int Maxbullets = 100;
//	sf::RectangleShape bullets[Maxbullets];
//	bool status[Maxbullets] = { false };
//
//
//	const int maxaliens = 50;
//	sf::CircleShape Aliens[maxaliens];
//	bool alive[maxaliens] = { false };
//
//	parallelexinitiaization(parallexbullet);
//	LEVEL(Aliens, alive, level, Alientexture);  // live mai hi aliens ko initialzze kr dia hai
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//
//			if (gamestate == 1 && event.type == sf::Event::KeyPressed)
//			{
//				if (event.key.code == sf::Keyboard::Space)
//					firebullets(bullets, status, player);
//			}
//
//			if (gamestate == 2 && event.type == sf::Event::KeyPressed)
//			{																// agr game end ho jai yani ship mar jai to dobra sai values ko initialize krwao
//				if (event.key.code == sf::Keyboard::Space)
//				{
//					level = 1;
//					lives = 3;
//					score = 0;
//
//					alienspeed = 0.3f + 0.2f * level;
//					parallexspeed = 0.3f + 0.3f * level;
//
//					LEVEL(Aliens, alive, level, Alientexture);
//					player.setPosition(1960 / 2.f, 1000.f);
//
//					gamestate = 1;
//				}
//			}
//		}
//
//
//		if (gamestate == 1)				// agr state 2 ho gi to game chli gai hi nai aur bas error message display ho ga phir jab banda game restart krai ga to 
//			// chlai gi game
//		{
//			Alienmovement(Aliens, alive, alienspeed);
//			parallelexMovement(parallexbullet, parallexspeed);
//			handleinput(window, player, playerspeed);
//			updatebullets(bullets, status, 10.f);
//			HandleCollisions(Aliens, alive, 50, bullets, status, 100, player, score, lives);
//
//
//			if (CheckAllAliensKilled(alive, maxaliens))
//			{
//
//				level += 1.f;
//
//
//				alienspeed = 0.3f + 0.2f * level;
//				parallexspeed = 0.3f + 0.3f * level;
//
//
//				LEVEL(Aliens, alive, level, Alientexture);
//
//
//				player.setPosition(1960 / 2.f, 1000.f);
//			}
//
//			if (lives <= 0)
//			{
//				gamestate = 2;
//			}
//			scoretext.setString("Score: " + to_string(score));
//			livestext.setString("Lives: " + to_string(lives));
//
//
//
//		}
//
//		window.clear(sf::Color::White);
//
//
//		if (gamestate == 1)													// draw aur display wla sab kuch window clear k baad ho ga
//		{
//			window.draw(player);
//			drawbullets(window, bullets, status);
//			DrawAliens(window, Aliens, alive);
//			parallexdisplay(parallexbullet, window);
//			window.draw(scoretext);
//			window.draw(livestext);
//		}
//
//		else if (gamestate == 2)													// draw aur display wla sab kuch window clear k baad ho ga
//		{
//			sf::Text Gameover;
//			Gameover.Bold;
//			Gameover.setFillColor(sf::Color::Black);
//			Gameover.setFont(font);
//			Gameover.setCharacterSize(60);
//			Gameover.setString("Game over \nPress Space to Restart");
//			Gameover.setPosition(600.f, 400.f);
//
//			window.draw(Gameover);
//
//			window.draw(player);
//
//			parallexdisplay(parallexbullet, window);
//			window.draw(scoretext);
//			window.draw(livestext);
//		}
//
//
//
//		window.display();
//	}
//
//}