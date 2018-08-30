#include"Entities.h"
#include"Fonts.h"


int Score = 0;
/*
                                                                                                                   
                                       ENTITY CLASS:
                               _____________________________
                     MANAGES THE PLAYER, ENEMIES AND STATIC WORLD OBJECTS.                                                                                               
                     POSSIBLY ADD THE PROJECTILES INTO THIS IN THE FUTURE.                                                                                               

    8/27/2018 
*/

/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                                                                                                                                                                      
                                     Various Game Mechanics and Collision Responses given to Entities to describe their 
   Actions throughout the game. Function pointers are handed to the Entity to carry out said actions                                                                                                                                                                                   
                                                                                                                                                                                      
                                                                                                                                                                                      
                                                                                                                                                                                                                                                                                           
 ======================================================================================================================================================================================== */

void Default_Response(Entity *other) //  Do Nothing
{
}
void DefaultProjectileResponse(Entity *mob,  Projectile *bullet)
{
    bullet->Kill();
}
void EnemyProjectileResponse(Enemy *mob,  Projectile *bullet)
{
    mob->Health-= 10;
}


/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                            PLAYER CLASS                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                      
                                                                                                                                                                                                          
========================================================================================================================================================================================
NOTES:    



It is the distant future and a dark energy has fallen across the universe as an evil and powerful creature has emerged. 
It is your job to track down and defeat the evil alien before he finish his retched plan to turn the entire universe into 
Minecraft cubes in one week. 


Hopsila's hell bent on planetary destruction. He hates round objects!
With the help of his minon hord from the Discord Nebula system all hell has broken loose across the Galaxy. 

Only you, the wise, charming... (And good looking), Hero Sedit can save the day and defeat the evil Hopsila !!!
With the help from powerups and weapons donated by the obviously superiour OLC system and their leader Xavid you setout to fullfill your destiny!



because everyone knows they are the most helpful and best star system in all the galaxy!


========================================================================================================================================================================================*/




Player::Player()
{
    Health = 100;
    EnergyLevel = 10000;
    Lives = 3;
    CollisionResponse.SetEnemyResponse      (Default_Response);  
    CollisionResponse.SetPlayerReponse      (Default_Response); 
    CollisionResponse.SetPowerUpReponse     (Default_Response);
    CollisionResponse.SetStaticObjectReponse(Default_Response);
    CollisionResponse.SetProjectileReponse  (EnemyProjectileResponse);
}

// WARNING!!! CLUSTERFUCK AHEAD !!!!!
void Player::Kill()   
{
 // Check how many lives are left, Deduct points and respawn if appropriate
 Lives--;

    if(Lives <= 0)
    {
        FontRender Fonts;
        Fonts.LoadFont("SpaceAge.ttf");
        
        Fonts.Write("GAME OVER MAN!", SCREENWIDTH / 2 - 150, SCREENHEIGHT/ 2);
        SCREEN->SYNC();
        bool A = false;
        while(A != true){SCREEN->Keyboard.KeyState = SDL_GetKeyboardState(NULL); A = SCREEN->Keyboard.KeyState[SDLK_SPACE]; SCREEN->LOOP_GAME();}
    }
    else
    {
        FontRender Fonts;
        Fonts.LoadFont("SpaceAge.ttf");
        
        Fonts.Write("~ Get Ready ~", SCREENWIDTH / 2 - 100, SCREENHEIGHT/ 2);
        SCREEN->SYNC();
        float time = SDL_GetTicks();
        float A =0;
        while(A < 5000){A = SDL_GetTicks() - time;}
    }

    Health = 100;
    Score = 0;
}
void Player::Update() 
{
    Image.Position = CollisionBox->Position;

    EnergyLevel += 1;
    if(EnergyLevel > 100)
    {
        EnergyLevel = 100;
    }

    CollisionBox->Update();

    if(CollisionBox->Body.Position.x < 10) CollisionBox->Body.Position.x = 10;
    if(CollisionBox->Body.Position.x > (SCREENWIDTH - 10)) CollisionBox->Body.Position.x =  (SCREENWIDTH - 10); 
    
    if(CollisionBox->Body.Position.y <  SCREENHEIGHT - 300) CollisionBox->Body.Position.y =  SCREENHEIGHT  - 300;
    if(CollisionBox->Body.Position.y > (SCREENHEIGHT  )) CollisionBox->Body.Position.y =  (SCREENHEIGHT );


    for(auto &other: Enemy::EnemyList)
    {
        if(other.Alive)
        {
            if(CollisionBox->IsCollision(other.CollisionBox) == true)
            {
               Score-= 1;
               Health -= 1;
                Print("Enemy Hit the Player"); // CollisionResponse.EnemyResponse(other);
            }
        }
    }

    if(Health <= 0)
    {
        Kill();
    }
}
void Player::Render()
{
    Image.Render();
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




//========================================================================================================
//______________________________________   POWERUPS   ____________________________________________________
//                                                                                                        
//  Powerups, Buffs and Debuffs. All actions will be determined by the callbacks assigned to the function 
// pointers                                                                                               
//========================================================================================================

Powerups::Powerups()
{
    CollisionResponse.SetEnemyResponse      (Default_Response);  
    CollisionResponse.SetPlayerReponse      (Default_Response); 
    CollisionResponse.SetPowerUpReponse     (Default_Response);
    CollisionResponse.SetStaticObjectReponse(Default_Response);
    CollisionResponse.SetProjectileReponse  (EnemyProjectileResponse);
}

void Powerups::Kill() 
{
    // Remove from the play world and assign the player his buff/Debuff
}
void Powerups::Update() 
{
    Age++;
    Image.Position = CollisionBox->Position;
}
void Powerups::Render()
{
    Image.Render();
}
void Powerups::Response(Entity *other)
{
}



/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                             STATIC OBJECTS                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                      
                                                                                                                                                                                                          
========================================================================================================================================================================================
NOTES:    World Objects, Collidable yet provides little other in the way of other actions 
========================================================================================================================================================================================*/


StaticObject::StaticObject(Vec2  pos, Sprite *img) 
{
    Position = pos;

    CollisionResponse.SetEnemyResponse      (Default_Response);  
    CollisionResponse.SetPlayerReponse      (Default_Response); 
    CollisionResponse.SetPowerUpReponse     (Default_Response);
    CollisionResponse.SetStaticObjectReponse(Default_Response);
    CollisionResponse.SetProjectileReponse  (EnemyProjectileResponse);
}

void StaticObject::Kill()  
{
// Remove from the world if appropriate
}
void StaticObject::Update() 
{

    Image.Position = CollisionBox->Position;
}
void StaticObject::Render() 
{
    Image.Render();
}
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


/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                              Enemy Class                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                      
                                                                                                                                                                                                          
========================================================================================================================================================================================
NOTES:    Enemies, when they collide with the player health is lost and/or points
           When they are killed Points increase           
========================================================================================================================================================================================*/

Enemy Enemy::EnemyList[MAX_PROJECTILES];
int Enemy::NumberOfEnemies = 0;

std::vector<int> 
    Enemy::EnemyValidID;

void BulletHit(Entity *object, Projectile *bullet)
{
}

Enemy::Enemy() 
{
    Health = 100;
    Alive = false;
    Position = Vec2(0,0);
    Image = nullptr;

    ID = 0;
    Age = 0;
}
Enemy::Enemy(Vec2  pos, Vec2 vel, Sprite *img)
{
    Health = 100;
    Alive = true;
    Position = Vec2(0,0);
    Image = *img;
    Age = 0;

    CollisionResponse.SetEnemyResponse      (Default_Response);  
    CollisionResponse.SetPlayerReponse      (Default_Response); 
    CollisionResponse.SetPowerUpReponse     (Default_Response);
    CollisionResponse.SetStaticObjectReponse(Default_Response);
    CollisionResponse.SetProjectileReponse  (EnemyProjectileResponse);
}
void Enemy::Update() 
{
    if(Alive == true)
    {
        Age++;
        CollisionBox->Body.Force = Speed;//Vec2(0,.3);

        CollisionBox->Update();
        Position = CollisionBox->Position;
        Image.Position = Position;
        
        for(auto &other: Projectile::ProjectileList)
        {
            if(other.Alive)
            {
                if(CollisionBox->IsCollision(other.Position) == true)//CollisionBox->IsCollision(other.CollisionBox) == true)
                {
                    Health = Health - 10;
                    
                    Print("Bullet Hit the Enemy"); // CollisionResponse.EnemyResponse(other);
                }
            }
        }
 
       // Position.x > SCREENWIDTH  + SCREEN_BUFFER_AREA || Position.x < -SCREEN_BUFFER_AREA ||
       if( Position.y > SCREENHEIGHT + SCREEN_BUFFER_AREA || Position.y < -SCREEN_BUFFER_AREA )
       {
           Score -= 50;
           Kill();
       }
       if (Health <= 0)
       {
           Score += 50;
           Kill();
       }
    }
}
void Enemy::Render()
{
    Image.Render();
}
void Enemy::Kill()
{
    EnemyValidID.push_back(ID);   
    Alive = false;
}
void Enemy::InitializeEnemies()
{
    EnemyValidID.reserve(MAX_PROJECTILES);
    for_loop(Count, MAX_PROJECTILES)
    {
        EnemyValidID.push_back(MAX_PROJECTILES - (Count + 1));
    }
}
int  Enemy::Spawn(Vec2 pos, Vec2 vel, Sprite *img)
{
    if(EnemyValidID.empty() != true)
    {
        int Index = EnemyValidID.back();
        EnemyList[Index].Alive = true;
        EnemyList[Index].Health = 100;
        EnemyList[Index].Position = pos;
        EnemyList[Index].Image = *img;
        EnemyList[Index].Speed = vel;
        EnemyList[Index].CollisionBox = EnemyList[Index].Image.MakeCollisionBox();
        EnemyList[Index].CollisionBox->Body.Position = pos;
        EnemyList[Index].ID = Index;
        EnemyList[Index].Age = 0;
        EnemyList[Index].CollisionBox->Body.Velocity = Vec2(0,5);
        EnemyValidID.pop_back();
        return Index;
    }
return 0;
}
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




/*========================================================================================================================================================================================
                                                                                                                                                                                      
                                              Projectile Class                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                      
                                                                                                                                                                                      
========================================================================================================================================================================================
NOTES: Mostly Complete:Study this class in the morning and apply it to all other Entity class.Possibly put the Projectiles into an Entity class as well because I need to be able to Spawn....Kill....Collision Checks and Responses
========================================================================================================================================================================================*/

Projectile Projectile::ProjectileList[MAX_PROJECTILES];

int Projectile::NumberOfProjectiles = 0;

std::vector<int> 
    Projectile::ProjectileValidID;



Projectile::Projectile(Vec2 pos, Vec2 vel, Sprite *img)
{
    Position = pos; 
    CollisionBox = img->MakeCollisionBox();
    CollisionBox->Position = pos;
//    CollisionBox->Body.Force = vel;
    Image = *img;
    Alive = false;
}

int  Projectile::Spawn(Vec2 pos, Vec2 vel, Sprite *img)
{
    if(ProjectileValidID.empty() != true)
    {
        int Index = ProjectileValidID.back();
        ProjectileList[Index].Alive = true;
        ProjectileList[Index].Position = pos;
        ProjectileList[Index].Image = *img;
        ProjectileList[Index].Speed = vel;
        ProjectileList[Index].CollisionBox = ProjectileList[Index].Image.MakeCollisionBox();
        ProjectileList[Index].CollisionBox->Body.Position = pos;
        ProjectileList[Index].ID = Index;
        ProjectileList[Index].Age = 0;
        ProjectileList[Index].CollisionBox->Body.Velocity = vel;
        ProjectileValidID.pop_back();
        return Index;
    }
return 0;
}
void Projectile::InitializeProjectiles()
{
    ProjectileValidID.reserve(MAX_PROJECTILES);
    for_loop(Count, MAX_PROJECTILES)
    {
        ProjectileValidID.push_back(MAX_PROJECTILES - (Count + 1));
    }

//Sprite *Bullet = new Sprite(new SpriteSheet("Bullet.bmp"), 1); 
//Bullet->STATE[0] = State(MAKE_Rect(0, 0,8, 8), 3);
//Bullet->Size = Vec2(8);
//
//    ProjectileList.resize(MAX_PROJECTILES);
   // for_loop(Count, MAX_PROJECTILES)
   // {
   //     //ProjectileList.push_back(new Projectile(Vec2(0,0), Vec2(0,0), ));
   //     Projectile::Spawn(Vec2(0,0), Vec2(0,0), Bullet);
   // }
}
void Projectile::Update()
{
    if(Alive)
    {
        Age++; // Increase the age so we can kill it if its getting to old.
        if(Age > 500)
        {
            Kill();
            return;
        }
        
        CollisionBox->Body.Force = Speed; // Apply force so it moves. Tinker with this to get a good speed out of the projectiles
        CollisionBox->Update();
        Position = CollisionBox->Position;// Set the Position of the Bullet to the CollisionBox position
        Image.Position = Position;     // Set the Sprite Image to the Position of the Projectile
    }
}
void Projectile::Render()
{
    Image.Position = CollisionBox->Position;
    Image.Render();
}
void Projectile::Kill()
{
    ProjectileValidID.push_back(ID);   
    Alive = false;
}
void Projectile::Response(Entity *other){}