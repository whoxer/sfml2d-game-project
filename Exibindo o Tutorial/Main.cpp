#include "Main.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
#include "Rocket.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Vector2f viewSize(1024, 768);
VideoMode vm(viewSize.x, viewSize.y);
RenderWindow window(vm, "Ganhando Pontos", Style::Default);

Texture skyTexture;
Sprite skySprite;

Texture bgTexture;
Sprite bgSprite;

Hero hero;

vector<Enemy*> enemies;
vector<Rocket*> rockets;

float currentTime;
float prevTime = 0.0f;

int score = 0;
bool gameover = true;

Font headingFont;
Text headingText;

Font scoreFont;
Text scoreText;

Font tutorialFont;
Text tutorialText;

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
    enemy->init("Assets/Sprites/enemy.png", enemyPos, speed);
    enemies.push_back(enemy);
}

void shoot() {
    Rocket *rocket = new Rocket;
    rocket->init("Assets/Sprites/rocket.png", hero.getSprite().getPosition(), 400.0f);
    rockets.push_back(rocket);
}

void init() {
    skyTexture.loadFromFile("Assets/Sprites/sky.png");
    skySprite.setTexture(skyTexture);

    bgTexture.loadFromFile("Assets/Sprites/bg.png");
    bgSprite.setTexture(bgTexture);

    headingFont.loadFromFile("Assets/fonts/intelone-mono-font-family-regular.ttf");

    headingText.setFont(headingFont);
    headingText.setString("Tiny Bazooka");
    headingText.setCharacterSize(84);
    headingText.setFillColor(Color::Red);

    FloatRect headingbounds = headingText.getLocalBounds();

    headingText.setOrigin(headingbounds.width  / 2, headingbounds.height / 2);
    headingText.setPosition(Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));

    scoreFont.loadFromFile("Assets/fonts/intelone-mono-font-family-regular.ttf");

    scoreText.setFont(scoreFont);
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(45);
    scoreText.setFillColor(Color::Red);

    FloatRect scoreboudings = scoreText.getLocalBounds();

    scoreText.setOrigin(scoreboudings.width / 2, scoreboudings.height / 2);
    scoreText.setPosition(Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));
    
    tutorialFont.loadFromFile("Assets/fonts/intelone-mono-font-family-regular.ttf");
    

    tutorialText.setFont(tutorialFont);
    tutorialText.setString("(press space to attack and up arrow to jump)");
    tutorialText.setCharacterSize(25);
    tutorialText.setFillColor(Color::Red);

    FloatRect tutorialboundings = tutorialText.getLocalBounds();
    tutorialText.setOrigin(tutorialboundings.width / 2, tutorialboundings.height / 2);
    tutorialText.setPosition(Vector2f(viewSize.x * 0.5f, viewSize.y * 0.20f));

    hero.init("Assets/Sprites/hero.png", Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);
    srand((int)time(0));
}
void draw() {
    window.draw(skySprite);
    window.draw(bgSprite);
    window.draw(hero.getSprite());

    for (Enemy *enemy : enemies) {
        window.draw(enemy->getSprite());
    }
    for (Rocket *rocket : rockets) {
        window.draw(rocket->getSprite());
    }

    if (gameover) {
        window.draw(headingText);
        window.draw(tutorialText);
    } else {
        window.draw(scoreText);
    }
}

void updateInput() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Up) {
                hero.jump(750.0f);  
            }
            if (event.key.code == Keyboard::Space) {
               if (gameover)  {
                   reset();
                   gameover = false;
               } else {
                   shoot();
            }
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
            gameover = true;
        }
    }
    for (int i = 0; i < rockets.size(); i++) {
        Rocket *rocket = rockets[i];
        rocket->update(dt);
        if (rocket->getSprite().getPosition().x > viewSize.x) {
            rockets.erase(rockets.begin() + i);
            delete(rocket);
        }
    }
    for (int i = 0; i < rockets.size(); i++) {
        for (int j = 0; j < enemies.size(); j++) {
            Rocket *rocket = rockets[i];
            Enemy *enemy = enemies[j];
            if (checkCollision(rocket->getSprite(), enemy->getSprite())) {
                score++;
                string finalScore = "Score: " + to_string(score);
                scoreText.setString(finalScore);
                FloatRect scorebounds = scoreText.getLocalBounds();
                scoreText.setOrigin(scorebounds.width / 2, scorebounds.height / 2);
                scoreText.setPosition(Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));
                rockets.erase(rockets.begin() + i);
                enemies.erase(enemies.begin() + j);
                delete(rocket);
                delete(enemy);
            }
        }
    }
}

bool checkCollision(Sprite sprite1, Sprite sprite2) {
    FloatRect shape1 = sprite1.getGlobalBounds();
    FloatRect shape2 = sprite2.getGlobalBounds();
    if (shape1.intersects(shape2)) {
        return true;
    } else  {
        return false; 
    }
}

void reset() {
    score = 0;
    scoreText.setString("Score: 0");
    currentTime = 0.0f;
    prevTime = 0.0;
    for (Enemy *enemy : enemies) {
        delete(enemy);
    }
    for (Rocket *rocket : rockets) {
        delete(rocket);
    }
    enemies.clear();
    rockets.clear();
}

int main(int argc, char **argv) {
    Clock clock;
    init();
    while (window.isOpen()) {
        updateInput();
        Time dt = clock.restart();
        if (!gameover)
            update(dt.asSeconds());
        draw();
        window.display();
    }
    return 0;
}
