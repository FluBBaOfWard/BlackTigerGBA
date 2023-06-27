#include <gba.h>

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/dir.h>

#include "FileHandling.h"
#include "Shared/EmuMenu.h"
#include "Shared/EmuSettings.h"
#include "Emubase.h"
#include "Main.h"
#include "Gui.h"
#include "BlackTiger.h"
#include "Cart.h"
#include "Gfx.h"
#include "io.h"

static const char *const folderName = "acds";
static const char *const settingName = "settings.cfg";

configdata cfg;
static int selectedGame = 0;

static bool loadRoms(int gamenr, bool doLoad);

#define GAMECOUNT (6)

//---------------------------------------------------------------------------------
int loadSettings() {
	g_dipSwitch0 = cfg.dipSwitch0;
	g_dipSwitch1 = cfg.dipSwitch1;
	g_dipSwitch2 = cfg.dipSwitch2;
	gScaling     = cfg.scaling&1;
	gFlicker     = cfg.flicker&1;
	gGammaValue  = cfg.gammaValue;
	emuSettings  = cfg.emuSettings & ~EMUSPEED_MASK; // Clear speed setting.
	sleepTime    = cfg.sleepTime;
	joyCfg       = (joyCfg&~0x400)|((cfg.controller&1)<<10);
//	strlcpy(currentDir, cfg.currentPath, sizeof(currentDir));

	infoOutput("Settings loaded.");
	return 0;
}
void saveSettings() {
	strcpy(cfg.magic,"cfg");
	cfg.dipSwitch0  = g_dipSwitch0;
	cfg.dipSwitch1  = g_dipSwitch1;
	cfg.dipSwitch2  = g_dipSwitch2;
	cfg.scaling     = gScaling&1;
	cfg.flicker     = gFlicker&1;
	cfg.gammaValue  = gGammaValue;
	cfg.emuSettings = emuSettings & ~EMUSPEED_MASK; // Clear speed setting.
	cfg.sleepTime   = sleepTime;
	cfg.controller  = (joyCfg>>10)&1;
//	strlcpy(cfg.currentPath, currentDir, sizeof(currentDir));

	infoOutput("Settings saved.");
}

int loadNVRAM() {
	return 0;
}

void saveNVRAM() {
}

void loadState(void) {
	unpackState(testState);
	infoOutput("Loaded state.");
}
void saveState(void) {
	packState(testState);
	infoOutput("Saved state.");
}
//---------------------------------------------------------------------------------
bool loadGame() {
	if (loadRoms(selected, false)) {
		return true;
	}
	selectedGame = selected;
	loadRoms(selectedGame, true);
	setEmuSpeed(0);
	loadCart(selectedGame,0);
	if (emuSettings & 4) {
		loadState();
	}
	return false;
}

bool loadRoms(int game, bool doLoad) {
//	int i, j, count;
//	bool found;
//	u8 *romArea = ROM_Space;
//	FILE *file;

//	count = fileCount[game];
/*
	chdir("/");			// Stupid workaround.
	if (chdir(currentDir) == -1) {
		return true;
	}

	for (i=0; i<count; i++) {
		found = false;
		if ( (file = fopen(romFilenames[game][i], "r")) ) {
			if (doLoad) {
				fread(romArea, 1, romFilesizes[game][i], file);
				romArea += romFilesizes[game][i];
			}
			fclose(file);
			found = true;
		} else {
			for (j=0; j<GAMECOUNT; j++) {
				if ( !(findFileInZip(gameZipNames[j], romFilenames[game][i])) ) {
					if (doLoad) {
						loadFileInZip(romArea, gameZipNames[j], romFilenames[game][i], romFilesizes[game][i]);
						romArea += romFilesizes[game][i];
					}
					found = true;
					break;
				}
			}
		}
		if (!found) {
			infoOutput("Couldn't open file:");
			infoOutput(romFilenames[game][i]);
			return true;
		}
	}
*/
	return false;
}
