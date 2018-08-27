#pragma once
#include"window.h"
#include"sprite.h"


#define MAX_PROJECTILES 100

class Projectile
{
public:
        Projectile(Vec2 pos,Vec2 vel, Sprite *img);
        


        Vec2 Position;
        Vec2 Velocity;
        
        unsigned int Age; 
        int ID;
        Sprite *Image;
        
        bool Alive;
        
        void Update();
        void Render();
        void Kill();
        void CheckCollisions();

static int Create(Vec2 pos, Vec2 vel, Sprite *img);

        static void UpdateAll();
        static void InitializeProjectiles();
        static std::vector<Projectile *> ProjectileList;
        static std::vector<int> ValidID;
        static int NumberOfProjectiles;


};