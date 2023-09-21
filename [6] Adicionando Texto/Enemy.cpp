#include "Enemy.hpp"

Enemy::Enemy() {}
Enemy::~Enemy() {}

void Enemy::init(string textureName, Vector2f position, float _speed) {
    e_speed = _speed;
    e_position = position;
    e_texture.loadFromFile(textureName.c_str());
    e_sprite.setTexture(e_texture);
    e_sprite.setPosition(e_position);
    e_sprite.setOrigin(e_texture.getSize().x / 2.0f, e_texture.getSize().y / 2.0f);
}

void Enemy::update(float dt) {
    e_sprite.move(e_speed * dt, 0);
}

Sprite Enemy::getSprite() {
    return e_sprite;
}