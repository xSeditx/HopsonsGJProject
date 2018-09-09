#include"Entities.h"
#include"Fonts.h"
#include"World.h"
 
#define FORWARD       0
#define BACKWARDS     3
#define LEFT          1
#define RIGHT         2
/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                    STATIC DEFINITIONS                                                                                                                                                                                                                                                                                           
                                Simplest way to handle this stuff in the timeframe required.                                                                                                                                                 
========================================================================================================================================================================================*/
                
Enemy           *Entity::CthuluEye, 
                *Entity::Dragon,
                *Entity::GreenEye;
Player          *Entity::PlayerOne;
Powerup         *Entity::EnergySphere;
Projectile      *Entity::Bullets;
StaticObject    *Entity::Explosion;
EnemyProjectile *Entity::FireBall;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enemy Enemy::EnemyList[MAX_ENEMIES];
int Enemy::NumberOfEnemies = 0;

std::vector<int> 
    Enemy::EnemyValidID;
//---------------------------------------------------------------------
Projectile Projectile::ProjectileList[MAX_PROJECTILES];
int Projectile::NumberOfProjectiles = 0;

std::vector<int> 
    Projectile::ProjectileValidID;
//---------------------------------------------------------------------

EnemyProjectile EnemyProjectile::EnemyProjectileList[MAX_PROJECTILES];
int EnemyProjectile::NumberOfProjectiles = 0;

std::vector<int> 
    EnemyProjectile::ProjectileValidID;
//---------------------------------------------------------------------

StaticObject StaticObject::StaticObjectList[MAX_STATICOBJECTS];
int StaticObject::NumberOfStaticObjectList = 0;

std::vector<int> 
    StaticObject::StaticObjectValidID;
//---------------------------------------------------------------------

Powerup Powerup::PowerupList[MAX_POWERUPS];
int Powerup::NumberOfPowerup = 0;

std::vector<int> 
    Powerup::PowerupValidID;
//---------------------------------------------------------------------

/*========================================================================================================================================================================================
__________________________________________________________________________________________________________________________________________________________________________________________                                                                                                                                            
========================================================================================================================================================================================*/


/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                    Game Mechanics                                                                                                                                                                                                                                                                                          
                                                                                                                                                                         
========================================================================================================================================================================================
NOTES: Various different mechanics for the Behaviors of different Enemies and Entitys this allows for overiding of the Update() method
   Allowing me to specify direct mechanics for every different sprite if I wish.
========================================================================================================================================================================================*/
void Powerup::Nuke()
{
    for(auto &object : Enemy::EnemyList)
    {
        if(object.Alive)
        {
            Entity::PlayerOne->NumberOfKills++;
            Entity::PlayerOne->Score+=object.Worth;
            
            StaticObject::Spawn(object.Position, Vec2(0), 1000, *Sprite::Explosion);
            SoundEffect::Boom5->Play();
            object.Kill();
        }
    }
}
void SpawnDrop(Vec2 pos)
{
// Go from Lowest to Highest to get accurate spawn rate

    if(RANDOM(100) > 99) // Spawn a random drop of 1% of NUKE
    {
        int Index = Powerup::Spawn(pos, Vec2(0), Sprite::FireOrb);
        Powerup::PowerupList[Index].SetSpecialEffect(Powerup::Nuke);
        return;
    }

    if(RANDOM(100) > 95) // Spawn a random drop of 5% Health Sphere
    {
        int Index = Powerup::Spawn(pos,Vec2(0, 1), Sprite::EnergySphere );
        Powerup::PowerupList[Index].SetSpecialEffect(Powerup::HealthPowerup);
        return;
    }
    if(RANDOM(100) > 10) // Spawn a random drop of 90% Enegy Sphere
    {
        int Index = Powerup::Spawn(pos, Vec2(0), Sprite::HealthPowerup);
        Powerup::PowerupList[Index].SetSpecialEffect(Powerup::EnergyPowerup);
        return;
    }
    if(RANDOM(100) > 99) // Spawn a random drop of 1% of NUKE
    {
        int Index = Powerup::Spawn(pos, Vec2(0), Sprite::ExtraLife);
        Powerup::PowerupList[Index].SetSpecialEffect(Powerup::ExtraLife);
        SoundEffect::Extralife->Play();
        return;
    }

}
void DragonUpdate(Enemy *object)
{
    if(object->Alive)
    {
        object->Age++;

        object->CollisionBox->Body.Force = Vec2(sin(((int)(object->Age)) * 3.14159 / 180), .1);//(object->Speed;//Vec2(0,.3);
        object->CollisionBox->Update();
        object->Position = object->CollisionBox->Position;
        object->Picture.Position =  object->Position;
        
// This Spawns a Fireball out of the Dragons Mouth Every 100 Frames. Going to make this a Tad Bit Random
        if(object->Age % 100 == 0) 
        {
             int Index = EnemyProjectile::Spawn(object->Position,Vec2(0, 3) , Sprite::FireBall);
             EnemyProjectile::EnemyProjectileList[Index].BulletPower = 10;
        }
 //   Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x + 15,
 //              GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -3), Bullet);

// If the Enemy leaves the screen than Despawn
       if( object->Position.y > SCREENHEIGHT + SCREEN_BUFFER_AREA || object->Position.y < -SCREEN_BUFFER_AREA )
       {
           Entity::PlayerOne->Score -= (int)(object->Worth * .25);

           object->Kill();
         return;
       }
// If Enemy is dead Award the player What the Enemy was worth and Spawn an Explosion Sprite
       if (object->Health <= 0)
       {
           Entity::PlayerOne->NumberOfKills++;
           Entity::PlayerOne->Score+=object->Worth;

           StaticObject::Spawn(object->Position, Vec2(0), 1000, *Sprite::Explosion);

           SoundEffect::Boom5->Play();

           //if(RANDOM(100) > 95) // Spawn a random drop of 95% Enegy Sphere
          // {
           //    int Index = Powerup::Spawn(object->Position,Vec2(0, 1), Sprite::EnergySphere );
          // }
           SpawnDrop(object->Position);
           object->Kill(); // Despawn Enemy
         return;
       }
    }
}
void DiveBomber(Enemy *object) // This is the Green Eye Currently
{
    float DiveTimer = 0;
    if(object->Alive)
    {
        object->Age++;

        switch(object->Picture.CURRENT_STATE)
        {
            case 0:
                object->CollisionBox->Body.Velocity = Vec2(cos(((int)(object->Age)) * 3.14159 / 180), sin(((int)(object->Age)) * 3.14159 / 180));//(object->Speed;//Vec2(0,.3);
                object->CollisionBox->Update();
                object->Position = object->CollisionBox->Position;
                object->Picture.Position =  object->Position;
// This Spawns a Fireball out of the Dragons Mouth Every 100 Frames. Going to make this a Tad Bit Random
                if(object->Age % 100 == 0) 
                {
                    object->Picture.CURRENT_STATE = 1;
                    DiveTimer = SDL_GetTicks();
                }
            break;

            case 1:
                if((SDL_GetTicks() - DiveTimer) > 100)
                {
                    object->Picture.CURRENT_STATE = 2;
                    object->CollisionBox->Update();
                    object->Position = object->CollisionBox->Position;
                    object->Picture.Position =  object->Position;
                }


            break;
            case 2:
                object->CollisionBox->Body.Velocity = Vec2(0,6);
                object->CollisionBox->Update();
                object->Position = object->CollisionBox->Position;
                object->Picture.Position =  object->Position;
            break;
        }

 //   Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x + 15,
 //              GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -3), Bullet);

// If the Enemy leaves the screen than Despawn
       if( object->Position.y > SCREENHEIGHT + SCREEN_BUFFER_AREA || object->Position.y < -SCREEN_BUFFER_AREA )
       {

 
           Entity::PlayerOne->Score -= (int)(object->Worth *.5);

           object->Kill();
           return;
       }
// If Enemy is dead Award the player What the Enemy was worth and Spawn an Explosion Sprite
       if (object->Health <= 0)
       {
           Entity::PlayerOne->NumberOfKills++;
           Entity::PlayerOne->Score+=object->Worth;


           StaticObject::Spawn(object->Position, Vec2(0), 1000, *Sprite::Explosion);
           SpawnDrop(object->Position);
           SoundEffect::Boom5->Play();

           object->Kill(); // Despawn Enemy
           return;
       }
//------------------------------------------------------------------------------------------------------------------
    }

}
void Default_Response(Entity *other) //  Do Nothing
{
}
void DefaultEnemyUpdate(Enemy *object)
{
    if(object->Alive == true)
    {
        object->Age++;
        object->CollisionBox->Body.Force = object->Speed;//Vec2(0,.3);

        object->CollisionBox->Update();
        object->Position = object->CollisionBox->Position;
        object->Picture.Position = object->Position;

// If the Enemy leaves the screen than Despawn
       if( object->Position.y > SCREENHEIGHT + SCREEN_BUFFER_AREA || object->Position.y < -SCREEN_BUFFER_AREA )
       {
           Entity::PlayerOne->Score-=(int)(object->Worth * .5);
           object->Kill();
           return;
       }
// If Enemy is dead Award the player What the Enemy was worth and Spawn an Explosion Sprite
       if (object->Health <= 0)
       {
           Entity::PlayerOne->NumberOfKills++;
           Entity::PlayerOne->Score+=object->Worth;

        //   StaticObject::Spawn(object->Position, Vec2(0), 1000, Sprite::Explosion);
           StaticObject::Spawn(object->Position, Vec2(0, -.3), 1000, *Sprite::CthuluDeath);
          // if(RANDOM(100) > 10) // Spawn a random drop of 95% Enegy Sphere
          // {
          //     Powerup::Spawn(object->Position, Vec2(0), Sprite::FireOrb);
          //}
           SpawnDrop(object->Position);
           SoundEffect::Boom3->Play();
           object->Kill(); // Despawn Enemy
           return;
       }
    }
}   
void BossDragon(Enemy *object)
{
    if(object->Alive)
    {
        Vec2 DirectionMoving;
// This Spawns a Fireball out of the Dragons Mouth Every 100 Frames. Going to make this a Tad Bit Random
        object->MovementTimer--;

// MAKE A CHOICE AS TO WHICH DIRECTION TO MOVE AND HOW LONG TO GO THAT DIRECTION
        float S = 0.2f;
        int Choice = (int)(RANDOM(4));
        if(object->MovementTimer <= 0) 
        {
            switch(Choice)
            {
                case FORWARD:
                    object->Speed = Vec2(0, S);
                    object->Picture.CURRENT_STATE = FORWARD;
                    object->MovementTimer = RANDOM(50);
                break;
                case BACKWARDS:
                    object->Speed = Vec2(0,-S);
                    object->Picture.CURRENT_STATE = BACKWARDS;
                    object->MovementTimer = RANDOM(50);
                break;
                case LEFT:
                    object->Speed = Vec2(-S*2, 0);
                    object->Picture.CURRENT_STATE = LEFT;
                    object->MovementTimer = RANDOM(150);
                break;
                case RIGHT:
                    object->Speed = Vec2( S*2, 0);
                    object->Picture.CURRENT_STATE = RIGHT;
                    object->MovementTimer = RANDOM(150);
                break;
            }
        }

// CLAMP THE POSITION OF THE DRAGON TO THE SCREEN SO HE DOES NOT GO TO FAR AWAY
        if(object->Position.x <= (0 + (object->Picture.Size.x * .05f)))  // Went to far Left turn Right
        {
            object->Picture.CURRENT_STATE = 2;
            Choice = RIGHT;
            object->Speed = Vec2( 1.0f, 0);
        }
        else if(object->Position.x >= (SCREENWIDTH - (object->Picture.Size.x * .05f))) // Went to far Right turn left
        {
            object->Picture.CURRENT_STATE = 1;
            Choice = LEFT;
            object->Speed = Vec2(-1.0f, 0);
        }
        
        if(object->Position.y <= (0 + (object->Picture.Size.y * .05f)))  // Went to high up face down
        {
            object->Speed = Vec2(0, 1.0f);
            Choice = FORWARD;
            object->Picture.CURRENT_STATE = 0;
        }
        else if(object->Position.y >= ((SCREENHEIGHT * 0.5f) - (object->Picture.Size.y * .05f)))  // Went to far down some other way
        {
            object->Picture.CURRENT_STATE = 3;
            Choice = BACKWARDS;
            object->Speed = Vec2(0,-1.0f);
        }
       

// IF ENEMY IS DEAD AWARD THE PLAYER THE POINTS FOR IT AND SPAWN AN EXPLOSION SPRITE
       if (object->Health <= 0)
       {
               Entity::PlayerOne->NumberOfKills++;
               Entity::PlayerOne->Score+=object->Worth;
               
               StaticObject::Spawn(object->Position, Vec2(0), 1000, *Sprite::Explosion);
               
               SoundEffect::Boom5->Play();
               SpawnDrop(object->Position);
               object->Kill(); // Despawn Enemy
           return;
       }

// SPAWN THE FIRE BALLS AND ROTATE THEM FOR THE DIRECTION THE DRAGON IS CURRENTLY FACING
       int Index = 0;
       if(object->Age % 100 == 0) 
       {
            switch(Choice)
            {
                case LEFT:
                    Index = EnemyProjectile::Spawn(object->Position, Vec2(-4,0), Sprite::GreenFireBall);
                    EnemyProjectile::EnemyProjectileList[Index].Picture.Angle = 180 ;
                    EnemyProjectile::EnemyProjectileList[Index].BulletPower = 20;
                break;
                case RIGHT:
                    Index = EnemyProjectile::Spawn(object->Position,  Vec2(4,0), Sprite::GreenFireBall);
                    EnemyProjectile::EnemyProjectileList[Index].Picture.Angle =  0;
                    EnemyProjectile::EnemyProjectileList[Index].BulletPower = 20;
                break;
                case FORWARD: 
                    Index = EnemyProjectile::Spawn(object->Position, Vec2(0,4), Sprite::GreenFireBall);
                    EnemyProjectile::EnemyProjectileList[Index].Picture.Angle =  90;
                    EnemyProjectile::EnemyProjectileList[Index].BulletPower = 20;

                break;
                case BACKWARDS:
                    Index = EnemyProjectile::Spawn(object->Position, Vec2(0,-4), Sprite::GreenFireBall);
                    EnemyProjectile::EnemyProjectileList[Index].Picture.Angle =  270;
                    EnemyProjectile::EnemyProjectileList[Index].BulletPower = 20;
               break;
            }
       }
 
// STANDARD UPDATE STUFF, INCREASE AGE AND UPDATE COLLISIONBOX
        object->Age++;
        object->CollisionBox->Body.Force +=  object->Speed;//(DirectionMoving); //Vec2(sin(((int)(object->Age)) * 3.14159 / 180), .1);//(object->Speed;//Vec2(0,.3);
        object->CollisionBox->Update();
        object->Position = object->CollisionBox->Position;
        object->Picture.Position =  object->Position;


// Render the Red background for the Dragons healthbar.
        SDL_Rect HBar ={object->Position.x - (object->Picture.Size.x / 2 ) + 15, 
                        object->Position.y - (object->Picture.Size.y / 2),  
                        100, 5};
        SDL_SetRenderDrawColor(SCREEN->Renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(SCREEN->Renderer, &HBar);


// Render the Green Dragons Healthbar 
        float G = (object->Health *(100.0 / BOSSDRAGON_MAXLIFE));
        SDL_Rect HBar2 ={object->Position.x - (object->Picture.Size.x / 2 ) + 15, 
                        object->Position.y - (object->Picture.Size.y / 2),  
                         G, 5};
        SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(SCREEN->Renderer, &HBar2);
    }
}


// I do not think that I use this
// It seems I do use them but never truly use them from the looks of it
// It would be easier if I did this and would have to use this system if my game grew larger as I would make Presets
// For each entity so that the response system can be generic but the proper function pointer was called. 
void EnemyProjectileResponse(Enemy *mob,  Projectile *bullet)
{
    mob->Health-= 10;
}
void DefaultProjectileResponse(Entity *mob,  Projectile *bullet)
{
    bullet->Kill();
}


/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                    OBJECT CONSTRUCTION FUNCTIONS                                                                                                                                                                                                                                                                                         
                                                                                                                                                                         
========================================================================================================================================================================================*/
void Entity::Unload()
{
    // ENTITY
    delete(PlayerOne);
    delete(Explosion);
    delete(Dragon);
    delete(EnergySphere);
    delete(CthuluEye);
    delete(Bullets);
    delete(FireBall);
    delete(GreenEye);
}

Enemy::Enemy() 
{
        Health = 100;
        Alive = false;
        Position = Vec2(0,0);
        Picture = nullptr;
        Invincible = false;
        ID = 0;
        Age = 0;
        Type = EntityType::EnemyEntity;
        SetSpecialUpdate(DefaultEnemyUpdate);
}
Enemy::Enemy(Vec2  pos, Vec2 vel, Sprite img)
{
        Health = 100;
        Alive = true;
        Position = Vec2(0,0);
        Picture = img;
        Age = 0;
        
        Invincible = false;
        
        CollisionResponse.SetEnemyResponse      (Default_Response);  
        CollisionResponse.SetPlayerReponse      (Default_Response); 
        CollisionResponse.SetPowerUpReponse     (Default_Response);
        CollisionResponse.SetStaticObjectReponse(Default_Response);
        CollisionResponse.SetProjectileReponse  (EnemyProjectileResponse);

        Type = EntityType::EnemyEntity;
        SetSpecialUpdate(DefaultEnemyUpdate);
}
Player::Player()
{
    Health = 100;
    EnergyLevel = 100;
    Lives = 3;
    CollisionResponse.SetEnemyResponse      (Default_Response);  
    CollisionResponse.SetPlayerReponse      (Default_Response); 
    CollisionResponse.SetPowerUpReponse     (Default_Response);
    CollisionResponse.SetStaticObjectReponse(Default_Response);
    CollisionResponse.SetProjectileReponse  (EnemyProjectileResponse);
    NumberOfKills = 0;
    Invincible = false;
    Type = EntityType::PlayerEntity;
    HitWave = SoundEffect::PlayerHit; 
    SpecialUpdate  = NULL;
}
Powerup::Powerup(Vec2 pos, Vec2 vel, Sprite *img)
{
    CollisionResponse.SetEnemyResponse      (Default_Response);  
    CollisionResponse.SetPlayerReponse      (Default_Response); 
    CollisionResponse.SetPowerUpReponse     (Default_Response);
    CollisionResponse.SetStaticObjectReponse(Default_Response);
    CollisionResponse.SetProjectileReponse  (EnemyProjectileResponse);

    Type = EntityType::PowerUpEntity;

    Position = pos; 
    CollisionBox = img->MakeCollisionBox();
    CollisionBox->Position = pos;
    CollisionBox->Body.Force = vel;
    Picture = *img;
    Alive = false;
    SpecialUpdate  = NULL;
    SpecialEffect  = NULL;
    Death = SoundEffect::Boom1; 
}
Projectile::Projectile(Vec2 pos, Vec2 vel, Sprite *img)
{
    Position = pos; 
    CollisionBox = img->MakeCollisionBox();
    CollisionBox->Position = pos;
    CollisionBox->Body.Velocity = vel; // Steady speed just changed this watch out
    Picture = *img;
    Alive = false;
    Type = EntityType::ProjectileEntity;
    SpecialUpdate  = NULL;
    Death = SoundEffect::Boom1;   
}
StaticObject::StaticObject() 
{
        Alive = false;
        Position = Vec2(0,0);
        Picture = nullptr;
        Invincible = true;
        ID   = 0;
        Age  = 0;
        Type = EntityType::StaticEntity;
        SpecialUpdate = NULL;
}
StaticObject::StaticObject(Vec2  pos, Vec2 vel, Sprite img)
{
 
        Alive = true;
        Position = Vec2(0,0);
        Picture = img;
        Age = 0;
        
        Invincible = false;
        
        CollisionResponse.SetEnemyResponse      (Default_Response);  
        CollisionResponse.SetPlayerReponse      (Default_Response); 
        CollisionResponse.SetPowerUpReponse     (Default_Response);
        CollisionResponse.SetStaticObjectReponse(Default_Response);
        CollisionResponse.SetProjectileReponse  (EnemyProjectileResponse);
        Type = EntityType::StaticEntity;
        SetSpecialUpdate(DefaultEnemyUpdate);
}
EnemyProjectile::EnemyProjectile(Vec2 pos, Vec2 vel, Sprite *img)
{
    Position = pos; 
    CollisionBox = img->MakeCollisionBox();
    CollisionBox->Position = pos;
    CollisionBox->Body.Velocity = vel;
    CollisionBox->Body.Force = Vec2(0,0);
    Picture = *img;
    Alive = false;
    Type = EntityType::ProjectileEntity;
    BulletPower = 3;
    SpecialUpdate  = NULL;
    Death = SoundEffect::Boom1; 
}


/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                    INITIALIZATION FUNCTIONS                                                                                                                                                                                                                                                                                         
                                                                                                                                                                         
========================================================================================================================================================================================*/



void Enemy::Initialize()
{
    EnemyValidID.reserve(MAX_ENEMIES);
    for_loop(Count, MAX_ENEMIES)
    {
        EnemyValidID.push_back(MAX_ENEMIES - (Count + 1));
    }
}
void Entity::Initialize()
{
        PlayerOne = new Player();
        PlayerOne->Position = Vec2(SCREENWIDTH *.5,SCREENHEIGHT -100);
        PlayerOne->Picture = *Sprite::ShipSprite; //Sprite(SpriteSheets->Ship, 1);
        PlayerOne->Picture.Size = Vec2(160 * .6);

        PlayerOne->Picture.STATE[0] = State(MAKE_Rect(0, 0,160, 160), 4);
        PlayerOne->Picture.STATE[1] = State(MAKE_Rect(0, 160,160, 160), 4);
        PlayerOne->Picture.STATE[2] = State(MAKE_Rect(0, 320,160, 160), 4);
        PlayerOne->Picture.STATE[3] = State(MAKE_Rect(0, 480,160, 160), 4);


        PlayerOne->Picture.ANIMATED = true;
        PlayerOne->Picture.AnimationSpeed = 50;
        PlayerOne->CollisionBox = PlayerOne->Picture.MakeCollisionBox();
        
        
        Explosion = new StaticObject(Vec2(-10,-10), Vec2 (0,0), *Sprite::Explosion);

        Entity::Dragon       = new Enemy(Vec2(-99,-99), Vec2(0,0), *Sprite::DragonSprite);
        Entity::EnergySphere = new Powerup(Vec2(-99,-99), Vec2(0,0), Sprite::EnergySphere);
        Entity::Explosion    = new StaticObject(Vec2(-99,-99), Vec2(0,0), *Sprite::Explosion);
        Entity::CthuluEye    = new Enemy(Vec2(-99,-99), Vec2(0,0), *Sprite::CthuluEye);
        Entity::Bullets      = new Projectile(Vec2(-99,-99), Vec2(0,0), Sprite::Bullet);
        Entity::FireBall     = new EnemyProjectile(Vec2(-99,-99), Vec2(0,0), Sprite::FireBall);
        Entity::GreenEye     = new Enemy(Vec2(-99,-99), Vec2(0,0), *Sprite::GreenEye);
}
void Powerup::Initialize()
{
    PowerupValidID.reserve(MAX_POWERUPS);
    for_loop(Count, MAX_POWERUPS)
    {
       PowerupValidID.push_back(MAX_POWERUPS - (Count + 1));
    }
}
void Projectile::Initialize()
{
    ProjectileValidID.reserve(MAX_PROJECTILES);
    for_loop(Count, MAX_PROJECTILES)
    {
        ProjectileValidID.push_back(MAX_PROJECTILES - (Count + 1));
    }
}
void StaticObject::Initialize()
{
    StaticObjectValidID.reserve(MAX_STATICOBJECTS);
    for_loop(Count, MAX_STATICOBJECTS)
    {
        StaticObjectValidID.push_back(MAX_STATICOBJECTS - (Count + 1));
    }
}
void EnemyProjectile::Initialize()
{
    ProjectileValidID.reserve(MAX_PROJECTILES);
    for_loop(Count, MAX_PROJECTILES)
    {
        ProjectileValidID.push_back(MAX_PROJECTILES - (Count + 1));
    }
}


/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                    SPAWN FUNCTIONS                                                                                                                                                                                                                                                                                         
                                                                                                                                                                         
========================================================================================================================================================================================*/


int Enemy::Spawn(Vec2 pos, Vec2 vel, Sprite img)
{
    if(EnemyValidID.empty() != true)
    {
        int Index = EnemyValidID.back();
        EnemyList[Index].Alive = true;
        EnemyList[Index].Health = 100;
        EnemyList[Index].Position = pos;
        EnemyList[Index].Picture = img;

//*********************************!!!! WARNING !!!!!!  What The Fuck Is This Shit ************************************************
// GLM Occasionally throws an Error here for seeingly no reason so instead of using their = I will attempt to use
// Just a typical = instead of the glm::vec2 = and pray that fixes it

//FUCK ITS STILL HAPPENING WTF

// This time Enemies just stopped spawning for about an entire minute for seemingly no reason.
// I had one life left and I came back they never spawned and then thrown this Access error.
// I have no idea... Its got to be because of threading the loading screen, that is the only thing I can think of right now 
// because that is around the time this all started.
//   916: 			this->_Orphan_all();
// 000CDC65  mov         esi,esp  
// 000CDC67  mov         ecx,dword ptr [this]  
// 000CDC6A  call        dword ptr ds:[121624h]  //<- Must be the error
// 000CDC70  cmp         esi,esp    // Next line of code to be called.
// 000CDC72  call        __RTC_CheckEsp (0BBEE2h)  
//  In the above This is SpriteSheet Explosion1;
// Damnit... Index == 194 and yet EnemyList only has 50 Elements... Thats gotta be it
// How has that not been crashing it already?
// Nope not it atleast not why the enemies stop spawning. The ValidID has gone totally blank...
// UPDATE: *I BELIEVE I SOLVED THIS ISSUE AND IT WAS AN ERROR DUE TO NOT ENOUGH ENEMIES BEING ABLE TO SPAWN OR SOME SHIT LIKE THAT
        EnemyList[Index].Speed.x = vel.x;
        EnemyList[Index].Speed.y = vel.y;
// ******************************************************************************************************************************
        EnemyList[Index].CollisionBox = EnemyList[Index].Picture.MakeCollisionBox();
        EnemyList[Index].CollisionBox->Body.Position = pos;
        EnemyList[Index].ID = Index;
        EnemyList[Index].Age = 0;
        EnemyList[Index].Worth = 50;
//        EnemyList[Index].CollisionBox->Body.Velocity = Vec2(0,5);
        EnemyValidID.pop_back();
        return Index;
    }
return 0;
}
int Powerup::Spawn(Vec2 pos, Vec2 vel, Sprite *img)
{
    if(PowerupValidID.empty() != true)
    {
        int Index = PowerupValidID.back();
       // PowerupList[Index] = *Entity::Bullets;
        PowerupList[Index].Alive = true;
        PowerupList[Index].Position = pos;
        PowerupList[Index].Picture = *img;
        //PowerupList[Index].Speed = vel;
        PowerupList[Index].CollisionBox = PowerupList[Index].Picture.MakeCollisionBox();
        PowerupList[Index].CollisionBox->Body.Position = pos;
        PowerupList[Index].ID = Index;
        PowerupList[Index].Age = 0;
        PowerupList[Index].EnergyBuff = 10;
        PowerupList[Index].Death = SoundEffect::Boom2; 
        PowerupList[Index].CollisionBox->Body.Velocity = vel;
        PowerupValidID.pop_back();
        return Index;
    }
return 0;
}
int Projectile::Spawn(Vec2 pos, Vec2 vel, Projectile *object)
{
    if(ProjectileValidID.empty() != true)
    {
        int Index = ProjectileValidID.back();
        ProjectileList[Index] = *Entity::Bullets;

        ProjectileList[Index].Alive = true;
        ProjectileList[Index].Position = pos;

        ProjectileList[Index].Speed = vel;

        ProjectileList[Index].CollisionBox = object->CollisionBox; //ProjectileList[Index].Picture.MakeCollisionBox();
        ProjectileList[Index].CollisionBox->Body.Position = pos;
        ProjectileList[Index].ID = Index;
        ProjectileList[Index].Age = 0;
        ProjectileList[Index].Death = SoundEffect::Boom2;  // Change1
        ProjectileList[Index].CollisionBox->Body.Velocity = vel;
        ProjectileValidID.pop_back();
        return Index;
    }
return 0;
}
int Projectile::Spawn(Vec2 pos, Vec2 vel, Sprite *img)
{
    if(ProjectileValidID.empty() != true)
    {
        int Index = ProjectileValidID.back();
        ProjectileList[Index] = *Entity::Bullets;

        ProjectileList[Index].Alive = true;
        ProjectileList[Index].Position = pos;
        ProjectileList[Index].Picture = *img;
        ProjectileList[Index].Speed = vel;
        ProjectileList[Index].CollisionBox = ProjectileList[Index].Picture.MakeCollisionBox();
        ProjectileList[Index].CollisionBox->Body.Position = pos;
        ProjectileList[Index].ID = Index;
        ProjectileList[Index].Age = 0;
        ProjectileList[Index].Death = SoundEffect::Boom2; 
        ProjectileList[Index].CollisionBox->Body.Velocity = vel;
        ProjectileValidID.pop_back();
        return Index;
    }
return 0;
}
int StaticObject::Spawn(Vec2 pos, Vec2 vel, double lifespan,Sprite img)
{
    if(StaticObjectValidID.empty() != true)
    {

        int Index = StaticObjectValidID.back();
        StaticObjectList[Index].Alive = true;
        StaticObjectList[Index].Timer = SDL_GetTicks();
        StaticObjectList[Index].Position = pos;
        StaticObjectList[Index].Picture = img;
        StaticObjectList[Index].Speed = vel;
        StaticObjectList[Index].CollisionBox = StaticObjectList[Index].Picture.MakeCollisionBox();
        StaticObjectList[Index].CollisionBox->Body.Position = pos;
        StaticObjectList[Index].ID = Index;
        StaticObjectList[Index].Age = 0;
        StaticObjectList[Index].CollisionBox->Body.Velocity = Vec2(0,5);
        StaticObjectValidID.pop_back();
        return Index;
    }
return 0;
}
int EnemyProjectile::Spawn(Vec2 pos, Vec2 vel, EnemyProjectile *object)
{
    if(ProjectileValidID.empty() != true)
    {
        int Index = ProjectileValidID.back();
        EnemyProjectileList[Index] = *Entity::FireBall;


        EnemyProjectileList[Index].Alive = true;
        EnemyProjectileList[Index].Position = pos;

        EnemyProjectileList[Index].Speed = vel;

        EnemyProjectileList[Index].CollisionBox = object->CollisionBox; //ProjectileList[Index].Picture.MakeCollisionBox();
        EnemyProjectileList[Index].CollisionBox->Body.Position = pos;
        EnemyProjectileList[Index].ID = Index;
        EnemyProjectileList[Index].Age = 0;
        EnemyProjectileList[Index].Death = SoundEffect::Boom2;  // Change1
        EnemyProjectileList[Index].CollisionBox->Body.Velocity = vel;
        ProjectileValidID.pop_back();
        return Index;
    }
return 0;
}
int EnemyProjectile::Spawn(Vec2 pos, Vec2 vel, Sprite *img)
{
    if(ProjectileValidID.empty() != true)
    {
        int Index = ProjectileValidID.back();
        EnemyProjectileList[Index] = *Entity::FireBall;
        EnemyProjectileList[Index].Alive = true;
        EnemyProjectileList[Index].Position = pos;
        EnemyProjectileList[Index].Picture = *img;
        EnemyProjectileList[Index].Speed = vel;
        EnemyProjectileList[Index].CollisionBox = EnemyProjectileList[Index].Picture.MakeCollisionBox();
        EnemyProjectileList[Index].CollisionBox->Body.Position = pos;
        EnemyProjectileList[Index].ID = Index;
        //EnemyProjectileList[Index].BulletPower = 25;// Change1.... Should I uncomment this
        EnemyProjectileList[Index].Age = 0;
        EnemyProjectileList[Index].Death = SoundEffect::Boom2;  
        EnemyProjectileList[Index].CollisionBox->Body.Velocity = vel;

        ProjectileValidID.pop_back();
        return Index;
    }
return 0;
}


/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                    UPDATE FUNCTIONS                                                                                                                                                                                                                                                                                         
                                                                                                                                                                         
========================================================================================================================================================================================*/

void Enemy::Update() 
{
    SpecialUpdate(this);
}
void Player::Update() 
{
    Picture.Position = CollisionBox->Position;

    if(EnergyLevel < 100)
    {
        EnergyLevel += 1;
    }

    CollisionBox->Update();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  CLAMP THE PLAYERS POSITION  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
    if(CollisionBox->Body.Position.x < 10) CollisionBox->Body.Position.x = 10;
    if(CollisionBox->Body.Position.x > (SCREENWIDTH )) CollisionBox->Body.Position.x = (SCREENWIDTH); 
    
    if(CollisionBox->Body.Position.y <  0) CollisionBox->Body.Position.y =  0;
    if(CollisionBox->Body.Position.y > (SCREENHEIGHT)) CollisionBox->Body.Position.y = (SCREENHEIGHT );

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Position = CollisionBox->Body.Position;
    if(!Invincible)// This checks to see if the Player was recently Hit, if not Check for Collision
    {
        for(auto &other: Enemy::EnemyList)// This checks to see if there has been a Collision between the Player and an Enemy
        {
            if(other.Alive)
            {
                if(CollisionBox->IsCollision(other.CollisionBox) == true)
                {
                    Entity::PlayerOne->Score-= other.DamagePoints;
                    Health -= other.DamagePoints;
                    Invincible = true;
                    InvincibilityTimer = SDL_GetTicks();
                    HitWave->Play();
                    Print("Enemy Hit the Player"); 
                }
            }
        }
    }
    else // The player has recently been hit that we check its timer to see how long ago it was hit and if past a given time we Reset it
    {
        Picture.CURRENT_STATE = 1;
        if(SDL_GetTicks() - InvincibilityTimer > 500)
        {
            Invincible = false;
            Picture.CURRENT_STATE = 0;
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    if(Health <= 0) // If the player is dead... Kill it, take a life and reset
    {
        Kill();
    }

}
void Powerup::Update() 
{
    if(Alive)
    {
        Age++; // Increase the age so we can kill it if its getting to old.
        if(Age >= 500)
        {
            Kill();
            return;
        }
        
// CollisionBox->Body.Velocity = Speed; //Set the Velocity Tinker with this to get a good speed out of the projectiles
        CollisionBox->Update();

        if(CollisionBox->IsCollision(Entity::PlayerOne->CollisionBox)) // Means it collided with the player
        {
            SpecialEffect();
            Kill();
            Print("Picked up Powerup");
        }
        Position = CollisionBox->Position;// Set the Position of the Bullet to the CollisionBox position
        Picture.Position = Position;     // Set the Sprite Image to the Position of the Projectile
    }
}
void Projectile::Update()
{
    if(Alive)
    {
        Age++; // Increase the age so we can kill it if its getting to old.
        if(Age > 200)
        {
            Kill();
            return;
        }
        
        CollisionBox->Body.Velocity = Speed; // Apply force so it moves. Tinker with this to get a good speed out of the projectiles
        CollisionBox->Update();

        for(auto &E: Enemy::EnemyList) // Check to see if the Players Bullet hit an Enemy
        {
            if(E.Alive) // But only if the Bullet is Alive
            {
                if(E.CollisionBox->IsCollision(CollisionBox))
                {
                    E.Health -= BulletPower;
                    Kill();
                    SoundEffect::Boom8->Play();
                    Print("Bullet Hit Enemy");
                }
            }
        }
        Position = CollisionBox->Position;// Set the Position of the Bullet to the CollisionBox position
        Picture.Position = Position;     // Set the Sprite Image to the Position of the Projectile
    }
}
void StaticObject::Update() 
{
    if( Alive == true)
    {
        Age++;
        CollisionBox->Body.Force = Vec2(0,0);//Speed;
        
        CollisionBox->Update();
        Position = CollisionBox->Position;
        Picture.Position = Position;

        if( Position.y > SCREENHEIGHT + SCREEN_BUFFER_AREA || Position.y < -SCREEN_BUFFER_AREA )
        {
            Kill();
        }
        
        if (SDL_GetTicks()- Timer >= 1000)
        {
              Kill();
        }
    }
 
}
void EnemyProjectile::Update()
{
    if(Alive)
    {
        Age++; // Increase the age so we can kill it if its getting to old.
        if(Age >= 200)
        {
            Kill();
            return;
        }
        
        CollisionBox->Body.Velocity = Speed; //Set the Velocity Tinker with this to get a good speed out of the projectiles
        CollisionBox->Update();

        if(CollisionBox->IsCollision(Entity::PlayerOne->CollisionBox)) // Means it collided with the player
        {
            Entity::PlayerOne->Health -= BulletPower;
            Entity::PlayerOne->Invincible = true;
            Entity::PlayerOne->InvincibilityTimer = SDL_GetTicks();
            Death->Play();
            Kill();
            Print("Player Hit by FireBall");
        }
        Position = CollisionBox->Position;// Set the Position of the Bullet to the CollisionBox position
        Picture.Position = Position;     // Set the Sprite Image to the Position of the Projectile
    }
}

/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                DEATH & DESPAW FUNCTIONS                                                                                                                                                                                                                                                                                         
                                                                                                                                                                         
========================================================================================================================================================================================*/

void Enemy::Kill()
{
    EnemyValidID.push_back(ID);  
     Alive = false;
}
void Player::Kill()   
{
// There has to be an error here because the enemies randomly stop spawning and I think this might be the reason...
// Check how many lives are left, Deduct points and respawn if appropriate
 Lives--;
 World::Reset();

    if(Lives <= 0)
    {
        while(SCREEN->LOOP_GAME())
        {

            SCREEN->CLS();
            FontRender::Fonts->Write("GAME OVER MAN!", Vec2( SCREENWIDTH / 2 - 150, SCREENHEIGHT/ 2));
            FontRender::Fonts->Write("Press Enter to Restart", Vec2(((SCREENWIDTH *.5) -(20*14)), (SCREENHEIGHT *.5 + 30)) );
            
            std::string Str = std::to_string(Player::PlayerOne->Score);
            const char* S = Str.c_str();
            FontRender::Fonts->Write("Score: " ,Vec2(10,10));
            FontRender::Fonts->Write(S, Vec2(160,10));

            if(SCREEN->Keyboard.KeyState[SDL_SCANCODE_RETURN] == true)
            {
//TODO: SetUp a Display states function here
// Show the Top Scores... Number of Kills, Pass/Kill Ratio etc...etc
// Why in the fuck are the ID vectors going empty here?
// OK... I think I got it..... It was Killing off the Creatures on Reset but never giving their IDs back to the ValidID vector
// When the game starts over ValidID vector was empty and nothing could spawn.
                Player::PlayerOne->Score = 0;
                Player::PlayerOne->Lives = 4;
                return;// break; <-- cCould it have been this? The accidental break. Was that UDB or WTF?
// NOPE wasnt that....
            }
            SCREEN->SYNC();
        }
    }
    else
    {
        FontRender::Fonts->Write("~ Get Ready ~", Vec2(SCREENWIDTH / 2 - 110, SCREENHEIGHT/ 2));
        SCREEN->SYNC();
        float time = SDL_GetTicks();
        float A =0;
        while(A < 5000){A = SDL_GetTicks() - time;}
    }
    Health = 100;
}
void Powerup::Kill() 
{
    PowerupValidID.push_back(ID);   
    Alive = false;
}
void Projectile::Kill()
{
    ProjectileValidID.push_back(ID);   
    Alive = false;
}
void StaticObject::Kill()
{
    StaticObjectValidID.push_back(ID);  
    Alive = false;
}
void EnemyProjectile::Kill()
{
    ProjectileValidID.push_back(ID);   
    Alive = false;
}


/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                   RENDERING FUNCTIONS                                                                                                                                                                                                                                                                                         
                                                                                                                                                                         
========================================================================================================================================================================================*/

void Enemy::Render()
{
    Picture.Render();
}
void Player::Render()
{
    Picture.Render();
}
void Powerup::Render()
{
    Picture.Render();
}
void Projectile::Render()
{
    Picture.Position = CollisionBox->Position;
    Picture.Render();
}
void StaticObject::Render()
{
    Picture.Render();
}
void EnemyProjectile::Render()
{
    Picture.Position = CollisionBox->Position;
    Picture.Render();
}

/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                   RESPONSE FUNCTIONS                                                                                                                                                                                                                                                                                         
                                                                                                                                                                         
========================================================================================================================================================================================*/


void Enemy::Response(Entity *other)
{
    switch(other->Type)
    {
        case EnemyEntity:
            CollisionResponse.EnemyResponse(other);
        break;
        
        case StaticEntity:
            CollisionResponse.StaticObjectReponse(other);
        break;
        
        case PowerUpEntity:
            CollisionResponse.PowerUpReponse(other);
        break;
        
        case PlayerEntity:
            CollisionResponse.PlayerReponse(other);
        break;
    }
}
void Player::Response(Entity *other)
{
    switch(other->Type)
    {
        case EnemyEntity:
            CollisionResponse.EnemyResponse(other);
        break;
        
        case StaticEntity:
            CollisionResponse.StaticObjectReponse(other);
        break;
        
        case PowerUpEntity:
            CollisionResponse.PowerUpReponse(other);
        break;
        
        case PlayerEntity:
            CollisionResponse.PlayerReponse(other);
        break;
    }
}
void Powerup::Response(Entity *other)
{
}
void Projectile::Response(Entity *other){}
void StaticObject::Response(Entity *other)
{
    switch(other->Type)
    {
        case EnemyEntity:
            CollisionResponse.EnemyResponse(other);
        break;
        
        case StaticEntity:
            CollisionResponse.StaticObjectReponse(other);
        break;
        
        case PowerUpEntity:
            CollisionResponse.PowerUpReponse(other);
        break;
        
        case PlayerEntity:
            CollisionResponse.PlayerReponse(other);
        break;
    }
}
void EnemyProjectile::Response(Entity *other){}
