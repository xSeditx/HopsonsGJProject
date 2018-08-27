#include"Projectiles.h"

/*

Study this class in the morning and apply it to all other Entity class
Possibly put the Projectiles into an Entity class as well because I need to be able to 
Spawn....
Kill....
Collision Checks and Responses


*/

std::vector<Projectile *> Projectile::ProjectileList;
int Projectile::NumberOfProjectiles = 0;
std::vector<int> Projectile::ValidID;


Projectile::Projectile(Vec2 pos, Vec2 vel, Sprite *img)
{
    Alive = false;
}
void Projectile::Update()
{
    Position += Velocity;
    Image->Position.x = Position.x;
    Image->Position.y = Position.y;
    Render();
    Age++;
    if(Age > 500)
    {
        Kill();
    }
}
void Projectile::Render()
{
    Image->Render();
}
void Projectile::Kill()
{
    ValidID.push_back(ID);   
    Alive = false;
}
void Projectile::InitializeProjectiles()
{
    ValidID.reserve(MAX_PROJECTILES);
    for_loop(Count, MAX_PROJECTILES)
    {
        ValidID.push_back(MAX_PROJECTILES - (Count + 1));
    }


    ProjectileList.reserve(MAX_PROJECTILES);
    for_loop(Count, MAX_PROJECTILES)
    {
        ProjectileList.push_back(new Projectile(Vec2(0,0), Vec2(0,0), nullptr));
    }
}
void Projectile::UpdateAll()
{
    for(auto &P: ProjectileList)
    {
        if(P->Alive == true)
        {
            P->Update();
            P->CheckCollisions();
            P->Render();
        }
    }
}
void Projectile::CheckCollisions()
{
    for(auto& P: Collider::CollisionList)
    {
        if(P->ID != 0)
        {
            if(P->IsCollision(Position))
            {
                Print("Bullet Hit");
            }
        }
    }
}



int Projectile::Create(Vec2 pos, Vec2 vel, Sprite *img)
{
    if(ValidID.empty() != true)
    {
        int Index = ValidID.back();
        ProjectileList[Index]->Alive = true;
        ProjectileList[Index]->Position = pos;
        ProjectileList[Index]->Velocity = vel;
        ProjectileList[Index]->Image = img;
        ProjectileList[Index]->ID = Index;
        ProjectileList[Index]->Age = 0;
        ValidID.pop_back();
        return Index;
    }
return 0;
}