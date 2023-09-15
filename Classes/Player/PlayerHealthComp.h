#pragma once
#include "../lib/raylib.h"

struct PlayerHealthCompData {
    int hp;
    const int max_hp = 100;
};

class PlayerHealthComp {
    protected:
        PlayerHealthCompData data;

    public:

        class HealthBar {
            public:

                float CalculatePercentage(int hp, int max_hp) {
                    int percentage = (float)hp / (float)max_hp;
                    return percentage;
                }

                void Draw(Vector2 position, int hp, int max_hp) {
                    int percentage = CalculatePercentage(hp, max_hp);
                    
                    DrawRectangle(position.x, position.y, 100, 20, BLACK);
                    DrawRectangleLines(position.x, position.y, 100, 20, RED);
                    DrawRectangle(position.x, position.y, 100 * percentage, 20, GREEN);
                };
        };

        PlayerHealthComp() {
            
        }

        void DamagePlayer(int damage) {
            data.hp -= damage;
        }

        void HealPlayer(int heal) {
            data.hp += heal;
        }

        int GetMaxHealth() {
            return data.max_hp;
        }

        int GetHealth() {
            return data.hp;
        }
};