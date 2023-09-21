#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>

using namespace sf;

Vector2f viewSize(894, 894);
VideoMode vm(viewSize.x, viewSize.y);
RenderWindow window(vm, "Sprites :D", Style::Default);

Texture skyTexture;
Sprite skySprite;

Texture naveTexture;
Sprite naveSprite;
Vector2f playerPosition(0, 0);

bool playerMovingL = false,
    playerMovingR = false,
    playerMovingT = false,
    playerMovingB = false;

void initSprite() {
    skyTexture.loadFromFile("Assets/sky.png");
    skySprite.setTexture(skyTexture);
    naveTexture.loadFromFile("Assets/nave.png");
    naveSprite.setTexture(naveTexture);
    naveSprite.setPosition(viewSize.x - viewSize.x / 2, viewSize.y - viewSize.y / 2);
}

void draw() {
    window.draw(skySprite);
    window.draw(naveSprite);
}

void updateInput() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A) {
                playerMovingL = true;
            }
            if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D) {
                playerMovingR = true;
            }
            if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W) {
                playerMovingT = true;
            }
            if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S) {
                playerMovingB = true;
            }
        }
        if (event.type == Event::KeyReleased) {
            if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A) {
                playerMovingL = false;
            }
            if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D) {
                playerMovingR = false;
            }
            if (event.key.code == Keyboard::Up  || event.key.code == Keyboard::W) {
                playerMovingT = false;
            }
            if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S) {
                playerMovingB = false;
            }
        }
        if (event.key.code == Keyboard::Escape ||
            event.type == Event::Closed) {
            window.close();
        }
    }
}

void updatePlayer(float dt) {
    if (playerMovingL) {
        naveSprite.move(400.0f * -dt, 0);
    }
    if (playerMovingR) {
        naveSprite.move(400.0f * dt, 0);
    }
    if (playerMovingT) {
        naveSprite.move(0, 400.0f * -dt);
    }
    if (playerMovingB) {
        naveSprite.move(0, 400.0f * dt);
    }
}   

int main(int argc, char **argv) {
    Clock clock;
    initSprite();
    while (window.isOpen()) {
        window.clear(Color::Black);
        updateInput();
        Time dt = clock.restart();
        updatePlayer(dt.asSeconds());
        draw();
        window.display();
    }
    return 0;
}