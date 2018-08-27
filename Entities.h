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

class Player; class Enemy; class Static; class Entity;


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
        }

                              
        void (*EnemyResponse      )(Entity *other);
        void (*PlayerReponse      )(Entity *other);
        void (*PowerUpReponse     )(Entity *other);
        void (*StaticObjectReponse)(Entity *other);
        
        
        void SetEnemyResponse       (void (*f) (Entity *other))  {EnemyResponse       = f;}
        void SetPlayerReponse       (void (*f) (Entity *other))  {PlayerReponse       = f;}
        void SetPowerUpReponse      (void (*f) (Entity *other))  {PowerUpReponse      = f;}
        void SetStaticObjectReponse (void (*f) (Entity *other))  {StaticObjectReponse = f;}
};
class Entity
{
public:
    Entity(){}
        
        Vec2 Position;
        
        Sprite *Image;
        
        int ID;
        
        bool Alive;

        EntityType Type;

        Collider *CollisionBox;


        Response CollisionResponse;

        virtual void Spawn() = 0;
        virtual void Kill()  = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Response(Entity *other) = 0;

        static std::vector<Entity *> EnemyList;
        static std::vector<Entity *> SpriteList;

};
class Player : public Entity
{
    public:
        Player();
        int Health;

        void Spawn()                   override;
        void Kill()                    override;
        void Update()                  override;
        void Render()                  override;
        void Response(Entity *other)   override;    
                                           
};                                         
class Enemy : public Entity                
{                                          
    public:
        Enemy();
        int Health;


        void Spawn()                    override;
        void Kill()                     override;
        void Update()                   override;
        void Render()                   override;
        void Response(Entity *other)    override;

};
class StaticObject : public Entity
{
    public:
        StaticObject();

        void Spawn()                   override;
        void Kill()                    override;
        void Update()                  override;
        void Render()                  override;
        void Response(Entity *other)   override;

};
class Powerups : public Entity
{
    public:
        Powerups();

        void Spawn()                  override;
        void Kill()                   override;
        void Update()                 override;
        void Render()                 override;
        void Response(Entity *other)  override;
};
