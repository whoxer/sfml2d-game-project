#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace std;
using namespace sf;

class Hero {
    public:
        Hero();
        ~Hero();
        void init(string textureName, Vector2f position, float mass);
        void update(float dt);
        void jump(float velocity);
        Sprite getSprite();
    private:
        Texture h_texture;
        Sprite h_sprite;
        Vector2f h_position;
        int jumpCount = 0;
        float h_mass;
        float h_velocity;
        const float h_gravity = 9.80f;
        bool h_grounded;
};