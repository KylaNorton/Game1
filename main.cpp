#include <SFML/Graphics.hpp>

const sf::Keyboard::Key controls[4] = {
    sf::Keyboard::A,   // Player1 UP
    sf::Keyboard::Z,   // Player1 Down
    sf::Keyboard::Up,  // Player2 UP
    sf::Keyboard::Down // Player2 Down
};

//Parameters
const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f; //60 fps

//Objects of the game
sf::CircleShape ball;
sf::RectangleShape paddles[2];

void init() {
    // Set size and origin of paddles
    for (sf::RectangleShape &p : paddles) {
        p.setSize(paddleSize);
        p.setOrigin(paddleSize / 2.f);
    }
    // Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius,ballRadius); //Should be half the ball width and height
    // reset paddle position
    paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
    paddles[1].setPosition(paddleSize.x / 2.f, gameHeight / 2.f);
    // reset Ball Position
    ball.setPosition(gameWidth/2,gameHeight/2);
}

void update(float dt){
    // handle paddle movement
    float direction = 0.0f;
    if (sf::Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
    paddles[0].move(sf::Vector2f(0.f, direction * paddleSpeed * dt));
}

void render(sf::RenderWindow &window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

void clean(){
	//free up the memory if necessary.
}

int main () {
	//create the window
	sf::RenderWindow window(sf::VideoMode({gameWidth, gameHeight}), "PONG");
    //initialise and load
	init();
	while(!window.isOpen()){
		//Calculate dt
		static sf::Clock clock;
		const float dt = clock.restart().asSeconds();
		window.clear();
		update(dt);
		render(window);
		//wait for the time_step to finish before displaying the next frame.
		sf::sleep(time_step);
		//Wait for Vsync
		window.display();
	}
	//Unload and shutdown
	clean();
}