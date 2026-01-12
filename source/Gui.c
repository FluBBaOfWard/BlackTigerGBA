#include <gba.h>

#include "Gui.h"
#include "Shared/EmuMenu.h"
#include "Shared/EmuSettings.h"
#include "Main.h"
#include "FileHandling.h"
#include "Cart.h"
#include "Gfx.h"
#include "io.h"
#include "cpu.h"
#include "BlackTiger.h"
#include "ARMZ80/Version.h"
#include "BlackTigerVideo/Version.h"

#define EMUVERSION "V0.2.1 2026-01-12"

static void scalingSet(void);
static const char *getScalingText(void);
static void controllerSet(void);
static const char *getControllerText(void);
static void swapABSet(void);
static const char *getSwapABText(void);
static void fgrLayerSet(void);
static const char *getFgrLayerText(void);
static void bgrLayerSet(void);
static const char *getBgrLayerText(void);
static void sprLayerSet(void);
static const char *getSprLayerText(void);
static void coinASet(void);
static const char *getCoinAText(void);
static void coinBSet(void);
static const char *getCoinBText(void);
static void difficultSet(void);
static const char *getDifficultText(void);
static void continueSet(void);
static const char *getContinueText(void);
static void cabinetSet(void);
static const char *getCabinetText(void);
static void livesSet(void);
static const char *getLivesText(void);
static void demoSet(void);
static const char *getDemoText(void);
static void flipSet(void);
static const char *getFlipText(void);
static void serviceSet(void);
static const char *getServiceText(void);
static void gammaChange(void);

const MItem dummyItems[] = {
	{"", uiDummy},
};
const MItem mainItems[] = {
	{"File->", ui2},
	{"Controller->", ui3},
	{"Display->", ui4},
	{"DipSwitches->", ui5},
	{"Settings->", ui6},
	{"Debug->", ui7},
	{"About->", ui8},
	{"Sleep", gbaSleep},
	{"Restart", resetGame},
	{"Quit Emulator", ui10},
};
const MItem fileItems[] = {
	{"Load Game->", ui9},
	{"Load State", loadState},
	{"Save State", saveState},
	{"Save Settings", saveSettings},
	{"Reset Game", resetGame},
};
const MItem ctrlItems[] = {
	{"B Autofire: ", autoBSet, getAutoBText},
	{"A Autofire: ", autoASet, getAutoAText},
	{"Controller: ", controllerSet, getControllerText},
	{"Swap A-B:   ", swapABSet, getSwapABText},
};
const MItem displayItems[] = {
	{"Display: ", scalingSet, getScalingText},
	{"Scaling: ", flickSet, getFlickText},
	{"Gamma: ", gammaChange, getGammaText},
};
const MItem dipItems[] = {
	{"Coin A:", coinASet, getCoinAText},
	{"Coin B:", coinBSet, getCoinBText},
	{"Difficulty:", difficultSet, getDifficultText},
	{"Allow Continue:", continueSet, getContinueText},
	{"Cabinet:", cabinetSet, getCabinetText},
	{"Lives:", livesSet, getLivesText},
	{"Demo Sound:", demoSet, getDemoText},
	{"Flip Screen:", flipSet, getFlipText},
	{"Service Mode:", serviceSet, getServiceText},
};
const MItem setItems[] = {
	{"Speed: ", speedSet, getSpeedText},
	{"Autoload State: ", autoStateSet, getAutoStateText},
	{"Autosave Settings: ", autoSettingsSet, getAutoSettingsText},
	{"Autopause Game: ", autoPauseGameSet, getAutoPauseGameText},
	{"EWRAM Overclock: ", ewramSet, getEWRAMText},
	{"Autosleep: ", sleepSet, getSleepText},
};
const MItem debugItems[] = {
	{"Debug Output: ", debugTextSet, getDebugText},
	{"Disable Foreground: ", fgrLayerSet, getFgrLayerText},
	{"Disable Background: ", bgrLayerSet, getBgrLayerText},
	{"Disable Sprites: ", sprLayerSet, getSprLayerText},
	{"Step Frame", stepFrame},
};
const MItem fnList9[GAME_COUNT] = {
	{"Black Tiger",quickSelectGame},
	{"Black Tiger (older)",quickSelectGame},
	{"Black Tiger (bootleg set 1)",quickSelectGame},
	{"Black Tiger (bootleg set 2)",quickSelectGame},
	{"Black Dragon (Japan)",quickSelectGame},
	{"Black Dragon (bootleg)",quickSelectGame},
	{"Black Tiger / Black Dragon (mixed bootleg?)",quickSelectGame},
};
const MItem quitItems[] = {
	{"Yes", exitEmulator},
	{"No", backOutOfMenu},
};

const Menu menu0 = MENU_M("", uiNullNormal, dummyItems);
Menu menu1 = MENU_M("Main Menu", uiAuto, mainItems);
const Menu menu2 = MENU_M("File Handling", uiAuto, fileItems);
const Menu menu3 = MENU_M("Controller Settings", uiAuto, ctrlItems);
const Menu menu4 = MENU_M("Display Settings", uiAuto, displayItems);
const Menu menu5 = MENU_M("Dipswitch Settings", uiDipswitches, dipItems);
const Menu menu6 = MENU_M("Other Settings", uiAuto, setItems);
const Menu menu7 = MENU_M("Debug", uiAuto, debugItems);
const Menu menu8 = MENU_M("About", uiAbout, dummyItems);
const Menu menu9 = MENU_M("Load game", uiAuto, fnList9);
const Menu menu10 = MENU_M("Quit Emulator?", uiAuto, quitItems);

const Menu *const menus[] = {&menu0, &menu1, &menu2, &menu3, &menu4, &menu5, &menu6, &menu7, &menu8, &menu9, &menu10 };

char *const ctrlTxt[]   = {"1P", "2P"};
char *const dispTxt[]   = {"Unscaled", "Scaled"};

char *const coinTxt[]   = {
	"1 Coin 1 Credit",  "1 Coin 2 Credits", "1 Coin 3 Credits", "1 Coin 4 Credits",
	"1 Coin 5 Credits", "2 Coins 1 Credit", "3 Coins 1 Credit", "4 Coins 1 Credit"
};
char *const diffTxt[]   = {"Easiest", "Very Easy", "Easy", "Quite Easy", "Normal", "Hard", "Very Hard", "Hardest"};
char *const livesTxt[]  = {"3", "2", "5", "7"};
char *const bonusTxt[]  = {"30K 70K 70K+", "40K 80K 80K+", "50K 100K 100K+", "50K 200K 200K+"};
char *const cabTxt[]    = {"Cocktail", "Upright"};
char *const singleTxt[] = {"Single", "Dual"};


/// This is called at the start of the emulator
void setupGUI() {
	emuSettings = AUTOPAUSE_EMULATION;
//	keysSetRepeat(25, 4);	// Delay, repeat.
	menu1.itemCount = ARRSIZE(mainItems) - (enableExit?0:1);
	closeMenu();
}

/// This is called when going from emu to ui.
void enterGUI() {
	setPaletteCount(14);
}

/// This is called going from ui to emu.
void exitGUI() {
	if (gDebugSet) {
		setPaletteCount(15);
	}
	else {
		setPaletteCount(16);
	}
}

void quickSelectGame() {
	while (loadGame()) {
		redrawUI();
		return;
	}
	closeMenu();
}

void uiNullNormal() {
	uiNullDefault();
}

void uiAbout() {
	setupSubMenuText();
	drawText("Select:   Insert coin",3);
	drawText("Start:    Start button",4);
	drawText("DPad:     Move character",5);
	drawText("Up:       Climb up",6);
	drawText("Down:     Crouch/climb down",7);
	drawText("B:        Attack",8);
	drawText("A:        Jump",9);

	drawText("BlackTgrGBA " EMUVERSION, 17);
	drawText("ARMZ80      " ARMZ80VERSION, 18);
	drawText("BlkTgrVideo " BTVIDEOVERSION, 19);
}

void uiDipswitches() {
	char s[10];
	uiAuto();

	setMenuItemRow(15);
	int2Str(coinCounter0, s);
	drawSubItem("CoinCounter1:       ", s);
	int2Str(coinCounter1, s);
	drawSubItem("CoinCounter2:       ", s);
}

void nullUINormal(int key) {
}

void nullUIDebug(int key) {
}

void resetGame() {
	loadCart(0,0);
}


//---------------------------------------------------------------------------------
/// Switch between Player 1 & Player 2 controls
void controllerSet() {					// See io.s: refreshEMUjoypads
	joyCfg ^= 0x20000000;
}
const char *getControllerText() {
	return ctrlTxt[(joyCfg>>29)&1];
}

/// Swap A & B buttons
void swapABSet() {
	joyCfg ^= 0x400;
}
const char *getSwapABText() {
	return autoTxt[(joyCfg>>10)&1];
}

/// Turn on/off scaling
void scalingSet(){
	gScaling ^= 0x01;
	refreshGfx();
}
const char *getScalingText() {
	return dispTxt[gScaling];
}

/// Change gamma (brightness)
void gammaChange() {
	gammaSet();
	paletteInit(gGammaValue);
	paletteTxAll();					// Make new palette visible
	setupMenuPalette();
}

/// Turn on/off rendering of foreground
void fgrLayerSet() {
	gGfxMask ^= 0x01;
}
const char *getFgrLayerText() {
	return autoTxt[gGfxMask&1];
}
/// Turn on/off rendering of background
void bgrLayerSet() {
	gGfxMask ^= 0x02;
}
const char *getBgrLayerText() {
	return autoTxt[(gGfxMask>>1)&1];
}
/// Turn on/off rendering of sprites
void sprLayerSet() {
	gGfxMask ^= 0x10;
}
const char *getSprLayerText() {
	return autoTxt[(gGfxMask>>4)&1];
}


/// Number of coins for credits
void coinASet() {
	int i = (gDipSwitch0+1) & 0x7;
	gDipSwitch0 = (gDipSwitch0 & ~0x7) | i;
}
const char *getCoinAText() {
	return coinTxt[gDipSwitch0 & 0x7];
}
/// Number of coins for credits
void coinBSet() {
	int i = (gDipSwitch0+0x08) & 0x38;
	gDipSwitch0 = (gDipSwitch0 & ~0x38) | i;
}
const char *getCoinBText() {
	return coinTxt[(gDipSwitch0>>3) & 0x7];
}
/// Game difficulty
void difficultSet() {
	int i = (gDipSwitch1+0x04) & 0x1C;
	gDipSwitch1 = (gDipSwitch1 & ~0x1C) | i;
}
const char *getDifficultText() {
	return diffTxt[(gDipSwitch1>>2)&7];
}
/// Allow continue
void continueSet() {
	gDipSwitch1 ^= 0x40;
}
const char *getContinueText() {
	return autoTxt[(~gDipSwitch1>>6)&1];
}
/// Cocktail/upright
void cabinetSet() {
	gDipSwitch1 ^= 0x80;
}
const char *getCabinetText() {
	return cabTxt[(gDipSwitch1>>7)&1];
}
/// Number of lifes to start with
void livesSet() {
	int i = (gDipSwitch1+1) & 3;
	gDipSwitch1 = (gDipSwitch1 & ~3) | i;
}
const char *getLivesText() {
	return livesTxt[gDipSwitch1 & 3];
}
/// Demo sound on/off
void demoSet() {
	gDipSwitch1 ^= 0x20;
}
const char *getDemoText() {
	return autoTxt[(~gDipSwitch1>>5)&1];
}
/// Flip screen
void flipSet() {
	gDipSwitch0 ^= 0x40;
}
const char *getFlipText() {
	return autoTxt[(gDipSwitch0>>6)&1];
}
/// Test/Service mode
void serviceSet() {
	gDipSwitch0 ^= 0x80;
}
const char *getServiceText() {
	return autoTxt[(gDipSwitch0>>7)&1];
}
