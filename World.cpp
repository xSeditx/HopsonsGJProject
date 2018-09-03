#include"World.h"

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

Music *Music::BackgroundMusic,
      *Music::BackgroundMusic2;

FontRender *FontRender::Fonts;

//TODO: Place the Spawn Enemies into its own section. Give each enemy a spawn rate that is a Probability of them spawning. 
//     Do a complete overhaul on the spawning system as it appears right now that as I use the Presets for the Entities
//     they will all point to the same object which is a huge fucking problem
// STARTED:
// COMPLETED:


/*
    Manages all the world object. This is top class, All updates stem from this class and levels are loaded
    and sprites and assets get managed here as every other updates forks from this
*/

void World::Update()
{
    WorldTimer = SDL_GetTicks();
//______________________________________________________________________________________________________________________________________
//============================================= Spawns the Enemies =====================================================================
//==========================================_________________________===================================================================
         
        if(((int)WorldTimer %100) == 0)
        {
            int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH),-10), Vec2(0,2), Sprite::CthuluEye);
            Enemy::EnemyList[Index].Picture.Angle = 0;//RANDOM(10);
            Enemy::EnemyList[Index].Speed = Vec2(0, .4);
            Enemy::EnemyList[Index].SetSpecialUpdate(DefaultEnemyUpdate);
        }
         if(((int)WorldTimer %100) == 0)
        {// Must build up an Enemy preset so I can spawn various entities and have their behavior act correctly
             int Index = Enemy::Spawn(Vec2(RANDOM(SCREENWIDTH/4),-10), Vec2(0,.1), Sprite::DragonSprite);
            // Enemy::EnemyList[Index].Picture.Angle = 0;//RANDOM(10);
             //Enemy::EnemyList[Index].Speed = Vec2(RANDOM(.4) - .2, .4);
             Enemy::EnemyList[Index].SetSpecialUpdate(DragonUpdate);
        }   

    
//======================================================================================================================================
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

    StarBackground->ForwardThrust = -Player1->CollisionBox->Body.Velocity.y + 10;
    StarBackground->Update();


    Player1->Update();
    HeadsUp->Update(Player1->Health, Player1->EnergyLevel, Player1->Lives);
}
void World::Render()
{

    StarBackground->Render();
     HeadsUp->Render();

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

    for(auto &StaticOBJ: StaticObject::StaticObjectList)
    {
        if(StaticOBJ.Alive)
        {
            StaticOBJ.Render();
        }
    }

    Player1->Render();

}
void World::Load()
{
    HeadsUp =  new HUD();
    StarBackground =  new StarField();

    SoundEffect::InitializeSound();
    Music::InitializeMusic();

    SpriteSheet::Initialize();
    Sprite::Initialize();

    Entity::Initialize();
    Enemy::Initialize();
    Projectile::Initialize();
    EnemyProjectile::Initialize();
    StaticObject::Initialize();
//___________________________________________________________________________________________________________________________
//==========================================  PLAYER INIT  ==================================================================
    Player1 = new Player();
    Player1->Position = Vec2(SCREENWIDTH *.5,SCREENHEIGHT -100);

    Player1->Picture = Sprite(SpriteSheet::Ship, 1);
    Player1->Picture.Size = Vec2(160 * .6);
    Player1->Picture.STATE[0] = State(MAKE_Rect(0, 0,160, 160), 4);
    Player1->Picture.ANIMATED = true;
    Player1->Picture.AnimationSpeed = 50;
    Player1->CollisionBox = Player1->Picture.MakeCollisionBox();
    Entity::PlayerOne = Player1;
//===========================================================================================================================


    BackgroundMusic = new Music("Assets\\Music.wav", 30);
    FontRender::Fonts = new FontRender("Assets\\SpaceAge.ttf");
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
}


const char *Line1  =  "It is the distant future and";    
const char *Line2  =  "a dark energy has ";
const char *Line3  =  "fallen across the universe.";    
const char *Line4  =  "An evil and powerful ";
const char *Line5  =  "creature has emerged. It is" ;    
const char *Line6  =  "your job to track down";
const char *Line7  =  "and defeat the evil alien ";    
const char *Line8  =  "before he finish his";
const char *Line9  =  "retched plan to turn the ";    
const char *Line10 =  "entire universe into";
const char *Line11 =  "Minecraft cubes in one week";  
const char *Line12 =  "Hopsilas hell bent on";
const char *Line13 =  "planetary destruction.";       
const char *Line14 =  "He hates round objects!";
const char *Line15 =  "With the help of his minon";   
const char *Line16 =  "hord from the Discord ";
const char *Line17 =  "Nebula all hell has broken";    
const char *Line18 =  "loose across the Galaxy.";
const char *Line19 =  "Only you, the wise, charming..."; 
const char *Line20 =  "(And good looking),";
const char *Line21 =  "Hero Sedit can save the day";    
const char *Line22 =  "and defeat Hopsila !!!";
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
    float Timer = 0, Timer_Escape = 0;
    float CurrentTime = SDL_GetTicks();
        float Scroll = 0;
    while(Timer_Escape < 50000)
    {

        SCREEN->LOOP_GAME();
        SCREEN->CLS();
            Timer = SDL_GetTicks();

            FontRender::Fonts->Write(Line1 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont ));
            FontRender::Fonts->Write(Line2 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 2 ));
            FontRender::Fonts->Write(Line3 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 3  ));
            FontRender::Fonts->Write(Line4 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 4  ));
            FontRender::Fonts->Write(Line5 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 5  ));
            FontRender::Fonts->Write(Line6 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 6  ));
            FontRender::Fonts->Write(Line7 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 7  ));
            FontRender::Fonts->Write(Line8 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 8  ));
            FontRender::Fonts->Write(Line9 , Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 9  ));
            FontRender::Fonts->Write(Line10 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 10  ));
            FontRender::Fonts->Write(Line11 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 11  ));
            FontRender::Fonts->Write(Line12 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 12  ));
            FontRender::Fonts->Write(Line13 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 13  ));
            FontRender::Fonts->Write(Line14 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 14  ));
            FontRender::Fonts->Write(Line15 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 15  ));  
                                                                  
            FontRender::Fonts->Write(Line15 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 15  ));
            FontRender::Fonts->Write(Line16 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 16  ));
            FontRender::Fonts->Write(Line17 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 17  ));
            FontRender::Fonts->Write(Line18 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 18  ));
            FontRender::Fonts->Write(Line19 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 19 ));
            FontRender::Fonts->Write(Line20 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 20 ));
            FontRender::Fonts->Write(Line21 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 21 ));
            FontRender::Fonts->Write(Line22 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 22  ));
            FontRender::Fonts->Write(Line23 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 23  ));
            FontRender::Fonts->Write(Line24 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 24  ));
            FontRender::Fonts->Write(Line25 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 25  ));
            FontRender::Fonts->Write(Line26 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 26  ));            
            FontRender::Fonts->Write(Line27 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 27  )); 
            FontRender::Fonts->Write(Line28 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 28  ));
            FontRender::Fonts->Write(Line29 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 29 ));
            FontRender::Fonts->Write(Line30 ,Vec2(17, SCREENHEIGHT - Scroll + SizeofFont * 30  ));


            SCREEN->SYNC();
        Timer_Escape = Timer - CurrentTime;
        Scroll+= 0.7f;


        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDLK_RETURN])
        {
            break;
        }
    }
}
