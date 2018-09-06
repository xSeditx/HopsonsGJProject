//
//
//
//
//
//
// Initialize the Spritesheet
// Assign an Entity or AniEntity using &Spritesheet with the amount of Rows as States
// Generate each State per Entity with the amount of Frame or columns 
//
//___________________________________________________________________________________________________________________________________________

//TODO: Burn this fucking Mess to the ground and start over... Prob not going to complete that before game jam finished
#include"Sprite.h"
#include<memory>


  SpriteSheet *SpriteSheet::Ship,
              *SpriteSheet::Eye, 
              *SpriteSheet::EnergySpheres, 
              *SpriteSheet::Bullet,
              *SpriteSheet::PlasmaBurst,
              *SpriteSheet::Explosion1,
              *SpriteSheet::Cthulu, 
              *SpriteSheet::FireBall,
              *SpriteSheet::Dragon,
              *SpriteSheet::FireOrb, 
              *SpriteSheet::Lightning01;


  Sprite *Sprite::ShipSprite,
         *Sprite::Explosion, 
         *Sprite::DragonSprite,
         *Sprite::CthuluEye,
         *Sprite::EnergySphere,
         *Sprite::Plasma,
         *Sprite::FireBall,
         *Sprite::Bullet,
         *Sprite::GreenEye, 
         *Sprite::FireOrb, 
         *Sprite::Lightning01,
         *Sprite::CthuluDeath,
         *Sprite::BossDragon;
  
Sprite *Sprite::BigGun;


void Sprite::Initialize()
{

//======================---~~~  Players Ship  ~~~---=================================

     ShipSprite = new Sprite(SpriteSheet::Ship,4);
     ShipSprite->Size = Vec2(42);
     ShipSprite->STATE[0] = State(MAKE_Rect(0, 0,42, 42), 4);
     ShipSprite->STATE[1] = State(MAKE_Rect(0, 42,42, 42), 4);

     ShipSprite->ANIMATED = true;
     ShipSprite->AnimationSpeed = 100;

//======================---~~~  Standard Bullet  ~~~---===============================
             
        Bullet = new Sprite(SpriteSheet::Bullet, 1); 
        Bullet->STATE[0] = State(MAKE_Rect(0, 0,8, 8), 3);
        Bullet->ANIMATED = true;
        Bullet->Size = Vec2(8);

//=======================---~~~  Plasma Burst  ~~~---=================================
        Plasma = new Sprite(SpriteSheet::PlasmaBurst, 1);
        Plasma->STATE[0] = State(MAKE_Rect(0, 0,35,35), 42);
        Plasma->AnimationSpeed = 10;
        Plasma->ANIMATED = true;
        Plasma->Size = Vec2(35);

//======================---~~~  Ship Explosion  ~~~---================================


        Explosion = new Sprite(SpriteSheet::Explosion1, 1);
        Explosion->Size = Vec2(64);
        Explosion->AnimationSpeed = 100;
        Explosion->ANIMATED = true;
        Explosion->STATE[0]  = State(MAKE_Rect(0,   0, 128, 128), 4);
        Explosion->STATE[0] += State(MAKE_Rect(0, 128, 128, 128), 4);
        Explosion->STATE[0] += State(MAKE_Rect(0, 256, 128, 128), 4);
        Explosion->STATE[0] += State(MAKE_Rect(0, 384, 128, 128), 4);

//=======================---~~~  EnergySphere  ~~~---=================================
        EnergySphere = new Sprite(SpriteSheet::EnergySpheres,1);
        EnergySphere->Size = Vec2(32);
        EnergySphere->ANIMATED = true;
        EnergySphere->AnimationSpeed = 50;
        EnergySphere->STATE[0]  = State(MAKE_Rect(0,       0,  84, 84), 7);
        EnergySphere->STATE[0] += State(MAKE_Rect(0,      84,  84, 84), 7);
        EnergySphere->STATE[0] += State(MAKE_Rect(0, (2 * 84), 84, 84), 7);
        EnergySphere->STATE[0] += State(MAKE_Rect(0, (2 * 84), 84, 84), 7 );
        EnergySphere->STATE[0] += State(MAKE_Rect(0, (2 * 84), 84, 84), 7);


//=========================---~~~  Cthulu Eye  ~~~---=================================

        CthuluEye = new Sprite(SpriteSheet::Cthulu,1 );
        CthuluEye->Size = Vec2(32);
        CthuluEye->AnimationSpeed = 150;
        CthuluEye->ANIMATED = true;
        CthuluEye->STATE[0] = State(MAKE_Rect(0,0,32,32),2);
        
        
        DragonSprite = new Sprite(SpriteSheet::Dragon,4);
        DragonSprite->Size = Vec2(64);
        DragonSprite->AnimationSpeed = 150;
        DragonSprite->ANIMATED = true;
        DragonSprite->STATE[0] = State(MAKE_Rect(0,0,56,56),4);
        DragonSprite->STATE[1] = State(MAKE_Rect(0,56,56,56),4);
        DragonSprite->STATE[2] = State(MAKE_Rect(0,112,56,56),4);
        DragonSprite->STATE[3] = State(MAKE_Rect(0,168,56,56),4);
        
        
        FireBall = new Sprite(SpriteSheet::FireBall,1);
        FireBall->Size = Vec2(16);
        FireBall->ANIMATED = true;
        FireBall->AnimationSpeed = 50;
        FireBall->STATE[0] = State(MAKE_Rect(0,0,16,16),3);
        
        GreenEye = new Sprite(new SpriteSheet("Assets\\Tenticles.bmp"),3);
        GreenEye->Size = Vec2(100);
        GreenEye->ANIMATED = true;
        GreenEye->AnimationSpeed = 100;
        GreenEye->STATE[0] = State(MAKE_Rect(0,113,88,112),6);
        GreenEye->STATE[1] = State(MAKE_Rect(0,0,88,112),6); 
        GreenEye->STATE[2] = State(MAKE_Rect(264,0,88,112),3);
        GreenEye->CURRENT_STATE = 0;
        
        FireOrb = new Sprite(new SpriteSheet("Assets\\FireOrb.bmp"), 2);
        FireOrb->Size = Vec2(42);
        FireOrb->ANIMATED = true;
        FireOrb->AnimationSpeed = 30;
        FireOrb->STATE[0] = State(MAKE_Rect(0,0,47,47),5);
        FireOrb->STATE[1] = State(MAKE_Rect(0,47,47,47),5); 

        Lightning01 = new Sprite(new SpriteSheet("Assets\\Lightning1.bmp"), 1);
        Lightning01->Size = Vec2(90);
        Lightning01->ANIMATED = true;
        Lightning01->AnimationSpeed = 50;
        Lightning01->STATE[0] = State(MAKE_Rect(0,0,90,90),4);
//64x70
        CthuluDeath = new Sprite(new SpriteSheet("Assets\\RedExplosion.bmp"),1);
        CthuluDeath->Size = Vec2(64);
        CthuluDeath->ANIMATED = true;
        CthuluDeath->AnimationSpeed = 100;
        CthuluDeath->STATE[0] = State(MAKE_Rect(0,0,64,70),4);
        CthuluDeath->STATE[0] += State(MAKE_Rect(0,70,64,70),4);
        CthuluDeath->STATE[0] += State(MAKE_Rect(0,140,64,70),4);
        CthuluDeath->STATE[0] += State(MAKE_Rect(0,210,64,70),4);

        BigGun = new Sprite(new SpriteSheet("Assets\\BigGun.bmp"),1);
        BigGun->Size = Vec2(64);//76x84
        BigGun->ANIMATED = false;
        BigGun->AnimationSpeed = 0;
        BigGun->STATE[0] = State(MAKE_Rect(0,0,76,84),1);

        BossDragon = new Sprite(new SpriteSheet("Assets\\BlueDragon.BMP"),4);
        BossDragon->STATE[0] = State(MAKE_Rect(0,0,96,96), 4);
        BossDragon->Size = Vec2(128);
        BossDragon->ANIMATED = true;
        BossDragon->STATE[1] = State(MAKE_Rect(0,96,96,96), 4);
        BossDragon->STATE[2] = State(MAKE_Rect(0,96*2,96,96), 4);
        BossDragon->STATE[3] = State(MAKE_Rect(0,96*3,96,96), 4);

}
void SpriteSheet::Initialize()
{
       Eye           = new SpriteSheet("Assets\\Eye.bmp");
       Ship          = new SpriteSheet("Assets\\Ship.bmp");
       EnergySpheres = new SpriteSheet("Assets\\EnergySpheres.bmp");
       Bullet        = new SpriteSheet("Assets\\Bullet.bmp");
       PlasmaBurst   = new SpriteSheet("Assets\\PlasmaBurst.bmp");
       Explosion1    = new SpriteSheet("Assets\\Explosion.bmp");// 128x128'
       Dragon        = new SpriteSheet("Assets\\Dragon1.bmp");
       Cthulu        = new SpriteSheet("Assets\\Cthulu.bmp");
       FireBall      = new SpriteSheet("Assets\\Fireball.bmp");
}

void SpriteSheet::Unload()
{
   delete(Eye           );
   delete(Ship          );
   delete(EnergySpheres );
   delete(Bullet        );
   delete(PlasmaBurst   );
   delete(Explosion1    );
   delete(Dragon        );
   delete(Cthulu        );
   delete(FireBall      );
}
void Sprite::Unload()
{
    delete(ShipSprite);
    delete(Explosion);
    delete(DragonSprite);
    delete(CthuluEye);
    delete(EnergySphere);
    delete(Plasma);
    delete(FireBall);
    delete(Bullet);
    delete(GreenEye);
    delete(FireOrb);
}


Image::Image(const char *file)
{
     SourceFile = file;
     Surface *ImageSurface = IMG_Load(file);
     if(!ImageSurface)
     {
             Print("ImageClass: Image Can not be loaded");Print(file);
         return;
     }
     
     ImageTexture = SDL_CreateTextureFromSurface(SCREEN->Renderer, ImageSurface);

     if(!ImageTexture)
     {
             Print("ImageClass: Texture Can not be made.");Print(file);
         return;
     }
     Size.x = ImageSurface->w;
     Size.y = ImageSurface->h;

     SDL_FreeSurface(ImageSurface);

}
void Image::Render(Vec2 position)
{

    SDL_Rect srcrect = {0, 0, Size.x, Size.y}; 
    SDL_Rect dstrect = {position.x, position.y , position.x + Size.x, position.y + Size.y};
    SDL_RenderCopy(SCREEN->Renderer, ImageTexture, &srcrect, &dstrect);
   // SDL_RenderCopyEx(SCREEN->Renderer, SOURCE->SOURCE, &srcrect, &dstrect, Angle, NULL, SDL_FLIP_NONE);
}
void Image::Render(Vec2 position, Vec2 size)
{
    SDL_Rect srcrect = {0, 0, size.x, size.y}; 
    SDL_Rect dstrect = {position.x, position.y ,  size.x,size.y};
    SDL_RenderCopy(SCREEN->Renderer, ImageTexture, &srcrect, &dstrect);
}





//==================================================================================================================================
//_______________________________________  StaticSprite Sheet Class ______________________________________________________________________
//                                                                                                                                  
//  Multiple Sprites are capable of using the same sheet. They are broken down by the State Class and Entity class
//==================================================================================================================================

SpriteSheet::SpriteSheet(char *file)
{
    Sheet = new Image(file);
}





//==================================================================================================================================
//_______________________________________  State Class ______________________________________________________________________
//                                                                                                                                  
//   Each State is a state that an Entity can be in, Dead alive etc and is a group of frames that represents a state of the StaticSprite
//==================================================================================================================================


State::State(SDL_Rect srcrect,uint numframes)
     :TOTAL_FRAMES(numframes)
{
        CURRENT_FRAME = 0;
    	FRAMES.reserve(numframes);
    	uint x = srcrect.x;
    	for_loop(Count, numframes)
        {
    		    SDL_Rect frame;
    		    frame.x = x;
    		    frame.y = srcrect.y;
    		    frame.w = srcrect.w;
    		    frame.h = srcrect.h;
			   *this += frame; //FIXED Remember to get back to fixing the Overloaded Operator so that you can += new frames and states into your frame list.
    		    x += srcrect.w;
    	}
}

std::vector<SDL_Rect> 
    &State::ADD_FRAME(SDL_Rect frame)
{
		FRAMES.emplace_back(frame);
	return FRAMES;
} // Adds a frame to the State

AABB* Sprite::MakeCollisionBox()
{
    //IDK WTF TO DO WITH THIS AT THE MOMENT
    //SDL_Rect dstrect = {Position.x - (Size.x *.5), Position.y - (Size.y * .5), Size.x, Size.y}
    return new AABB(Position, Size *.5f);
}

//==================================================================================================================================
//_______________________________________  Entity Class ______________________________________________________________________
//                                                                                                                                  
//==================================================================================================================================

Sprite::Sprite(SpriteSheet *source, int numstates):TOTAL_STATES(numstates), SOURCE(source)
{
    TOTAL_STATES = numstates;
    STATE.reserve(numstates);

    for_loop(count, TOTAL_STATES)
    {
        State temp;
        STATE.emplace_back(temp);
    }

    CURRENT_STATE = 0;
    AnimationSpeed = 150;
    Angle = 0;
}

void Sprite::Update()
{
// Update information about this sprite, perhaps the specific frame or anythign of that nature
}
void Sprite::Render()
{
    Uint32 ticks = SDL_GetTicks();

    if( ANIMATED == true)
    {
     
        STATE[CURRENT_STATE].CURRENT_FRAME = (ticks / AnimationSpeed) % STATE[CURRENT_STATE].TOTAL_FRAMES;
    }

    SDL_Rect srcrect = STATE[CURRENT_STATE].FRAMES[STATE[CURRENT_STATE].CURRENT_FRAME]; //{ frames * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT };
    SDL_Rect dstrect = {Position.x - (Size.x *.5), Position.y - (Size.y * .5), Size.x, Size.y};
    SDL_RenderCopy(SCREEN->Renderer, SOURCE->Sheet->ImageTexture, &srcrect, &dstrect);  
}




//  SDL_RenderCopyEx(SCREEN->Renderer, SOURCE->Sheet->ImageTexture, &srcrect, &dstrect, Angle, NULL, SDL_FLIP_NONE);
//  SOURCE.Sheet->ImageTexture->Render(Position);

//==================================================================================================================================
//_______________________________________  Left over helper functions ______________________________________________________________
//  
// Possibly add these to a Class later on, These are old from when the code was first wrote months and months ago.
//==================================================================================================================================


std::shared_ptr<SpriteSheet> LOAD_SHEET(char *file)
{
    return std::make_shared<SpriteSheet>(file);
}

SDL_Rect  MAKE_Rect(int x,int y, int w, int h){
	SDL_Rect ret;
		ret.x=x;
		ret.y=y;
		ret.h=h;
		ret.w=w;
return ret;
}