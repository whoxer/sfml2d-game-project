#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
using namespace std;

class Rocket {
    public:
        Rocket();
        ~Rocket();
        void init(string textureName, Vector2f position, float _speed);
        void update(float dt);
        Sprite getSprite();
    private:
        Texture r_texture;
        Sprite r_sprite;
        Vector2f r_position;
        float r_speed;
};