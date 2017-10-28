#include "main.h"
#include "scalebit.h"
//#include <psppower.h>

extern SDL_Surface *screen;
extern SDL_Surface *display;
extern int keyboard[];

GAMESTATE state;
GAMESTATE laststate;

int score;
int lives;
int volume=2; /* 0-4 */ //was 3 changed by Farox
int difficulty=DIFF_EASY;


char mods[20][20];
int modcount=0;


void wait(){
        int i,j;
        for (i=0; i<10000; i++) {
                for(j=0; j<2000; j++)
			j++;
	}
}


void readModDirs( ) {
	//fprintf(stdout,"readDataDirs\n");
  DIR *dp;
  struct dirent *dir;
  if ( (dp = opendir(".")) == NULL ) {
    fprintf(stderr, "Can't open directory: ");
    exit(1);
  }
  while ((dir = readdir(dp)) != NULL) {
	if (dir->d_name[0]!='_') continue;
    //fprintf(stdout,"%s\n", dir->d_name);
    fprintf(stderr,"%s\n", dir->d_name);
    strcpy(mods[modcount],dir->d_name);
    modcount++;
  }
  closedir(dp);
}

/*
void chooseModDir() {
	int i;
	int selected=0;
	SceCtrlData cpad;
	memset(moddir,0,20);

	readModDirs();
	while (strlen(moddir)<2) {
		pspDebugScreenClear();
printF("\n \
 _  __ ___  _____  __  __ \n \
| |/ /| __||_   _||  \\/  | \n \
| ' < | _|   | |  | |\\/| | \n \
|_|\\_\\|___|  |_|  |_|  |_| \n\n");

		printF("\t\t version 0.9\n\n\n");
		printF("Please choose the mod:\n\n");
		for (i=0; i<modcount; i++) {
			if (i==selected)
				printF(">>> ");
			else
				printF("    ");
			printF("%s\n",mods[i]);


		}
		while (1) {
		sceCtrlReadBufferPositive(&cpad, 1);
		if ((cpad.Buttons & PSP_CTRL_UP) || (cpad.Ly <= 0x30)){
			if (selected>0) selected--;
			break;

		}
		if ((cpad.Buttons & PSP_CTRL_DOWN) || (cpad.Ly >= 0xD0)){
			if (selected<modcount-1) selected++;
			break;

		}

		 if (cpad.Buttons & PSP_CTRL_CROSS) {
			strcpy(moddir,mods[selected]);
			break;
		}
		}
		wait();

	}



}
*/

///////////////////////////
void chooseModDir() {
	int i;
	int selected=0;
	//SceCtrlData cpad;
	memset(moddir,0,20);

	readModDirs();
	//while (strlen(moddir)<2) {
		//pspDebugScreenClear();


		//for (i=0; i<modcount; i++) {
		//	if (i==selected)
				//fprintf(stdout,">>> ");
		//	else
				//fprintf(stdout,"    ");
			//fprintf(stdout,"%s\n",mods[i]);


		//}
		/*
		while (1) {
		//sceCtrlReadBufferPositive(&cpad, 1);
		//if ((cpad.Buttons & PSP_CTRL_UP) || (cpad.Ly <= 0x30)){
			if (selected>0) selected--;
			break;

		//}
		//if ((cpad.Buttons & PSP_CTRL_DOWN) || (cpad.Ly >= 0xD0)){
			if (selected<modcount-1) selected++;
			break;

		//}

		// if (cpad.Buttons & PSP_CTRL_CROSS) {
			strcpy(moddir,mods[selected]);
			break;
		//}
		}
		wait();
        */
	//}



}

////////////////////////////////

int main(int argc, char *argv[])
{
	/*
	scePowerSetClockFrequency(333,333,166);
	 pspDebugScreenInit();
	printF("Starting K.E.T.M.\n");
	chooseModDir();
    */
    //chooseModDir();

	game_init(argc, argv);
	playMusic("intro");
	while (state.mainstate!=ST_GAME_QUIT) {
		keyboard_poll();

		switch(state.mainstate) {
			case ST_START_INTRO:
				if(state.newstate) {
					startintro_init();
					state.newstate=0;
				}
				startintro_work();
				break;
			case ST_INTRO:
				if(state.newstate) {
					intro_init();
					state.newstate=0;
				}
				intro_work();
				break;
			case ST_GAME_PLAY:
				if(state.newstate) {
					playChunk(1);
					playMusic("stage1");
					thegame_init();
					state.newstate=0;
				}
				thegame_work();
				break;
			case ST_GAME_OVER:
				if(state.newstate) {
					playChunk(4);
					stopMusic();
					gameover_init();
					playMusic("intro");
					state.newstate=0;
				}
				gameover_work();
                                //newstate(ST_INTRO,0,1);
				break;
			case ST_MENU:
				if(state.newstate) {
					menu_init();
					state.newstate=0;
				}
				menu_work();
				break;
			case ST_SHOW_HCLIST:
				if(state.newstate) {
					hsc_show_init();
					state.newstate=0;
				}
				hsc_show_work();
				break;
			case ST_ENTRY_HCLIST:
				if(state.newstate) {
					hsc_entry_init();
					state.newstate=0;
				}
				hsc_entry_work();
				break;
		}

		fps_show();
		if (scaling==2||scaling==3)
			//scale2x(screen,display);
			scale(scaling, display->pixels, depth*scaling*WIDTH/8, screen->pixels, depth*WIDTH/8, depth/8, WIDTH, HEIGHT);
		else
			SDL_BlitSurface(screen,NULL,display,NULL);
		SDL_Flip(display);
		fps_newframe();
	}

	/* TODO: Free everything (memory, SDL_Surfaces, Joysticks...) */

	hsc_save();

	//fprintf(stdout,"Thank you for playing\n");
	exit(0);
}
