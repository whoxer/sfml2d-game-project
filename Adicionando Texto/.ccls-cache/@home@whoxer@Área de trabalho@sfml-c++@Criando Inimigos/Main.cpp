#include "Main.hpp"
#include "Hero.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace sf;

Vector2f viewSize(1024, 768);
VideoMode vm(viewSize.x, viewSize.y);
RenderWindow window(vm, "Criando Inimigos :o", Style::Default);

Texture skyTexture;
Sprite skySprite;

Texture bgTexture;
Sprite bgSprite;

Hero hero;

void init() {
    skyTexture.loadFromFile("Assets/sky.png");
    skySprite.setTexture(skyTexture);
    bgTexture.loadFromFile("Assets/bg.png");
    bgSprite.setTexture(bgTexture);
    hero.init("Assets/hero.png", Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);
}

void draw() {
    window.draw(skySprite);
    window.draw(bgSprite);
    window.draw(hero.getSprite());
}

void updateInput() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Up) {
                hero.jump(750.0f);
            }
        }
        if (event.key.code == Keyboard::Escape ||
            event.type == Event::Closed) {
            window.close();
        }
    }
}

void update(float dt) {
    hero.update(dt);
}   

int main(int argc, char **argv) {
    Clock clock;
    init();
    while (window.isOpen()) {
        window.clear(Color::Black);
        updateInput();
        Time dt = clock.restart();
        update(dt.asSeconds());
        draw();
        window.display();
    }
    return 0;
}
