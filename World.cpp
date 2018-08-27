#include"World.h"

/*
Manages all the world object. This is top class, All updates stem from this class and levels are loaded
and sprites and assets get managed here as every other updates forks from this

*/


World::World(VideoCamera *cam, Player *p1)
{
    Camera = cam;
    Player1 = p1;
}
Level::Level()
{
    Difficulty = 1;
}
void Level::AddSprite(Sprite *object)
{
    SpriteList.push_back(object);
}
void Level::AddEnemy(Sprite *object)
{
    EnemyList.push_back(object);
}
void Level::AddProjectile(Projectile *object)
{
    ProjectileList.push_back(object);
}
void Level::Update()
{
    for(auto &C: Collider::CollisionList)
    {
        C->Update();
    }
    for(auto &WorldObject: SpriteList)
    {
        WorldObject->Update();
    }
    for(auto &Enemies: EnemyList)
    {
        Enemies->Update();
    }

    Collision::Resolve();
    Player1->Update();
}
void Level::Render()
{
    for(auto &WorldObject: SpriteList)
    {
        WorldObject->Render();
    }
    for(auto &Enemies: EnemyList)
    {
        Enemies->Render();
    }
    Player1->Render();
}
void Level::Load()
{
    
    Camera = new VideoCamera(Vec2(0,0),Vec2(SCREENWIDTH*.5, SCREENHEIGHT *.5));;


    Player1 = new Player;
    Player1->Position = Vec2(200,200);
    Player1->Image = new Sprite(new SpriteSheet("Ship.bmp"), 1);
    Player1->Image->Size = Vec2(160 * .5);
    Player1->Image->STATE[0] = State(MAKE_Rect(0, 0,160, 160), 4);
    Player1->Image->ANIMATED = true;
    Player1->Image->AnimationSpeed = 50;
    Player1->CollisionBox = Player1->Image->MakeCollisionBox();


    Sprite *Bullet = new Sprite(new SpriteSheet("Bullet.bmp"), 1); 
    Bullet->Size = Vec2(8);
    Bullet->Position = Vec2(SCREENWIDTH/2, SCREENHEIGHT/2);
    Bullet->STATE[0] = State(MAKE_Rect(0, 0,8, 8), 3);
    Bullet->ANIMATED = true;
    Bullet->AnimationSpeed = 50;
    Bullet->MakeCollisionBox();
    AddSprite(Bullet);


    Projectile::InitializeProjectiles();


    Sprite *Energy =  new Sprite(new SpriteSheet("EnergySpheres.bmp"), 1); 
    Energy->SetPosition(Vec2(100,100));
    Energy->Size = Vec2(84);

    Energy->STATE[0] =   State(MAKE_Rect(0, 0,84, 84), 7);
    Energy->STATE[0] +=  State(MAKE_Rect(0, 84, 84, 84), 7);
    Energy->STATE[0] +=  State(MAKE_Rect(0, 168, 84, 84), 7);
    Energy->STATE[0] +=  State(MAKE_Rect(0, 252, 84, 84), 7);
    Energy->STATE[0] +=  State(MAKE_Rect(0, 336, 84, 84), 7);
    Energy->STATE[0] +=  State(MAKE_Rect(0, 420, 84, 84), 7);
    Energy->STATE[0] +=  State(MAKE_Rect(0, 504, 84, 84), 7);
    Energy->ANIMATED = true;
    Energy->AnimationSpeed = 50;
    Energy->MakeCollisionBox();
    AddSprite(Energy);





    Sprite *Eye = new Sprite( new SpriteSheet("eye.bmp"), 1); 
    Eye->SetPosition(Vec2(300,100));
    Eye->Size = Vec2(42);
    Eye->STATE[0] = State(MAKE_Rect(0, 0,42, 42), 3);
    Eye->ANIMATED = true;
    Eye->AnimationSpeed = 100;
    Eye->MakeCollisionBox();
    AddEnemy(Eye);


}
