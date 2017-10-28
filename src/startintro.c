#include "startintro.h"

extern int keyboard[];
extern SDL_Surface *screen;
extern GAMESTATE state;
extern float fps_factor;

SDL_Surface *badblocks=NULL;
SDL_Surface *presents=NULL;
SDL_Surface *ketm=NULL;
#ifdef PACC
SDL_Surface *PACC=NULL;
#endif


float scaled=0;

void startintro_init()
{
    #ifdef PACC
    /////////////added for PACC ///////////////
    if(PACC==NULL) {
		PACC=loadbmp("pacc.png");
		SDL_SetColorKey(PACC,SDL_SRCCOLORKEY,0x00000000);
	}
	/////////////////////////////////////
	#endif
	if(badblocks==NULL) {
		badblocks=loadbmp("badblocks.png");
		SDL_SetColorKey(badblocks,SDL_SRCCOLORKEY,0x00000000);
	}
	if(presents==NULL) {
		presents=font_render("PRESENT",FONT01);
	}
	if(ketm==NULL) {
		ketm=loadbmp("ketm.png");
		SDL_SetColorKey(ketm,SDL_SRCCOLORKEY,0x00000000);
	}
	SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
	scaled=0;
	//newstate(ST_START_INTRO,STIN_FADEIN_BB,0);old before PACC
	#ifdef PACC
	newstate(ST_START_INTRO,STIN_FADEIN_PACC,0);
	#else
	newstate(ST_START_INTRO,STIN_FADEIN_BB,0);
	#endif
}
void startintro_work()
{
	if(state.mainstate!=ST_START_INTRO || state.newstate==1) return;

    #ifdef PACC
	if(keyboard_keypressed()) {

	    if (state.substate!=STIN_FADEIN_PACC) //added for PACC
	    {
		newstate(ST_START_INTRO,STIN_QUIT,0);
	    }

	}
	#else

	if(keyboard_keypressed()) {

		newstate(ST_START_INTRO,STIN_QUIT,0);
	    }

	#endif

	SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));

	switch(state.substate) {
	    #ifdef PACC
	    case STIN_FADEIN_PACC:
			scaled+=0.008*fps_factor;
			SDL_BlitSurface(PACC,NULL,screen,NULL); //changed for PACC
			//startintro_centerimg(PACC,scaled);
			if(scaled>=3.0) {
			//	used here as a timer...
				scaled=0;
				newstate(ST_START_INTRO,STIN_FADEIN_BB,0);
			}
			break;
         #endif
		case STIN_FADEIN_BB:
			//scaled+=0.005*fps_factor; changed by Farox
			scaled+=0.004*fps_factor;
			startintro_centerimg(badblocks,scaled);
			if(scaled>=1.0) {
			//	parsys_add(badblocks,2,2,screen->w/2-badblocks->w/2,screen->h/2-badblocks->h/2,30,0,0,400,PIXELIZE,NULL);
				scaled=0;
				newstate(ST_START_INTRO,STIN_FADEIN_PRESENTS,0);
			}
			break;
		case STIN_FADEIN_PRESENTS:
			scaled+=0.01*fps_factor;
			startintro_centerimg(presents,scaled);
			if(scaled>=1.0) {
			//	parsys_add(presents,presents->w,1,screen->w/2-presents->w/2,screen->h/2-presents->h/2,10,0,0,200,LINESPLIT,NULL);
				scaled=0;
				newstate(ST_START_INTRO,STIN_FADEIN_KETM,0);
			}
			break;
		case STIN_FADEIN_KETM:
			scaled+=0.01*fps_factor;
			startintro_centerimg(ketm,scaled);
			if(scaled>=1.0) {
			//	parsys_add(ketm,4,4,screen->w/2-ketm->w/2,screen->h/2-ketm->h/2,30,0,0,100,PIXELIZE,NULL);
				scaled=0;
				newstate(ST_START_INTRO,STIN_SLEEP,0);
			}
			break;
		case STIN_SLEEP:
			scaled+=fps_factor;
			if(scaled>=100) {
				newstate(ST_START_INTRO,STIN_QUIT,0);
			}
			break;
		case STIN_QUIT:
			//parsys_remove_all();

			#ifdef PACC
			/////added for PACC
			unloadbmp_by_name("pacc.png");
			/////////////////
			#endif

			unloadbmp_by_name("badblocks.png");
			badblocks=NULL;
			//SDL_FreeSurface(presents);
			presents=NULL;
			unloadbmp_by_name("ketm.png");
			ketm=NULL;
			newstate(ST_INTRO,0,1);
	}

	parsys_display();

}

void startintro_centerimg(SDL_Surface *src, float scaled)
{
	SDL_Rect sr,dr;

	sr.w=src->w;
	sr.h=src->h;
	sr.x=0;
	sr.y=0;
	dr.w=src->w*scaled;
	dr.h=src->h*scaled;
	dr.x=screen->w/2-dr.w/2;
	dr.y=screen->h/2-dr.h/2;
	blit_scaled(src, &sr, screen, &dr);
}
