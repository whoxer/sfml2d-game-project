#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
using namespace std;

class Enemy {
    public:
        Enemy();
        ~Enemy();
        void init(string textureName, Vector2f position, float _speed);
        void update(float dt);
        Sprite getSprite();
    private:
        Texture e_texture;
        Sprite  e_sprite;
        Vector2f e_position;
        float e_speed;
};

void spawnEnemy();
bool checkCollision(Sprite sprite1, Sprite sprite2);
