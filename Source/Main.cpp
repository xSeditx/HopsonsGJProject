#include"../Header/window.h"
#include"../Header/Sprite.h"
#include"../Header/World.h"
#include"../Header/Fonts.h"
#include"../Header/Sound.h"
#include<string>
///#include"../Header/Camera.h"


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
  

    SDL_SetRelativeMouseMode(SDL_TRUE); // Locks mouse to the window



    while(MainWin.LOOP_GAME())
    {
//=======================================================================================================================================================================        
//_____________________________________________________  KEYBOARD STUFF  ___________________________________________________________________________________________________
//________________________________________________________________________________________________________________________________________________________________________

        if((SDL_GetTicks() - FireTimer) > FireRate)
        {
            if(GameWorld->Player1->EnergyLevel > 0)
            {
                if(IsLMouseButtonDown == true)
                {
                    int Index1 = Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x - 20, GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -3), Sprite::Bullet);
                    int Index2 = Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x + 15, GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -3), Sprite::Bullet);
 
                    Projectile::ProjectileList[Index1].BulletPower = 50;
                    Projectile::ProjectileList[Index2].BulletPower = 50;

                    Entity::PlayerOne->EnergyLevel -= 9;
                    SoundEffect::LaserTail0005->Play(); //   6   8
                    SoundEffect::LaserHead0006->Play();
                    
                    FireTimer = SDL_GetTicks();
                }
            }  
            else // Energy level 0 or less
            {
                FireRate = 500;
            }

            if(GameWorld->Player1->EnergyLevel >= 99) // Set the fire rate back to normal after the Spam lock time out has expired
            {
                FireRate = 50;
            }
        }

// This is for the Big gun on the Right Mouse Button, I know there is a better way to do all this but this was the fastest solution becayse
// I was running into issues when I had the mouse check at the same time in the above if statement
// Its damn near a repeat from the above although the fire rates are altered slightly to make the big gun act better
        if((SDL_GetTicks() - FireTimer) > (FireRate * 4))
        {
            if(GameWorld->Player1->EnergyLevel > 0 )
            {
                if(IsRMouseButtonDown == true)
                {
                    int Index = Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x , GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -4), Sprite::BigGun );
                    Projectile::ProjectileList[Index].BulletPower = 1000;
                    
                    SoundEffect::Boom1->Play();
                
                    GameWorld->Player1->EnergyLevel -= 50;
                    FireTimer = SDL_GetTicks();
                }
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

        MainWin.SYNC();
    Print(MainWin.FPS);
    }
 

    Entity::Unload();
    delete(FontRender::Fonts);

    delete(GameWorld);
    delete(Bullet);
    delete(Plasma);
}