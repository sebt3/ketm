/*
 * $Id: soundmanager.c,v 1.4 2003/02/09 07:34:16 kenta Exp $
 *
 * Copyright 2002 Kenta Cho. All rights reserved.
 */

/**
 * BGM/SE manager(using SDL_mixer).
 *
 * @version $Revision: 1.4 $
 */
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#ifdef PSP
#include <pspdebug.h>
#endif

#include <SDL/SDL_mixer.h>
#include "soundmanager.h"
#include "support.h"
static int useAudio = 0;

#define MUSIC_NUM 2

/*static char *musicFileName[MUSIC_NUM] = {
  "stg0", "stg1",
};
static Mix_Music *music[MUSIC_NUM];
*/


static Mix_Music *music;

///////added by Farox
int _CurrentVolume;
////////////////////////////

#define CHUNK_NUM 7

//#define moddir "/mnt/sd/game/ketm_2x/_1941"

// farox mod...temporary until a menu is done
//#define moddir "./_1941"
#define moddir "./_episode1"

static char *chunkFileName[CHUNK_NUM] = {
  "shot.wav", "hit.wav", "foedst.wav", "bossdst.wav", "shipdst.wav", "bonus.wav", "extend.wav",
};
static Mix_Chunk *chunk[CHUNK_NUM];
static int chunkFlag[CHUNK_NUM];

void closeSound() {
  int i;
  if ( !useAudio ) return;
  if ( Mix_PlayingMusic() ) {
    Mix_HaltMusic();
  }
/*
  for ( i=0 ; i<MUSIC_NUM ; i++ ) {
    if ( music[i] ) {
      Mix_FreeMusic(music[i]);
    }
  }
*/
  for ( i=0 ; i<CHUNK_NUM ; i++ ) {
    if ( chunk[i] ) {
      Mix_FreeChunk(chunk[i]);
    }
  }
  Mix_CloseAudio();
}


// Initialize the sound.

static void loadSounds() {
  int i;
  char name[52];
/*
  for ( i=0 ; i<MUSIC_NUM ; i++ ) {
    strcpy(name, "sounds/");
    strcat(name, musicFileName[i]);
    strcat(name, ".s3m");
    if ( NULL == (music[i] = Mix_LoadMUS(name)) ) {

		//try mod
    	strcpy(name, "sounds/");
    	strcat(name, musicFileName[i]);
    	strcat(name, ".mod");
    	if ( NULL == (music[i] = Mix_LoadMUS(name)) ) {
    		strcpy(name, "sounds/");
    		strcat(name, musicFileName[i]);
    		strcat(name, ".xm");
    		if ( NULL == (music[i] = Mix_LoadMUS(name)) ) {
    			strcpy(name, "sounds/");
    			strcat(name, musicFileName[i]);
    			strcat(name, ".ogg");
    			if ( NULL == (music[i] = Mix_LoadMUS(name)) ) {
      				pspDebugScreenPrintf("Couldn't load: %s\n", name);
      				//useAudio = 0;
      				//return;
			}
		}
	}
    }
  }
*/
  for ( i=0 ; i<CHUNK_NUM ; i++ ) {
    strcpy(name, moddir);
    strcat(name, "/sounds/");
    strcat(name, chunkFileName[i]);
    if ( NULL == (chunk[i] = Mix_LoadWAV(name)) ) {
      #ifdef PSP
      pspDebugScreenPrintf("Couldn't load: %s\n", name);
      #endif
      useAudio = 0;
      return;
    }
    chunkFlag[i] = 0;
  }
}

void initSound() {
  int audio_rate;
  Uint16 audio_format;
  int audio_channels;
  int audio_buffers;

  if ( SDL_InitSubSystem(SDL_INIT_AUDIO) < 0 ) {
    #ifdef PSP
    pspDebugScreenPrintf( "Unable to initialize SDL_AUDIO: %s\n", SDL_GetError());
    #endif
    return;
  }

  #ifdef GP2X
  audio_rate = 22050;
  audio_format = AUDIO_S16;
  audio_channels = 2;
  audio_buffers = 256 ;
  #else
  audio_rate = 44100;
  audio_format = AUDIO_S16;
  audio_channels = 2;
  audio_buffers = 1024 ;
  #endif

  if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0) {
    #ifdef PSP
    pspDebugScreenPrintf( "Couldn't open audio: %s\n", SDL_GetError());
    #endif
    return;
  } else {
    Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
    #ifdef GP2X
    Mix_AllocateChannels(16); //added by Farox
    #endif
  }

  useAudio = 1;
  loadSounds();
  ////////added by Farox
  _CurrentVolume=64;
  Mix_Volume(-1,_CurrentVolume);
  ////////////////////////
}

// Play/Stop the music/chunk.

void playMusic(char *file) {
  char name[72];
 /*   if ( music!=NULL ) {
  	if ( Mix_PlayingMusic() )
    		Mix_HaltMusic();
      	Mix_FreeMusic(music);
	music=NULL;
    } */
  if ( !useAudio ) return;
    strcpy(name, moddir);
    strcat(name, "/sounds/");
    strcat(name, file);
    strcat(name, ".s3m");
    if ( NULL == (music = Mix_LoadMUS(name)) ) {

		//try mod
    	strcpy(name, moddir);
    	strcat(name, "/sounds/");
    	strcat(name, file);
    	strcat(name, ".mod");
    	if ( NULL == (music = Mix_LoadMUS(name)) ) {
    		strcpy(name, moddir);
    		strcat(name, "/sounds/");
    		strcat(name, file);
    		strcat(name, ".xm");
    		if ( NULL == (music = Mix_LoadMUS(name)) ) {
    			strcpy(name, moddir);
    			strcat(name, "/sounds/");
    			strcat(name, file);
    			strcat(name, ".ogg");
    			if ( NULL == (music = Mix_LoadMUS(name)) ) {
    			    #ifdef PSP
      				pspDebugScreenPrintf("Couldn't load: %s\n", name);
      				#endif
      				//useAudio = 0;
      				//return;
			}
		}
	}
    }
  Mix_PlayMusic(music, -1);
}

void pauseMusic() {
  if ( !useAudio ) return;
  Mix_PauseMusic();
}

void resumeMusic() {
  if ( !useAudio ) return;
  Mix_ResumeMusic();
}

void fadeMusic() {
  if ( !useAudio ) return;
  Mix_FadeOutMusic(1280);
}
////////////////added by Farox
void GlobalVolumeUp() {
  if ( !useAudio ) return;
  // Check the current volume is above 0
    if(_CurrentVolume < 128)
    {
        // Change the volume level up a notch
        _CurrentVolume += 16;
        if(_CurrentVolume > 128)
        {
        _CurrentVolume == 128;
        }
        Mix_Volume(-1,_CurrentVolume);
        Mix_VolumeMusic (_CurrentVolume);
    }
}

void GlobalVolumeDown() {
  if ( !useAudio ) return;
  // Check the current volume is below 128
    if(_CurrentVolume > 0)
    {
        // Change the volume level up a notch
        _CurrentVolume -= 16;
        if(_CurrentVolume <= 0)
        {
        _CurrentVolume == 0;
        }
        Mix_Volume(-1,_CurrentVolume);
        Mix_VolumeMusic (_CurrentVolume);
    }
}
////////////////////////////////////////

void stopMusic() {
  if ( !useAudio ) return;
//    if ( music!=NULL ) {
  	if ( Mix_PlayingMusic() )
    		Mix_HaltMusic();
 //     	Mix_FreeMusic(music);
//	music=NULL;
 //   }
}

void playChunk(int idx) {
  if ( !useAudio ) return;
  Mix_PlayChannel(idx, chunk[idx], 0);
}

void setChunkVolume(int volume) {
	int i;
	for (i=0; i<CHUNK_NUM; i++)
		Mix_VolumeChunk(chunk[i], volume);
}
