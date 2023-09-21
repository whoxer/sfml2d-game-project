#include "Main.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
#include <iostream>

using namespace sf;
using namespace std;

Vector2f viewSize(1024, 768);
VideoMode vm(viewSize.x, viewSize.y);
RenderWindow window(vm, "Criando Inimigos :o", Style::Default);

Texture skyTexture;
Sprite skySprite;

Texture bgTexture;
Sprite bgSprite;

Hero hero;

vector<Enemy*> enemies;
float currentTime;
float prevTime = 0.0f;

void spawnEnemy() {
    int randLoc = rand() % 4;
    Vector2f enemyPos;
    float speed;

    switch (randLoc) {
        case 0:
            enemyPos = Vector2f(viewSize.x, viewSize.y * 0.75f);
            speed = -400;
            break;
        case 1:
            enemyPos = Vector2f(viewSize.x, viewSize.y * 0.60f);
            speed = -550;
            break;
        case 2:
            enemyPos = Vector2f(viewSize.x, viewSize.y * 0.40f);
            speed = -650;
            break;
        default: 
            cout << "incorrect y value" << endl;
            return;
    }
    Enemy *enemy = new Enemy();
    enemy->init("Assets/enemy.png", enemyPos, speed);
    enemies.push_back(enemy);
}

void init() {
    skyTexture.loadFromFile("Assets/sky.png");
    skySprite.setTexture(skyTexture);
    bgTexture.loadFromFile("Assets/bg.png");
    bgSprite.setTexture(bgTexture);
    hero.init("Assets/hero.png", Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);
    srand((int)time(0));
}

void draw() {
    window.draw(skySprite);
    window.draw(bgSprite);
    window.draw(hero.getSprite());
    for (Enemy *enemy : enemies) {
        window.draw(enemy->getSprite());
    }
}

void updateInput() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Space) {
                hero.jump(750.0f);
            }
        }
        if (event.key.code == Keyboard::Escape || event.type == Event::Closed) {
            window.close();
        }
    }
}

void update(float dt) {
    hero.update(dt);
    currentTime += dt;
    if (currentTime >= prevTime + 1.125f) {
        spawnEnemy();
        prevTime = currentTime;
    }
    for (int i = 0; i < enemies.size(); i++) {
        Enemy *enemy = enemies[i];
        enemy->update(dt);
        if (enemy->getSprite().getPosition().x < 0) {
            enemies.erase(enemies.begin() + i);
            delete(enemy);
        }
    }
}

int main(int argc, char **argv) {
    Clock clock;
    init();
    while (window.isOpen()) {
        updateInput();
        Time dt = clock.restart();
        update(dt.asSeconds());
        draw();
        window.display();
    }
    return 0;
}
