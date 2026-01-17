# BlackTigerGBA V0.2.1

This is a Black Tiger / Black Dragon - Arcade emulator for the GBA.

## How to use

Now put blktiger.zip/blkdrgon.zip into a folder where you have arcade roms.

When the emulator starts, you can press L+R to open up the menu (the emulator
tries to load Black Tiger automagically on startup). Now you can use the cross
to navigate the menus, A to select an option, B to go back a step.

## Menu

### File

* Load Game: Select a game to load.
* Load State: Load a previously saved state for the currently running game.
* Save State: Save a state for the current game.
* Save Settings: Save the current settings.
* Reset Game: Reset the currently running game.

### Controller

* B Autofire: Select if you want autofire on button B.
* A Autofire: Select if you want autofire on button A.
* Controller: 2P start a 2 player game.
* Swap A-B: Swap which GBA button is mapped to which arcade button.

### Display

* Display: Here you can select if you want scaled or unscaled screenmode. Unscaled mode:  L & R buttons scroll the screen up and down.
* Scaling: Here you can select if you want flicker or barebones lineskip.
* Gamma: Lets you change the gamma ("brightness").

### Dipswitches

Lot of settings for the actual arcade game, difficulty/lives etc.

### Settings

* Speed: Switch between speed modes.
  * Normal: Game runs at it's normal speed.
  * 200%: Game runs at double speed.
  * Max: Game runs at 4 times normal speed.
  * 50%: Game runs at half speed.
* Autoload State: Toggle Savestate autoloading. Automagically load the savestate associated with the selected game.
* Autosave Settings: Saves changed settings every time you leave menu.
* Autopause Game: Toggle if the game should pause when opening the menu.
* Overclock EWRAM: Changes the waitstates on EWRAM between 2 and 1, might
 damage your GBA and uses more power, around 10% speedgain. Doesn't work on
 Gameboy Micro. Use at your own risk!
* Autosleep: Choose between 5 min, 10 min, 30 min & off.

### Debug

* Debug Output: Show an FPS meter for now.
* Disable Foreground: Turn on/off foreground rendering.
* Disable Background: Turn on/off background rendering.
* Disable Sprites: Turn on/off sprite rendering.
* Step Frame: Emulate one frame.

### About

Some dumb info about the game and emulator...

### Sleep

Put the GBA into sleepmode. START+SELECT wakes up from sleep mode (activated
 from this menu or from 5/10/30 minutes of inactivity).

### Restart

Restart game.

## Credits

```text
Huge thanks to Loopy for the incredible PocketNES, without it this emu would
probably never have been made.
Thanks to:
Dwedit for help and inspiration with a lot of things.
Reesy for help with the Z80 emu core.
MAME team for driver info.
```

Fredrik Ahlström

<https://bsky.app/profile/therealflubba.bsky.social>

<https://www.github.com/FluBBaOfWard>

X/Twitter @TheRealFluBBa
