#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

using namespace sf;


Vector2f viewSize(640, 480);
VideoMode vm(viewSize.x, viewSize.y);
RenderWindow window(vm, "quadrados [ ] [ ]", Style::Default);

int main(int argc, char **argv) {
	RectangleShape square0(Vector2f(100.0f, 100.0f));
	RectangleShape square1(Vector2f(100.0f, 100.0f));
	RectangleShape square2(Vector2f(100.0f, 100.0f));

	square0.setFillColor(Color::White);
	square0.setPosition(viewSize.x / 2, viewSize.y / 2);
	square0.setOrigin(Vector2f(square0.getSize().x / 2, square0.getSize().y));

	square1.setFillColor(Color::Magenta);
	square1.setPosition(viewSize.x / 2 + 30, viewSize.y / 2 + 30);
	square1.setOrigin(Vector2f(square1.getSize().x / 2, square1.getSize().y));

	square2.setFillColor(Color::Cyan);
	square2.setPosition(viewSize.x / 2 - 30, viewSize.y / 2 + 60);
	square2.setOrigin(Vector2f(square2.getSize().x / 2, square2.getSize().y));

	while (window.isOpen()) {
		window.clear(Color::Black);
		window.draw(square0);
		window.draw(square1);
		window.draw(square2);
		window.display();
	}
	return 0;
}
