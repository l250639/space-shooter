//#include <SFML/Graphics.hpp>
//using namespace std;
//
//int main() {
//	sf::RenderWindow window(sf::VideoMode(1960, 1080), "MY GAME");
//	sf::RectangleShape player1;
//	sf::CircleShape player2;
//	player1.setSize(sf::Vector2f(150.f, 100.f));
//	player1.setFillColor(sf::Color::Blue);
//	player2.setRadius(50.f);
//	player2.setFillColor(sf::Color::Red);
//	player1.setPosition(sf::Vector2f(300.f, 200.f));
//	player2.setPosition(sf::Vector2f(500.f, 200.f));
//	sf::Texture axeTexture;
//	axeTexture.loadFromFile("C:/Users/HP/Downloads/New Piskel-1.png.png");
//	sf::Sprite axe(axeTexture);
//	axe.setScale(sf::Vector2f(20,20));
//	axe.setOrigin(sf::Vector2f(8, 8));
//	sf::Clock clock;
//	
//	while (window.isOpen())
//	{
//		sf::Time timesincelastframe = clock.restart();
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		sf::Vector2f RequestedPlayerMovement(0.f, 0.f);
//		float speed = 170.f;
//
//
//		//players movement gathered here
//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//			RequestedPlayerMovement+=sf::Vector2f(0.f,-1.f);
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//			RequestedPlayerMovement += sf::Vector2f(-1.f, 0.f);
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//			RequestedPlayerMovement += sf::Vector2f(1.f, 0.f);
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//			RequestedPlayerMovement += sf::Vector2f(0.f, 1.f);
//
//		player1.move(RequestedPlayerMovement*timesincelastframe.asSeconds()*speed);
//		window.clear();
//		window.draw(player1);
//		window.draw(player2);
//		window.display();
//		window.draw(axe);
//	}
//	return 0;
//}
