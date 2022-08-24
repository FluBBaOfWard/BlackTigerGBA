# BlackTigerGBA V0.1.6

This is a Black Tiger / Black Dragon - Arcade emulator for the GBA.

## How to use:
Now put blktiger.zip/blkdrgon.zip into a folder where you have arcade roms.

When the emulator starts, you can press L+R to open up the menu (the emulator
tries to load Black Tiger automagically on startup). Now you can use the cross
to navigate the menus, A to select an option, B to go back a step.

## Menu:
### File:
	Load Game: Select a game to load.
	Load State: Load a previously saved state for the currently running game.
	Save State: Save a state for the current game.
	Save Settings: Save the current settings.
	Reset Game: Reset the currently running game.
### Controller:
	Autofire: Select if you want autofire.
	Controller: 2P start a 2 player game.
	Swap A/B: Swap which GBA button is mapped to which arcade button.
### Display:
	Display: Here you can select if you want scaled or unscaled screenmode.
		Unscaled mode:  L & R buttons scroll the screen up and down.
	Scaling: Here you can select if you want flicker or barebones lineskip.
	Gamma: Lets you change the gamma ("brightness").
	Disable Foreground: Turn on/off foreground rendering.
	Disable Background: Turn on/off background rendering.
	Disable Sprites: Turn on/off sprite rendering.
### Settings:
	Speed: Switch between speed modes.
		Normal: Game runs at it's normal speed.
		200%: Game runs at double speed.
		Max: Game runs at 4 times normal speed (might change in the future).
		50%: Game runs at half speed.
	Autoload State: Toggle Savestate autoloading.
		Automagically load the savestate associated with the selected game.
	Autosave Settings: Saves changed settings every time you leave menu.
	Autopause Game: Toggle if the game should pause when opening the menu.
	Debug Output: Show an FPS meter for now.
	Autosleep: Choose between 5 min, 10 min, 30 min & off.
### Dipswitches:
	Lot of settings for the actual arcade game, difficulty/lives etc.
### Help:
	Some dumb info about the game and emulator...
### Sleep:
	Put the GBA to sleep, this lets you continue later.

### Restart:
	Restart game.

## Credits:
Huge thanks to Loopy for the incredible PocketNES, without it this emu would
probably never have been made.
Thanks to:
Dwedit for help and inspiration with a lot of things.
Reesy for help with the Z80 emu core.
MAME team for driver info.


Fredrik Ahlström
Twitter @TheRealFluBBa
http://www.github.com/FluBBaOfWard

