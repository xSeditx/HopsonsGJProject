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
#include"Sound.h"

#define SCREEN_BUFFER_AREA  100
#define MAX_PROJECTILES     400
#define MAX_ENEMIES          150
#define MAX_STATICOBJECTS    150
#define MAX_POWERUPS         150


#define BOSSDRAGON_MAXLIFE  10000.0f
class Player; 
class Enemy; 
class StaticObject; 
class Entity; 
class Projectile; 
class EnemyProjectile; 
class Powerup;


enum  EntityType
{
    EntityEntity = 0,
    PlayerEntity,
    EnemyEntity,
    StaticEntity,
    PowerUpEntity,
    ProjectileEntity,
};


/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                    RESPONSE CLASS                                                                                                                                                                                                                                                                                           
   NOTE: I made this, started to implement it... And never used it Anywhere. Not sure I have time to make it useful but we will see                                                                                                                                                        
========================================================================================================================================================================================*/

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


//========================================================================================================================================================================================
/*                            
                                                ENTITY CLASS:
                                        _____________________________
                              MANAGES THE PLAYER, ENEMIES AND STATIC WORLD OBJECTS.                                                                                               
                              POSSIBLY ADD THE PROJECTILES INTO THIS IN THE FUTURE.                                                                                               
    8/27/2018 
*/
//========================================================================================================================================================================================


class Entity
{
public:
        Entity()
        {
            ID  = 0;
            Age = 0;
        }
            
        Vec2 Position;
        
        Sprite Picture;
        
        int ID, Age;
        
        bool Alive;

        EntityType Type;

        Collider *CollisionBox;

        Response CollisionResponse;

        SoundEffect *HitWave;
        SoundEffect *Ambient;
        SoundEffect *Death;

        bool Invincible;

        void (*SpecialUpdate)(Enemy *object); 
        void SetSpecialUpdate(void(*function)(Enemy *object)){ SpecialUpdate = function;}

    virtual void Kill()                  = 0;
    virtual void Update()                = 0;
    virtual void Render()                = 0;
    virtual void Response(Entity *other) = 0;

static void Unload();
static void Initialize();

static Player *PlayerOne;

static Enemy  *CthuluEye, 
              *Dragon, 
              *GreenEye;

static StaticObject *Explosion, *Lightning01;
static Projectile   *Bullets;

static EnemyProjectile *FireBall;

static Powerup *EnergySphere;
};

/*__________________________________________________________________________________________________________________________________________________________________________________________                                                                                                                                            
========================================================================================================================================================================================*/


class Enemy : public Entity                
{                                          
    public:
        Enemy();

        Enemy(Vec2  pos, Vec2 vel, Sprite img);

        Vec2 Speed;

        int Health;

        int DamagePoints;
        int Worth;
        int MovementTimer;
        void Kill()                     override;
        void Update()                   override;
        void Render()                   override;
        void Response(Entity *other)    override;

    static int Spawn(Vec2 pos, Vec2 vel, Sprite img);
    static void Initialize();
    static Enemy EnemyList[MAX_ENEMIES];

    static std::vector<int> EnemyValidID;
    static int NumberOfEnemies;
};
class Player : public Entity
{
    public:
        Player();

        float Angle;

        int  Health;

        int EnergyLevel;

        int Lives;

        bool Invincible;
        double InvincibilityTimer;

        int Score;

        int NumberOfKills;

        void Kill()                    override;
        void Update()                  override;
        void Render()                  override;
        void Response(Entity *other)   override;    
};     

class Powerup : public Entity
{
    public:
        Powerup(){}
        Powerup(Vec2 pos, Vec2 vel, Sprite *img);

        int EnergyBuff;
        void Kill()                     override;
        void Update()                   override;
        void Render()                   override;
        void Response(Entity *other)    override;

        void (*SpecialEffect)(void); 

    static int Spawn(Vec2 pos, Vec2 vel, Sprite *img);
    static void Initialize();

    static Powerup PowerupList[MAX_POWERUPS];
    static std::vector<int> PowerupValidID;
    static int NumberOfPowerup;

    void SetSpecialEffect(void(*f)(void)) { SpecialEffect = f;}
 
    static void EnergyPowerup()
    {
        Entity::PlayerOne->EnergyLevel = 100;
    
        SoundEffect::Beep01->Play();
    }
    static void HealthPowerup()
    {
        Entity::PlayerOne->Health += 10;
        SoundEffect::LaserTail0004->Play();
        if(Entity::PlayerOne->Health > 100)
        {
            Entity::PlayerOne->Health = 100;
        }
    }
    static void ExtraLife()
    {
        Player::PlayerOne->Lives++;
    }
    static void Nuke();

};
class Projectile : public Entity
{
public:
        Projectile(){}
        Projectile(Vec2 pos,Vec2 vel, Sprite *img);
        ~Projectile()
        {
        }
        Vec2 Speed;

        float BulletPower;
        void Kill()                     override;
        void Update()                   override;
        void Render()                   override;
        void Response(Entity *other)    override;

    static int Spawn(Vec2 pos, Vec2 vel, Projectile *object);
    static int Spawn(Vec2 pos, Vec2 vel, Sprite *img);
    static void Initialize();
    static Projectile ProjectileList[MAX_PROJECTILES];
    static std::vector<int> ProjectileValidID;
    static int NumberOfProjectiles;
};
class StaticObject : public Entity
{
    public:
        StaticObject();
        StaticObject(Vec2  pos,  Vec2 vel, Sprite img);

        Sprite Picture;

        double LifeSpan;
        double Timer;

        Vec2 Speed;

        void Kill()                    override;
        void Update()                  override;
        void Render()                  override;
        void Response(Entity *other)   override;

 static int Spawn(Vec2 pos, Vec2 vel, double lifespan, Sprite img);
 static void Initialize();
 static StaticObject StaticObjectList[MAX_STATICOBJECTS];
 static int NumberOfStaticObjectList;
 static std::vector<int> StaticObjectValidID;
};
class EnemyProjectile : public Entity
{
public:
        EnemyProjectile(){}
        EnemyProjectile(Vec2 pos,Vec2 vel, Sprite *img);
       ~EnemyProjectile(){}
        
        Vec2  Speed;
        float BulletPower;

        void Kill()                     override;
        void Update()                   override;
        void Render()                   override;
        void Response(Entity *other)    override;

 static int Spawn(Vec2 pos, Vec2 vel, EnemyProjectile *object);
 static int Spawn(Vec2 pos, Vec2 vel, Sprite *img);
 
 static void Initialize();
 static EnemyProjectile EnemyProjectileList[MAX_PROJECTILES];
 static std::vector<int> ProjectileValidID;
 static int NumberOfProjectiles; // This shit will cause conflict if its ever read as Entity and had to be sorted out I think
};



/*========================================================================================================================================================================================
                                                                                                                             
                                                GAME MECHANIC STUFF                                                                
                                                                                                                             
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/                                                                                                                                            
void BulletHit(Entity *object, Projectile *bullet);
void DragonUpdate(Enemy *object);
void DiveBomber(Enemy *object);


void Default_Response(Entity *other);
void DefaultEnemyUpdate(Enemy *object);

void EnemyProjectileResponse(Enemy *mob,  Projectile *bullet);
void DefaultProjectileResponse(Entity *mob,  Projectile *bullet);

void BossDragon(Enemy *object);