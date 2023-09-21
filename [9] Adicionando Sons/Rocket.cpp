#include "Rocket.hpp"
#include <SFML/Graphics/Sprite.hpp>

Rocket::Rocket() {}
Rocket::~Rocket() {}

void Rocket::init(string textureName, Vector2f position, float _speed) {
    r_speed = _speed;
    r_position = position;
    r_texture.loadFromFile(textureName.c_str());
    r_sprite.setTexture(r_texture);
    r_sprite.setPosition(r_position);
    r_sprite.setOrigin(r_texture.getSize().x / 2.0f, r_texture.getSize().y / 2.0f);
}

void Rocket::update(float dt) {
    r_sprite.move(r_speed * dt, 0);
}

Sprite Rocket::getSprite() {
    return r_sprite;
}