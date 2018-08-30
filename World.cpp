#include"World.h"

/*
Manages all the world object. This is top class, All updates stem from this class and levels are loaded
and sprites and assets get managed here as every other updates forks from this

*/


World::World(VideoCamera *cam)
{
    Camera = cam;
    Player1 = nullptr;
    Difficulty = 1;
    SpriteSheets = new SpriteSheet();
    SpriteSheets->LoadAssets();
    Load();

    SpriteSheets = new SpriteSheet();
    SpriteSheets->LoadAssets();
    WorldTimer = SDL_GetTicks();
}

//======================================================================================================================

void World::Update()
{

    WorldTimer = SDL_GetTicks();
    if(((int)WorldTimer %100) == 0)
    {
        int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH),0), Vec2(0,3), EyeBallEnemySprite);
        Enemy::EnemyList[Index].Image.Angle = 0;//RANDOM(10);
        Enemy::EnemyList[Index].Speed = Vec2(0, .4);
    }
    

    for(auto &Enemies: Enemy::EnemyList)
    {
        if(Enemies.Alive)
        {
            Enemies.Update();
        }
    }

    for(auto &Bullet: Projectile::ProjectileList)
    {
        if(Bullet.Alive)
        {
            Bullet.Update();
        }
    }

    StarBackground->ForwardThrust = -Player1->CollisionBox->Body.Velocity.y + 10;
    StarBackground->Update();
    Player1->Update();
    HeadsUp->Update(Player1->Health, Player1->EnergyLevel, Player1->Lives);
}

//======================================================================================================================

void World::Render()
{
    StarBackground->Render();

    for(auto &Enemies: Enemy::EnemyList)
    {
        if(Enemies.Alive)
        {
            Enemies.Render();
        }
    }


    for(auto &Bullet: Projectile::ProjectileList)
    {
        if(Bullet.Alive)
        {
            Bullet.Render();
        }
    }

    Player1->Render();
    HeadsUp->Render();
}

//======================================================================================================================

void World::Load()
{
    HeadsUp =  new HUD();
    Enemy::InitializeEnemies();
    Projectile::InitializeProjectiles();
    Enemy::InitializeEnemies();

    Player1 = new Player;
    Player1->Position = Vec2(SCREENWIDTH *.5,SCREENHEIGHT -100);

    Player1->Image = Sprite(SpriteSheets->Ship, 1);

    Player1->Image.Size = Vec2(160 * .6);
    Player1->Image.STATE[0] = State(MAKE_Rect(0, 0,160, 160), 4);
    Player1->Image.ANIMATED = true;
    Player1->Image.AnimationSpeed = 50;
    Player1->CollisionBox = Player1->Image.MakeCollisionBox();


    EyeBallEnemySprite = new Sprite(SpriteSheets->Eye,1);
    EyeBallEnemySprite->Size = Vec2(42);
    EyeBallEnemySprite->STATE[0] = State(MAKE_Rect(0, 0,42, 42), 3);
    EyeBallEnemySprite->ANIMATED = true;
    EyeBallEnemySprite->AnimationSpeed = 100;

    StarBackground =  new StarField();
}
