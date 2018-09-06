#include"World.h"
#include<thread>

bool World::DoneLoading = false;
bool World::KeyHasBeenPressed = false;



 SoundEffect *SoundEffect::LaserSound,
             *SoundEffect::PlayerHit;

 SoundEffect *SoundEffect::Boom1,
             *SoundEffect::Boom2,
             *SoundEffect::Boom3,
             *SoundEffect::Boom4,
             *SoundEffect::Boom5,
             *SoundEffect::Boom6,
             *SoundEffect::Boom7,
             *SoundEffect::Boom8,
             *SoundEffect::Boom9;

 SoundEffect *SoundEffect::LaserHead0001,
             *SoundEffect::LaserHead0002,
             *SoundEffect::LaserHead0003,
             *SoundEffect::LaserHead0004,
             *SoundEffect::LaserHead0005,
             *SoundEffect::LaserHead0006,
             *SoundEffect::LaserHead0007,
             *SoundEffect::LaserHead0008,
             *SoundEffect::LaserHead0000;
                      
SoundEffect  *SoundEffect::LaserTail0001,
             *SoundEffect::LaserTail0002,
             *SoundEffect::LaserTail0003,
             *SoundEffect::LaserTail0004,
             *SoundEffect::LaserTail0005,
             *SoundEffect::LaserTail0006,
             *SoundEffect::LaserTail0007,
             *SoundEffect::LaserTail0008,
             *SoundEffect::LaserTail0000;
                         
SoundEffect  *SoundEffect::LaserBody0001,
             *SoundEffect::LaserBody0002,
             *SoundEffect::LaserBody0003,
             *SoundEffect::LaserBody0004,
             *SoundEffect::LaserBody0005,
             *SoundEffect::LaserBody0006,
             *SoundEffect::LaserBody0007,
             *SoundEffect::LaserBody0008,
             *SoundEffect::LaserBody0000;

 SoundEffect *SoundEffect::GunFire;  


SoundEffect *SoundEffect::Beep01;

Music *Music::BackgroundMusic,
      *Music::BackgroundMusic2;

FontRender *FontRender::Fonts;

/*
    Manages all the world object. This is top class, All updates stem from this class and levels are loaded
    and sprites and assets get managed here as every other updates forks from this
*/
#include"Fonts.h"
void World::Update()
{

    SpawnEnemies();

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
    for(auto &Bullet: EnemyProjectile::EnemyProjectileList)
    {
        if(Bullet.Alive)
        {
            Bullet.Update();
        }
    }

    for(auto &StaticOBJ: StaticObject::StaticObjectList)
    {
        if(StaticOBJ.Alive)
        {
            StaticOBJ.Update();
        }
    }
    for(auto &Power: Powerup::PowerupList)
    {
        if(Power.Alive)
        {
            Power.Update();
        }
    }
    StarBackground->ForwardThrust = -Player1->CollisionBox->Body.Velocity.y + 10;
    StarBackground->Update();


    Player1->Update();
    HeadsUp->Update(Player1->Health, Player1->EnergyLevel, Player1->Lives);
}
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
    for(auto &Bullet: EnemyProjectile::EnemyProjectileList)
    {
        if(Bullet.Alive)
        {
            Bullet.Render();
        }
    }
    for(auto &Power: Powerup::PowerupList)
    {
        if(Power.Alive)
        {
            Power.Render();
        }
    }

    Player1->Render();

    for(auto &StaticOBJ: StaticObject::StaticObjectList)
    {
        if(StaticOBJ.Alive)
        {
            StaticOBJ.Render();
        }
    }
     HeadsUp->Render();
}
void World::Load()
{
    HeadsUp =  new HUD();
    StarBackground =  new StarField();

    DoneLoading = false;
    Music LoadingMusic("Assets\\Mayhem.wav",30);
    LoadingMusic.Play();
    std::thread *Init = new std::thread(THREAD_InitializeAll);
    
    World::StartScreen();
    Init->join();
 

//___________________________________________________________________________________________________________________________
//==========================================  PLAYER INIT  ==================================================================
    Player1 = new Player();
    Player1->Position = Vec2(SCREENWIDTH *.5,SCREENHEIGHT - 100);

    Player1->Picture = Sprite(SpriteSheet::Ship, 4);
    Player1->Picture.Size = Vec2(160 * .6);
    Player1->Picture.STATE[0] = State(MAKE_Rect(0, 0,160, 160), 4);
    Player1->Picture.STATE[1] = State(MAKE_Rect(0, 160,160, 160), 4);
    Player1->Picture.STATE[2] = State(MAKE_Rect(0, 320,160, 160), 4);
    Player1->Picture.STATE[3] = State(MAKE_Rect(0, 480,160, 160), 4);

    Player1->Picture.ANIMATED = true;
    Player1->Picture.AnimationSpeed = 50;
    Player1->CollisionBox = Player1->Picture.MakeCollisionBox();
    Entity::PlayerOne = Player1;
//===========================================================================================================================
    Mix_HaltMusic();
    BackgroundMusic = new Music("Assets\\Music.wav", 30);
    BackgroundMusic->Play();
    StartTimer = SDL_GetTicks();
}
void World::Reset()
{
   // Player1->Position = Vec2(SCREENWIDTH *.5,SCREENHEIGHT -100);
    for(auto &P : Projectile::ProjectileList)
    {
        P.Alive= false;
    }
    for(auto &E : Enemy::EnemyList)
    {
        E.Alive= false;
    }

    for(auto &EP: EnemyProjectile::EnemyProjectileList)
    {
        EP.Alive= false;
    }
    Enemy::EnemyValidID.clear();
    EnemyProjectile::ProjectileValidID.clear();
    Projectile::ProjectileValidID.clear();

    Enemy::Initialize();
    EnemyProjectile::Initialize();
    Projectile::Initialize();
}
void World::PauseGame()
{
  SDL_SetRelativeMouseMode(SDL_FALSE);
    while(SCREEN->LOOP_GAME())
    {
        SCREEN->CLS();
        FontRender::Fonts->Write("PAUSED", Vec2(((SCREENWIDTH *.5) -(6*14)), (SCREENHEIGHT *.5)));
        if(SCREEN->Keyboard.Key.ScanCode == SDL_SCANCODE_RETURN)
        {
            break;
        }
        SCREEN->SYNC();
    }
  SDL_SetRelativeMouseMode(SDL_TRUE);
}
void World::SpawnEnemies()
{
    WorldTimer = SDL_GetTicks() - StartTimer;
 
//______________________________________________________________________________________________________________________________________
//============================================= Spawns the Enemies =====================================================================
//==========================================_________________________===================================================================
  if(WorldTimer > (1000 * 5))
  {
        if(((int)WorldTimer % 50) == 0)
        {
            int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH),-10), Vec2(0,2), Sprite::CthuluEye);
            Enemy::EnemyList[Index].Picture.Angle = 0;
            Enemy::EnemyList[Index].Speed = Vec2(0, .4);
            Enemy::EnemyList[Index].SetSpecialUpdate(DefaultEnemyUpdate);
        }
  }
  if(WorldTimer > (1000 * 60))
  {
        if(((int)WorldTimer % 75) == 0)
        {// Must build up an Enemy preset so I can spawn various entities and have their behavior act correctly
             int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH/4),-10), Vec2(0,.1), Sprite::DragonSprite);
             Enemy::EnemyList[Index].SetSpecialUpdate(DragonUpdate);
        }   
  }
  if(WorldTimer > (1000 * 90))
  {
        if(((int)WorldTimer % 100 ) == 0)
        {// Must build up an Enemy preset so I can spawn various entities and have their behavior act correctly~No shit do it already then FFS
             int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH),-10), Vec2(RANDOM(.8)-.4,.1), Sprite::GreenEye);
             Enemy::EnemyList[Index].SetSpecialUpdate(DiveBomber);
        }    
  }


if(((int)WorldTimer % 100 ) == 0)
{// Must build up an Enemy preset so I can spawn various entities and have their behavior act correctly~No shit do it already then FFS
     int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH),-10), Vec2(RANDOM(.8)-.4,.1), Sprite::BossDragon);
     Enemy::EnemyList[Index].SetSpecialUpdate(DragonUpdate);
}    
//======================================================================================================================================

}










const char *Line1  =  "In the distant future A";    
const char *Line2  =  "dark energy has fallen";
const char *Line3  =  "across the universe.";    
const char *Line4  =  "An evil and powerful ";
const char *Line5  =  "creature has emerged. It is" ;    
const char *Line6  =  "your job to track down";
const char *Line7  =  "and defeat the evil alien  ";    
const char *Line8  =  "Hopsinoid before he finish ";
const char *Line9  =  "his retched plan to turn the ";    
const char *Line10 =  "entire universe into giant";
const char *Line11 =  "Minecraft cubes in one week";  
const char *Line12 =  "Hopsinoid is hell bent on";
const char *Line13 =  "planetary destruction.";       
const char *Line14 =  "He hates round objects!";
const char *Line15 =  "With the help of his minon";   
const char *Line16 =  "hord from the Discord ";
const char *Line17 =  "Nebula all hell has broken";    
const char *Line18 =  "loose across the Galaxy.";
const char *Line19 =  "Only you, the wise, charming..."; 
const char *Line20 =  "       (And good looking),";
const char *Line21 =  "Hero Sedit can save the day";    
const char *Line22 =  "and defeat Hopsinoid !!!";
const char *Line23 =  "With the help from powerups";    
const char *Line24 =  "and weapons donated by the";
const char *Line25 =  "obviously superiour OLC  ";      
const char *Line26 =  "system and the fearless ";
const char *Line27 =  "leader Xavid from the X9 ";
const char *Line28 =  "Planet you setout to";
const char *Line29 =  "fullfill your destiny!";        
const char *Line30 =  "Good Luck and God speed!";           

float SizeofFont = 24;

void World::StartScreen()
{

        float Scroll = 0;

Image BackG = Image("Assets\\TitleScreen.bmp");

    while( SCREEN->LOOP_GAME())//) Timer_Escape < 50000)
    {
        SCREEN->CLS(0);

        BackG.Render(Vec2(0,SCREENHEIGHT- BackG.Size.y - 100), Vec2(SCREENWIDTH, BackG.Size.y));

        FontRender::Fonts->Write(Line1 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont      ));
        FontRender::Fonts->Write(Line2 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 2  ));
        FontRender::Fonts->Write(Line3 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 3  ));
        FontRender::Fonts->Write(Line4 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 4  ));
        FontRender::Fonts->Write(Line5 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 5  ));
        FontRender::Fonts->Write(Line6 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 6  ));
        FontRender::Fonts->Write(Line7 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 7  ));
        FontRender::Fonts->Write(Line8 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 8  ));
        FontRender::Fonts->Write(Line9 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 9  ));
        FontRender::Fonts->Write(Line10 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 10 ));
        FontRender::Fonts->Write(Line11 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 11 ));
        FontRender::Fonts->Write(Line12 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 12 ));
        FontRender::Fonts->Write(Line13 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 13 ));
        FontRender::Fonts->Write(Line14 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 14 ));                                          
        FontRender::Fonts->Write(Line15 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 15 ));
        FontRender::Fonts->Write(Line16 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 16 ));
        FontRender::Fonts->Write(Line17 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 17 ));
        FontRender::Fonts->Write(Line18 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 18 ));
        FontRender::Fonts->Write(Line19 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 19 ));
        FontRender::Fonts->Write(Line20 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 20 ));
        FontRender::Fonts->Write(Line21 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 21 ));
        FontRender::Fonts->Write(Line22 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 22 ));
        FontRender::Fonts->Write(Line23 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 23 ));
        FontRender::Fonts->Write(Line24 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 24 ));
        FontRender::Fonts->Write(Line25 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 25 ));
        FontRender::Fonts->Write(Line26 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 26 ));            
        FontRender::Fonts->Write(Line27 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 27 )); 
        FontRender::Fonts->Write(Line28 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 28 ));
        FontRender::Fonts->Write(Line29 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 29 ));
        FontRender::Fonts->Write(Line30 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 30 ));

          // FontRender::Fonts->Write("Press Any Key", Vec2(17, 30));

        if(World::DoneLoading == true)
        {
            FontRender::Fonts->Write("Press Any Key", Vec2(157, 30));
        }
        else
        {
            FontRender::Fonts->Write("Loading...", Vec2(220, 30));
        }

        SCREEN->SYNC();
        Scroll+= 0.7f;

        if(World::KeyHasBeenPressed == true) // Anything trying to get the Keystates from SDL has failed so far so this is what is getting done fuck it
        {
            break;
        }
    }
}



void World::THREAD_InitializeAll()
{
    SoundEffect::InitializeSound();
    Music::InitializeMusic();

    SpriteSheet::Initialize();
    Sprite::Initialize();

    Entity::Initialize();
    Enemy::Initialize();
    Projectile::Initialize();
    EnemyProjectile::Initialize();
    StaticObject::Initialize();
    Powerup::Initialize();

    World::DoneLoading = true;
}