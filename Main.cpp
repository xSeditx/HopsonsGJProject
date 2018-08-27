//>?
#include"window.h"
#include"Sprite.h"
#include"Projectiles.h"
#include"World.h"
#include"Camera.h"

#define SHIP_HEIGHT 64
#define SHIP_WIDTH  64


Sprite *Bullet;

World  *GameWorld;

float ShipSpeed = 10;


void KeyDown(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier, Uint8 rep) 
{
    switch(Keycode)
    {
    case SDL_SCANCODE_LEFT:
        GameWorld->Player1->Position.x -= ShipSpeed;
        break;

    case SDL_SCANCODE_RIGHT:
         GameWorld->Player1->Position.x+= ShipSpeed;
        break;

    }
}
void KeyUp(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier )
{
}
void MouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    GameWorld->Player1->Position.x = mX;
    GameWorld->Player1->Position.y = mY;

    GameWorld->Player1->CollisionBox->Body.Position.y = mY;
    GameWorld->Player1->CollisionBox->Body.Position.x = mX;

    GameWorld->Player1->CollisionBox->Body.Force.y = relY * .02f;
    GameWorld->Player1->CollisionBox->Body.Force.x = relX * .02f;

}
void MouseRClick(int mX, int mY)
{
    Projectile::Create(Vec2(mX - 20, mY + 30), Vec2(0, -3), Bullet);
    Projectile::Create(Vec2(mX + 15, mY + 30), Vec2(0, -3), Bullet);
}




void main()
{
    Window MainWin(0,0,640,880,"Hopsons Game Jam");
           MainWin.CallBacks.SetOnKeyDown(KeyDown);
           MainWin.CallBacks.SetOnKeyUp(KeyUp);
           MainWin.CallBacks.SetOnMouseMove(MouseMove);
           MainWin.CallBacks.SetOnLButtonDown(MouseRClick);

    Bullet = new Sprite(new SpriteSheet("Bullet.bmp"), 1); 
    Bullet->STATE[0] = State(MAKE_Rect(0, 0,8, 8), 3);
    Bullet->Size = Vec2(8);

    GameWorld = new Level();
    GameWorld->Load();


    while(MainWin.LOOP_GAME())
    {
        MainWin.CLS();

        Projectile::UpdateAll();

        GameWorld->Update();
        GameWorld->Render();

        MainWin.SYNC();

//Print(MainWin.FPS);
    }
}