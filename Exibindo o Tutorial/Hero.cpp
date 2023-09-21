#include "Hero.hpp"

Hero::Hero() {}

Hero::~Hero() {}

void Hero::init(string textureName, Vector2f position, float mass) {
    h_position = position;
    h_mass = mass;

    h_grounded = false;

    h_texture.loadFromFile(textureName.c_str());
    
    h_sprite.setTexture(h_texture);
    h_sprite.setPosition(h_position);   
    
    h_sprite.setOrigin(h_texture.getSize().x / 2.0f, h_texture.getSize().y / 2.0f);
}

void Hero::update(float dt) {
    h_velocity -= h_mass * h_gravity * dt;
    h_position.y -= h_velocity * dt;
    h_sprite.setPosition(h_position);
    if (h_position.y >= 768 * 0.75f) {
        h_position.y = 768 * 0.75f;
        h_velocity = 0;
        h_grounded = true;
        jumpCount = 0;
    }
}

void Hero::jump(float velocity) {
    if (jumpCount < 2) {
        jumpCount++;
        h_velocity = velocity;
        h_grounded = false;
    }
}

Sprite Hero::getSprite() {
    return h_sprite;
}

