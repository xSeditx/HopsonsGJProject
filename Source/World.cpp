#include"../Header/World.h"
#include"../Header/Fonts.h"
#include<thread>

bool World::DoneLoading = false;
bool World::KeyHasBeenPressed = false;

SoundEffect *SoundEffect::LaserSound,
            *SoundEffect::PlayerHit;

SoundEffect *SoundEffect::Boom1,  
            *SoundEffect::Boom2,
            *SoundEffect::Boom3,
            *SoundEffect::Boom5,
            *SoundEffect::Boom8;
    
SoundEffect *SoundEffect::LaserHead0006;
                    
SoundEffect *SoundEffect::LaserTail0004,
            *SoundEffect::LaserTail0005;

SoundEffect *SoundEffect::GunFire;

SoundEffect *SoundEffect::Beep01;

SoundEffect *SoundEffect::Extralife;

Music *Music::BackgroundMusic,
      *Music::BackgroundMusic2;

FontRender *FontRender::Fonts;

/*
    Manages all the world object. This is top class, All updates stem from this class and levels are loaded
    and sprites and assets get managed here as every other updates forks from this
*/

void World::Update()
{

    SpawnEnemies();


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

    for(auto &Enemies: Enemy::EnemyList)
    {
        if(Enemies.Alive)
        {
            Enemies.Update();
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

    for(auto &Enemies: Enemy::EnemyList)
    {
        if(Enemies.Alive)
        {
            Enemies.Render();
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
//Player1->CollisionBox = Player1->Picture.MakeCollisionBox();

    Player1->CollisionBox = new AABB(Player1->Position, (( Player1->Picture.Size * .6f) *.5f)) ;
    Entity::PlayerOne = Player1;
//===========================================================================================================================
    Mix_HaltMusic();
    BackgroundMusic = new Music("Assets\\Music.wav", 30);
    BackgroundMusic->Play();
    StartTimer = SDL_GetTicks();
}
void World::Reset()
{

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
                int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH),-10), Vec2(0,2), *Sprite::CthuluEye);
                Enemy::EnemyList[Index].Picture.Angle = 0;
                Enemy::EnemyList[Index].Speed = Vec2(0, .4);
                Enemy::EnemyList[Index].SetSpecialUpdate(DefaultEnemyUpdate);
                Enemy::EnemyList[Index].DamagePoints = 10;
                Enemy::EnemyList[Index].Health = 150;

            }
      }
      if(WorldTimer > (1000 * 60))
      {
            if(((int)WorldTimer % 75) == 0)
            {// Must build up an Enemy preset so I can spawn various entities and have their behavior act correctly
                 int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH/4),-10), Vec2(0,.1), *Sprite::DragonSprite);
                 Enemy::EnemyList[Index].SetSpecialUpdate(DragonUpdate);
                 Enemy::EnemyList[Index].DamagePoints = 15;
                 Enemy::EnemyList[Index].Health = 250;
            }   
      }
      if(WorldTimer > (1000 * 90))
      {
            if(((int)WorldTimer % 100 ) == 0)
            {// Must build up an Enemy preset so I can spawn various entities and have their behavior act correctly~No shit do it already then FFS
                 int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH),-10), Vec2(RANDOM(.8)-.4,5), *Sprite::GreenEye);
                 Enemy::EnemyList[Index].SetSpecialUpdate(DiveBomber);
                 Enemy::EnemyList[Index].DamagePoints = 25;
                 Enemy::EnemyList[Index].Health = 650;
            }    
      
      }
      
      if(((int)WorldTimer %  (5000) ) == 0)
      {// Must build up an Enemy preset so I can spawn various entities and have their behavior act correctly~No shit do it already then FFS
           int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH),-10), Vec2(RANDOM(.8)-.4,1), *Sprite::BossDragon); // 
           Enemy::EnemyList[Index].SetSpecialUpdate(BossDragon);
           Enemy::EnemyList[Index].DamagePoints = 40;
           Enemy::EnemyList[Index].Health = BOSSDRAGON_MAXLIFE;
      }    
}




const char *Line1  =  "In the distant future";    
const char *Line2  =  "A dark energy has fallen";
const char *Line3  =  "across the Universe.";    
const char *Line4  =  "A powerful and evil creature";
const char *Line5  =  "has emerged. It is your job to";//    
const char *Line6  =  "track down and defeat the evil";//
const char *Line7  =  "alien Hopsinoid before he";     //
const char *Line8  =  "finishes his retched plan to";  //
const char *Line9  =  "turn the entire universe into"; //   
const char *Line10 =  "giant Minecraft cubes! ";       //
const char *Line11 =  "You have one week to stop it";  //
const char *Line12 =  "Hopsinoid is hell bent on";     //
const char *Line13 =  "    planetary destruction.";        //
const char *Line14 =  "He hates all round objects!";   //
const char *Line15 =  "With the help of his minon";    //
const char *Line16 =  "hord from the Discord Nebula";  //
const char *Line17 =  "hell has broken loose across "; //   
const char *Line18 =  "          the Galaxy.";           //
const char *Line19 =  "Only you, the wise, charming..";//  
const char *Line20 =  "    (And good looking) ";       //
const char *Line21 =  "Hero Sedit can save the day";// 
const char *Line22 =  "and defeat the evil Hopsinoid!";       //
const char *Line23 =  "With the help of powerups &"; // 
const char *Line24 =  "weapons donated by the great";  //
const char *Line25 =  "OLC starsystem and it's";       // 
const char *Line26 =  "fearless leader Xavid ";        //
const char *Line27 =  "from the J9 Planet you race ";//
const char *Line28 =  "to fullfill your destiny and";  //
const char *Line29 =  "     save the Universe  ";
const char *Line30 =  " ~Good Luck and God speed~";   //     

float SizeofFont = 50;

void World::StartScreen()
{

    float Scroll = 0;
    FontRender StartText("assets\\CalligraphyFLF.ttf",70);


    StartText.SetForgroundColor(0,255,255,255);
    Image BackG = Image("Assets\\TitleScreen.bmp");

    while( SCREEN->LOOP_GAME()) 
    {
        SCREEN->CLS(0);

        BackG.Render(Vec2(0,SCREENHEIGHT- BackG.Size.y - 100), Vec2(SCREENWIDTH, BackG.Size.y));

        StartText.WriteShadow(Line1 , Vec2(15, SCREENHEIGHT - Scroll + SizeofFont      ), 3);
        StartText.WriteShadow(Line2 , Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 2  ), 3);
        StartText.WriteShadow(Line3 , Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 3  ), 3);
        StartText.WriteShadow(Line4 , Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 4  ), 3);
        StartText.WriteShadow(Line5 , Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 5  ), 3);
        StartText.WriteShadow(Line6 , Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 6  ), 3);
        StartText.WriteShadow(Line7 , Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 7  ), 3);
        StartText.WriteShadow(Line8 , Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 8  ), 3);
        StartText.WriteShadow(Line9 , Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 9  ), 3);
        StartText.WriteShadow(Line10 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 10 ), 3);
        StartText.WriteShadow(Line11 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 11 ), 3);
        StartText.WriteShadow(Line12 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 12 ), 3);
        StartText.WriteShadow(Line13 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 13 ), 3);
        StartText.WriteShadow(Line14 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 14 ), 3);                                          
        StartText.WriteShadow(Line15 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 15 ), 3);
        StartText.WriteShadow(Line16 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 16 ), 3);
        StartText.WriteShadow(Line17 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 17 ), 3);
        StartText.WriteShadow(Line18 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 18 ), 3);
        StartText.WriteShadow(Line19 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 19 ), 3);
        StartText.WriteShadow(Line20 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 20 ), 3);
        StartText.WriteShadow(Line21 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 21 ), 3);
        StartText.WriteShadow(Line22 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 22 ), 3);
        StartText.WriteShadow(Line23 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 23 ), 3);
        StartText.WriteShadow(Line24 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 24 ), 3);
        StartText.WriteShadow(Line25 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 25 ), 3);
        StartText.WriteShadow(Line26 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 26 ), 3);            
        StartText.WriteShadow(Line27 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 27 ), 3); 
        StartText.WriteShadow(Line28 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 28 ), 3);
        StartText.WriteShadow(Line29 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 29 ), 3);
        StartText.WriteShadow(Line30 ,Vec2(15, SCREENHEIGHT - Scroll + SizeofFont * 30 ), 3);

        if(World::DoneLoading == true)
        {
            
            FontRender::Fonts->SetForgroundColor(225,0,0,255);
            FontRender::Fonts->WriteShadow("Press Enter", Vec2(177, 30),10);
        }
        else
        {
            FontRender::Fonts->Write("Loading...", Vec2(220, 30));
        }

        SCREEN->SYNC();
        Scroll+= 2.0f;

        if(World::KeyHasBeenPressed == true) // Anything trying to get the Keystates from SDL has failed so far so this is what is getting done fuck it
        {
            break;
        }
    }
}

// RUN THIS AND STARTSCREEN() AT THE SAME TIME INCASE THERE IS A WAIT WHILE LOADING.
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