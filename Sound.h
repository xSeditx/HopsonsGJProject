#include"window.h"
#include"SDL_Mixer.h"





class Sound
{
public:
    Sound()
    {
            //Initialize SDL_mixer
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT,2, 4096 ) == -1 )
        {
            Print("Failed to initialize sound");  
        }
        else
        {
            BottleRocket = Mix_LoadWAV( "Laser.wav" );
            BGmusic = Mix_LoadMUS("Music.wav");
            Mix_VolumeMusic(1000 );
            Mix_Volume(-1, 20);
            printf("Music Error %s",Mix_GetError());
        }
    }

    Mix_Chunk *BottleRocket;
    Mix_Music *BGmusic;
    void Play(Mix_Chunk *sound)
    {
        Mix_PlayChannel(-1, sound, 0);
    }

    void MusicPlay(Mix_Music *song)
    {
         Mix_PlayMusic( song, -1 );
    }


    ~Sound()
    {
        Mix_FreeChunk(BottleRocket);
    }

};

