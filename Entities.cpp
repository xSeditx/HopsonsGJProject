#include"Entities.h"

/*
                                                                                                                   
                                       ENTITY CLASS:
                               ____________________________
                     MANAGES THE PLAYER, ENEMIES AND STATIC WORLD OBJECTS.                                                                                               
                     POSSIBLY ADD THE PROJECTILES INTO THIS IN THE FUTURE.                                                                                               

    8/27/2018 
*/

//========================================================================================================
//______________________________________   PLAYER CLASS  _________________________________________________
//========================================================================================================



Player::Player()
{
    Health = 100;
}
void Player::Spawn()
{
}
void Player::Kill()   
{
 // Check how many lives are left, Deduct points and respawn if appropriate
}
void Player::Update() 
{
    Image->Position = CollisionBox->Position;
}
void Player::Render()
{
    Image->Render();
}

//========================================================================================================
//______________________________________   ENEMY CLASS   _________________________________________________
//                                                                                                        
//  Enemies, when they collide with the player health is lost and/or points
//  When they are killed Points increase                                                                  
//========================================================================================================
Enemy::Enemy() 
{
    Health = 100;
}
void Enemy::Spawn()  {}
void Enemy::Kill()   
{
    // Increase players points
}
void Enemy::Update() 
{
    Image->Position = CollisionBox->Position;
}
void Enemy::Render()
{
    Image->Render();
}


//========================================================================================================
//______________________________________   POWERUPS   ____________________________________________________
//                                                                                                        
//  Powerups, Buffs and Debuffs. All actions will be determined by the callbacks assigned to the function 
// pointers                                                                                               
//========================================================================================================



Powerups::Powerups()
{
}
void Powerups::Spawn()  {}
void Powerups::Kill() 
{
    // Remove from the play world and assign the player his buff/Debuff
}
void Powerups::Update() 
{
    Image->Position = CollisionBox->Position;
}
void Powerups::Render()
{
    Image->Render();
}


//========================================================================================================
//_________________________________________ STATIC OBJECTS _______________________________________________
//                                                                                                        
//    World Objects, Collidable yet provides little other in the way of other actions                                                 
//========================================================================================================


StaticObject::StaticObject() 
{
}
void StaticObject::Spawn()  {}
void StaticObject::Kill()  
{
// Remove from the world if appropriate
}
void StaticObject::Update() 
{
    Image->Position = CollisionBox->Position;
}
void StaticObject::Render() 
{
    Image->Render();
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
void Powerups::Response(Entity *other)
{
}


