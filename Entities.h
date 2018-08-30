#pragma once
/*
____________________________________________________________________________________________________________________________________________________________
                                                                                                                   
                                       ENTITY CLASS:
                               ____________________________
                     MANAGES THE PLAYER, ENEMIES AND STATIC WORLD OBJECTS.                                                                                               
                     POSSIBLY ADD THE PROJECTILES INTO THIS IN THE FUTURE.                                                                                               

    8/27/2018 
_______________________________________________________________________________________________________________________________________________________
*/


#include"window.h"
#include"sprite.h"
#include"Collision.h"

#define SCREEN_BUFFER_AREA  100
#define MAX_PROJECTILES     100

class Player; class Enemy; class Static; class Entity; class Projectile;

extern int Score;

enum  EntityType{
    EntityEntity = 0,
    PlayerEntity,
    EnemyEntity,
    StaticEntity,
    PowerUpEntity
};

class Response
{
public:
        Response()
        {
                EnemyResponse       = NULL; // Perhaps setup default responses for these 
                PlayerReponse       = NULL; // It will probably provide simplification in the future
                PowerUpReponse      = NULL;
                StaticObjectReponse = NULL;
                ProjectileResponse  = NULL;
        }
                              
        void (*EnemyResponse      )( Entity *other);
        void (*PlayerReponse      )( Entity *other);
        void (*PowerUpReponse     )( Entity *other);
        void (*StaticObjectReponse)( Entity *other);
        void (*ProjectileResponse) ( Enemy*, Projectile *other);
        
        void SetEnemyResponse       (void (*f) ( Entity *other))     {EnemyResponse       = f;}
        void SetPlayerReponse       (void (*f) ( Entity *other))     {PlayerReponse       = f;}
        void SetPowerUpReponse      (void (*f) ( Entity *other))     {PowerUpReponse      = f;}
        void SetStaticObjectReponse (void (*f) ( Entity *other))     {StaticObjectReponse = f;}
        void SetProjectileReponse   (void (*f) ( Enemy*, Projectile *other)) {ProjectileResponse  = f;}
};
class Entity
{
public:
        Entity()
        {
            ID = 0;
            Age = 0;
        }
            
        Vec2 Position;
        
        Sprite Image;
        
        int ID, Age;
        
        bool Alive;

        EntityType Type;

        Collider *CollisionBox;

        Response CollisionResponse;


        virtual void Kill()                  = 0;
        virtual void Update()                = 0;
        virtual void Render()                = 0;
        virtual void Response(Entity *other) = 0;
};
class Player : public Entity
{
    public:
        Player();

        float Angle;

        int  Health;

        int EnergyLevel;

        int Lives;


        void Kill()                    override;
        void Update()                  override;
        void Render()                  override;
        void Response(Entity *other)   override;    
                                           
};         
class StaticObject : public Entity
{
    public:
        StaticObject(Vec2  pos,  Sprite *img);


        void Kill()                    override;
        void Update()                  override;
        void Render()                  override;
        void Response(Entity *other)   override;

};
class Powerups : public Entity
{
    public:
        Powerups();

        void Kill()                   override;
        void Update()                 override;
        void Render()                 override;
        void Response(Entity *other)  override;
};
class Enemy : public Entity                
{                                          
    public:
        Enemy();

        Enemy(Vec2  pos, Vec2 vel, Sprite *img);

        Vec2 Speed;

        int Health;

        void Kill()                     override;
        void Update()                   override;
        void Render()                   override;
        void Response(Entity *other)    override;

        static int Spawn(Vec2 pos, Vec2 vel, Sprite *img);
        static void InitializeEnemies();


        static Enemy EnemyList[MAX_PROJECTILES];
        static std::vector<int> EnemyValidID;
        static int NumberOfEnemies;
};
class Projectile : public Entity
{
public:
        Projectile(){}
        Projectile(Vec2 pos,Vec2 vel, Sprite *img);
        
        Vec2 Speed;

        void Kill()                     override;
        void Update()                   override;
        void Render()                   override;
        void Response(Entity *other)    override;


        static int Spawn(Vec2 pos, Vec2 vel, Sprite *img);
        static void InitializeProjectiles();

        static Projectile ProjectileList[MAX_PROJECTILES];
        static std::vector<int> ProjectileValidID;
        static int NumberOfProjectiles;
};