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


#include"Sprite.h"
#include<memory>


  SpriteSheet *SpriteSheet::Ship,
              *SpriteSheet::Eye, 
              *SpriteSheet::EnergySpheres, 
              *SpriteSheet::Bullet,
              *SpriteSheet::PlasmaBurst;
              

//==================================================================================================================================
//_______________________________________  StaticSprite Sheet Class ______________________________________________________________________
//                                                                                                                                  
//  Multiple Sprites are capable of using the same sheet. They are broken down by the State Class and Entity class
//==================================================================================================================================

SpriteSheet::SpriteSheet(char *file):SOURCE_FILE(file){
    	IMAGE = IMG_Load(SOURCE_FILE);
    	if(!IMAGE){
    		    Print("Image Can not be loaded");Print(file);
    	}
    
    	SOURCE = SDL_CreateTextureFromSurface(SCREEN->Renderer,IMAGE);
    	if(!SOURCE){
    		    Print("Texture Can not be made.");Print(file);
    	}
        SDL_FreeSurface(IMAGE);

}
Texture* SpriteSheet::LoadImageSheet(const char* file)
{
    	IMAGE = IMG_Load(file);
    	if(!IMAGE)
        {
    		    Print("Image Can not be loaded");Print(file);
    	}
    
    	SDL_Texture *text = SDL_CreateTextureFromSurface(SCREEN->Renderer,IMAGE);
    	if(!text)
        {
    		    Print("Texture Can not be made.");Print(file);
    	}
        SDL_FreeSurface(IMAGE);
        return text;
}

void SpriteSheet::LoadAssets()
{
       Eye = new SpriteSheet("Eye.bmp");
       Ship = new SpriteSheet("Ship.bmp");
       EnergySpheres = new SpriteSheet("EnergySpheres.bmp");
       Bullet = new SpriteSheet("Bullet.bmp");
       PlasmaBurst = new SpriteSheet("PlasmaBurst.bmp");
}

//==================================================================================================================================
//_______________________________________  State Class ______________________________________________________________________
//                                                                                                                                  
//   Each State is a state that an Entity can be in, Dead alive etc and is a group of frames that represents a state of the StaticSprite
//==================================================================================================================================


State::State(SDL_Rect srcrect,uint numframes):TOTAL_FRAMES(numframes){
        CURRENT_FRAME = 0;
    	FRAMES.reserve(numframes);
    	uint x = 0;
    	LOOP(numframes){
    		    SDL_Rect frame;
    		    frame.x = x;
    		    frame.y = srcrect.y;
    		    frame.w = srcrect.w;
    		    frame.h = srcrect.h;
			   *this += frame; //FIXED Remember to get back to fixing the Overloaded Operator so that you can += new frames and states into your frame list.
    		    x += srcrect.w;
    	}
}

std::vector<SDL_Rect> &State::ADD_FRAME(SDL_Rect frame){
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
   // SDL_RenderCopy(SCREEN->Renderer, SOURCE->SOURCE, &srcrect, &dstrect);
    SDL_RenderCopyEx(SCREEN->Renderer, SOURCE->SOURCE, &srcrect, &dstrect, Angle, NULL, SDL_FLIP_NONE);
}

//==================================================================================================================================
//_______________________________________  Left over helper functions ______________________________________________________________________
//  
// Possibly add these to a Class later on, These are old from when the code was first wrote months and months ago.
//==================================================================================================================================


std::shared_ptr<SpriteSheet> LOAD_SHEET(char *file)
{
    return std::make_shared<SpriteSheet>(file);
}
void DESTROY_SHEET(SpriteSheet *sheet)
{
	delete(sheet);
}
SDL_Rect  MAKE_Rect(int x,int y, int w, int h){
	SDL_Rect ret;
		ret.x=x;
		ret.y=y;
		ret.h=h;
		ret.w=w;
return ret;
}




