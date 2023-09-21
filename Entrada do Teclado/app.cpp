#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

using namespace sf;

Vector2f viewSize(894, 894);
VideoMode vm(viewSize.x, viewSize.y);
RenderWindow window(vm, "Sprites :D", Style::Default);

Texture skyTexture;
Sprite skySprite;

void initSprite() {
    skyTexture.loadFromFile("Assets/sky.png");
    skySprite.setTexture(skyTexture);
}

void drawSprite() {
    window.draw(skySprite);
}

void updateInput() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.key.code == Keyboard::Escape ||
            event.type == Event::Closed) {
            window.close();
        }
    }
}

int main(int argc, char **argv) {
    initSprite();
    while (window.isOpen()) {
        window.clear(Color::Black);
        drawSprite();
        updateInput();
        window.display();
    }
    return 0;
}