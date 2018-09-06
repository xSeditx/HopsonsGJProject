#include"window.h"
#include"Sprite.h"
#include"World.h"
#include"Camera.h"
#include"Fonts.h"
#include"Sound.h"
#include<string>


#define SHIP_HEIGHT 64
#define SHIP_WIDTH  64



SpriteSheet *SpriteSheets;

Sprite *Bullet;
Sprite *Plasma;
World  *GameWorld;

float ShipSpeed = 25;
 

float FireTimer = 0;
float FireRate = 50;
bool IsLMouseButtonDown = false;
bool IsRMouseButtonDown = false;



void KeyDown(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier, Uint8 rep) 
{
    if(SCREEN->Keyboard.KeyState[SDL_SCANCODE_ESCAPE] == true)
    {
        World::PauseGame();
    }
}
void KeyUp(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier )
{
}
void MouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
  GameWorld->Player1->CollisionBox->Body.Velocity.x += (relX * .03);
  GameWorld->Player1->CollisionBox->Body.Velocity.y += (relY * .03);

  Entity::PlayerOne->Picture.CURRENT_STATE = 0;

  if(relX > 3)
  {
      Entity::PlayerOne->Picture.CURRENT_STATE = 3;
  }
  else if(relX < -3)
  {
      Entity::PlayerOne->Picture.CURRENT_STATE = 2;
  }


Print(relX);
}

void MouseLClick(int mX, int mY)
{
    if(Entity::PlayerOne->EnergyLevel > 0)
    {
       // Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x - 20, GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -3), Bullet);
      //  Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x + 15, GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -3), Bullet);
      //  Entity::PlayerOne->EnergyLevel -= 1;
        IsLMouseButtonDown = true;
    }
}
void MouseRClick(int mX, int mY)
{
    if(GameWorld->Player1->EnergyLevel > 0)
    {
//        Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x , GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -.2), Plasma );
//        SoundEffect::Boom1->Play();
//        GameWorld->Player1->EnergyLevel -= 500;
        IsRMouseButtonDown = true;
    }
}

void MouseLRelease(int x, int y)
{
        IsLMouseButtonDown = false;
}
void MouseRRelease(int x, int y)
{
        IsRMouseButtonDown = false;
}


void InitKeyPress(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier, Uint8 rep) 
{
    World::KeyHasBeenPressed = true;
}


#include<thread>

void main()
{
    Window MainWin(0,0,SCREENWIDTH,SCREENHEIGHT,"Hopsons Game Jam");
           MainWin.Set_Sync_rate(60);
           MainWin.CallBacks.SetOnKeyDown(InitKeyPress);           
   
    FontRender::Fonts = new FontRender("Assets\\SpaceAge.ttf");

    GameWorld = new World();  //     This is where it starts.

           MainWin.CallBacks.SetOnKeyDown(KeyDown);
           MainWin.CallBacks.SetOnKeyUp(KeyUp);
           MainWin.CallBacks.SetOnMouseMove(MouseMove);
           MainWin.CallBacks.SetOnLButtonDown(MouseLClick);
           MainWin.CallBacks.SetOnRButtonDown(MouseRClick);

           MainWin.CallBacks.SetOnLButtonUp(MouseLRelease);
           MainWin.CallBacks.SetOnRButtonUp(MouseRRelease);
  

    SDL_SetRelativeMouseMode(SDL_TRUE);


//    const char* SayScore = "SCORE: ";


    while(MainWin.LOOP_GAME())
    {
//=======================================================================================================================================================================        
//_____________________________________________________  KEYBOARD STUFF  ___________________________________________________________________________________________________
//________________________________________________________________________________________________________________________________________________________________________

        if((SDL_GetTicks() - FireTimer) > FireRate)
        {
            if(GameWorld->Player1->EnergyLevel > 0 )
            {
                if(IsLMouseButtonDown == true)
                {
                    Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x - 20, GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -3), Sprite::Bullet);
                    Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x + 15, GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -3), Sprite::Bullet);
                    Entity::PlayerOne->EnergyLevel -= 9;
                     SoundEffect::LaserTail0005->Play(); // 6 8
                     SoundEffect::LaserHead0006->Play();
                    //SoundEffect::GunFire->Play();
                   // SoundEffect::LaserTail0001->Play();
                    
                    FireTimer = SDL_GetTicks();
                }
               //if(GameWorld->Player1->EnergyLevel > 50)
               //{
               //    if(IsRMouseButtonDown == true)
               //    {
               //       // Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x , GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -.2), Sprite::FireOrb );
               //        int Index = Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x , GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -4), Sprite::BigGun );
               //      Projectile::ProjectileList[Index].BulletPower = 9999;
               //        
               //        SoundEffect::Boom1->Play();
               //    
               //        GameWorld->Player1->EnergyLevel -= 25;
               //        FireTimer = SDL_GetTicks();
               //    }
               //}
            }  //

            else
            {
                FireRate = 500;
            }

            if(GameWorld->Player1->EnergyLevel >= 99)
            {
                FireRate = 50;
            }

        }


        if((SDL_GetTicks() - FireTimer) > (FireRate * 4))
        {
            if(GameWorld->Player1->EnergyLevel > 0 )
            {
               // if(GameWorld->Player1->EnergyLevel > 99)
               // {
                    if(IsRMouseButtonDown == true)
                    {
                       // Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x , GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -.2), Sprite::FireOrb );
                        int Index = Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x , GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -4), Sprite::BigGun );
                      Projectile::ProjectileList[Index].BulletPower = 9999;
                        
                        SoundEffect::Boom1->Play();
                    
                        GameWorld->Player1->EnergyLevel -= 50;
                        FireTimer = SDL_GetTicks();
                    }
              //  }
            }

            else
            {
                FireRate = 1000;
            }

            if(GameWorld->Player1->EnergyLevel >= 99)
            {
                FireRate = 50;
            }

        }

//=======================================================================================================================================================================        

        MainWin.CLS();


           GameWorld->Update();
           GameWorld->Render();

           std::string Str = std::to_string(Player::PlayerOne->Score);
            const char* S = Str.c_str();
           FontRender::Fonts->Write("Score: " ,Vec2(10,10));
           FontRender::Fonts->Write(S, Vec2(160,10));
           if(Player::PlayerOne->Score < 0 )
           {
               Player::PlayerOne->Score = 0;
           }
        MainWin.SYNC();
  //  Print(MainWin.FPS);
    }
 

    Entity::Unload();
    delete(FontRender::Fonts);

    delete(GameWorld);
    delete(Bullet);
    delete(Plasma);
}