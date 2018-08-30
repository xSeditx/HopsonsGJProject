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
Sound *GameSounds;





void KeyDown(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier, Uint8 rep) 
{
  //  switch(Keycode)
 //  {
 //      case SDL_SCANCODE_LEFT:
 //          GameWorld->Player1->CollisionBox->Body.Velocity.x -= ShipSpeed;
 //      break;
 //      
 //      case SDL_SCANCODE_RIGHT:
 //          GameWorld->Player1->CollisionBox->Body.Velocity.x += ShipSpeed;
 //      break;
 //      case SDL_SCANCODE_UP:
 //          GameWorld->Player1->CollisionBox->Body.Velocity.y -= ShipSpeed;
 //      break;
 //      
 //      case SDL_SCANCODE_DOWN:
 //          GameWorld->Player1->CollisionBox->Body.Velocity.y += ShipSpeed;
 //      break;
 //  }

    if(SCREEN->Keyboard.KeyState[SDL_SCANCODE_LEFT] == true)
    {
           // GameWorld->Player1->CollisionBox->Body.Position.x -= ShipSpeed;
            GameWorld->Player1->CollisionBox->Body.Force.x -= ShipSpeed;
    }
    if(SCREEN->Keyboard.KeyState[SDL_SCANCODE_RIGHT] == true)
    {
           // GameWorld->Player1->CollisionBox->Body.Position.x += ShipSpeed;
            GameWorld->Player1->CollisionBox->Body.Force.x += ShipSpeed;
    }
    if(SCREEN->Keyboard.KeyState[SDL_SCANCODE_UP] == true)
    {
          //  GameWorld->Player1->CollisionBox->Body.Position.y -= ShipSpeed;
            GameWorld->Player1->CollisionBox->Body.Force.y -= ShipSpeed;
    }
    if(SCREEN->Keyboard.KeyState[SDL_SCANCODE_DOWN] == true)
    {
           // GameWorld->Player1->CollisionBox->Body.Position.y += ShipSpeed;
            GameWorld->Player1->CollisionBox->Body.Force.y += ShipSpeed;
    }


}
void KeyUp(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier )
{
}
void MouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
 // GameWorld->Player1->Position.x = mX;
 // GameWorld->Player1->Position.y = mY;
 ///
  GameWorld->Player1->CollisionBox->Body.Position.y = mY;
  GameWorld->Player1->CollisionBox->Body.Position.x = mX;

}
void MouseLClick(int mX, int mY)
{
    Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x - 20, GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -3), Bullet);
    Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x + 15, GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -3), Bullet);
    GameSounds->Play(GameSounds->BottleRocket);
}
void MouseRClick(int mX, int mY)
{
    if(GameWorld->Player1->EnergyLevel > 0)
    {
        Projectile::Spawn(Vec2(GameWorld->Player1->CollisionBox->Body.Position.x , GameWorld->Player1->CollisionBox->Body.Position.y + 30), Vec2(0, -.2), Plasma );
        GameSounds->Play(GameSounds->BottleRocket);
        GameWorld->Player1->EnergyLevel -= 500;
    }
}



void main()
{
    Window MainWin(0,0,SCREENWIDTH,SCREENHEIGHT,"Hopsons Game Jam");
           MainWin.CallBacks.SetOnKeyDown(KeyDown);
           MainWin.CallBacks.SetOnKeyUp(KeyUp);
           MainWin.CallBacks.SetOnMouseMove(MouseMove);
           MainWin.CallBacks.SetOnLButtonDown(MouseLClick);
           MainWin.CallBacks.SetOnRButtonDown(MouseRClick);

    VideoCamera *Camera = new VideoCamera(Vec2( 0, 0),Vec2(SCREENWIDTH *.5, SCREENHEIGHT *.5));

    GameWorld = new World(Camera);
        
    Bullet = new Sprite(new SpriteSheet("Bullet.bmp"), 1); 
    Bullet->STATE[0] = State(MAKE_Rect(0, 0,8, 8), 3);
    Bullet->ANIMATED = true;
    Bullet->Size = Vec2(8);
    
    Plasma = new Sprite(new SpriteSheet("PlasmaBurst.bmp"), 1);
    Plasma->STATE[0] = State(MAKE_Rect(0, 0,35,35), 42);
    Plasma->AnimationSpeed = 10;
    Plasma->ANIMATED = true;
    Plasma->Size = Vec2(35);
    
    

    FontRender Fonts;
    Fonts.LoadFont("SpaceAge.ttf");

    GameSounds = new Sound();
    GameSounds->MusicPlay(GameSounds->BGmusic);


    const char* SayScore = "SCORE: ";

    while(MainWin.LOOP_GAME())
    {
        MainWin.CLS();
           std::string Str = std::to_string(Score);
            const char* S = Str.c_str();

           Fonts.Write(SayScore,10,10);
           Fonts.Write(S,160,10);

           GameWorld->Update();
           GameWorld->Render();
                       if(Score < 0 ) Score = 0;
        MainWin.SYNC();
    Print(MainWin.FPS);
    }
}