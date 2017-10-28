KETM PSP v0.9- Kill Everything That Moves.

This is a PSP adoptation of KETM (studio-grey/badblocks), fast paced tyrian style 2D shooter.
Featuring 
- 4 levels with different environments, music & bosses
- 1 bonus level
- 15 enemies with unique attack patterns and adjusting hostility
- 7 primary weapons
- 4 secondary weapons (rockets, laser, bomb, rotating shield)
- 2 mods: original episode1 and 1941 mod by bourbon_bot
- Fully modable design: you can change sounds, graphics, script your own attacking sequences and intensity.
- Source code & PSPSDK Makefile provided

NEW IN v0.9
----------
- added explosions when plane is hit
- increased the transparency level during the invinsibility period
- new enemy ( GROUNDER ) and objects BGPANEL/BGPANEL2 added.
sample definition:
00100|6|GROUNDER|200032
Last parameter is the x,y coordinates in format x*1000+y
second parameter is the downscroll speed (5 = bg speed)
- added all sprites to "pre-loader" about 10 sprites were missing in v.8, and that 
  caused minor hickups during the inital run of the levels.
- slightly changed AI and atacking patterns of some enemies
- changed the shield size for the plane to smaller and more realistic size..
- level4
- added the ending/bonus level.
- high scores are saved now
- added in-game messages fade-out
- better difficulty settings (the game is made easier on "EASY" setting
- removed some debugging stuff



NEW IN v0.8
----------
- Hardware rendering: big performance boost; game runs ~ 30% faster now
- Patched old objects garbage collection bug which used to slow down the game at later stages.
- Menu cleanup: all menu functions should work now. Fixed difficulty & sound fx tabs.
- Big graphics facelift, thanks to bourbon_bot :-).. 
- 2 new enemy patterns & 1 new boss


INSTALLATION
--------

1.5 users: copy contents of 1.5 folder to ms:/PSP/GAME
1.0 use EBOOT.PBP from 1.0 folder with data files from 1.5 folder
2.0 Please let me know if either version works with the latest eboot loader for 2.0 firmware

You can try to rebuild the binary with the source code provided.


CONTROLS
----------------

[ANALOG PAD]		MENU NAVIGATION & SHIP'S IN GAME MOVEMENTS
[TRANGLE]			SELECT/FIRE 


MODDING THE GAME
--------------
Create a new folder starting with '_' in ms:/PSP/GAME/ketm
Copy ALL graphics, data files and sounds from episode1 in to your new folder.
You can change the size of most sprites as long as you keep them proportional
and keep the number of frames in animations the same.
Game sequence is scripted in levelXX.dat files. 
The format is explained in the coments in the begining of the data file.
The music can be in s3m/xm/mod tracker formats or in ogg vorbis. 
Keep in mind that ogg decryption is much more cpu intensive and may slowdown the game.

TODO
---
- Fix SDL_surface related memory leak: the game runs out of memory in ~30 min of play
- Create more episoded



Enjoy,

DENIS
