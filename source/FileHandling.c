#include <gba.h>
#include <string.h>

#include "FileHandling.h"
#include "Emubase.h"
#include "Shared/EmuMenu.h"
#include "Shared/EmuSettings.h"
#include "Shared/AsmExtra.h"
#include "Main.h"
#include "Gui.h"
#include "Cart.h"
#include "Gfx.h"
#include "io.h"
#include "BlackTiger.h"

static const char *const folderName = "acds";
static const char *const settingName = "settings.cfg";

EWRAM_BSS int selectedGame = 0;
EWRAM_BSS ConfigData cfg;

static bool loadRoms(int gamenr, bool doLoad);

//---------------------------------------------------------------------------------
void applyConfigData(void) {
	emuSettings  = cfg.emuSettings & ~EMUSPEED_MASK; // Clear speed setting.
	gScaling    = cfg.scaling & SCALED;
	gFlicker    = cfg.flicker & 1;
	gGammaValue = cfg.gammaValue;
	sleepTime   = cfg.sleepTime;
	joyCfg      = (joyCfg & ~0x400) | ((cfg.controller & 1) << 10);
	gDipSwitch0 = cfg.dipSwitch0;
	gDipSwitch1 = cfg.dipSwitch1;
	gDipSwitch2 = cfg.dipSwitch2;
}

void updateConfigData(void) {
	strcpy(cfg.magic, "cfg");
	cfg.emuSettings = emuSettings & ~EMUSPEED_MASK; // Clear speed setting.
	cfg.scaling     = gScaling & SCALED;
	cfg.flicker     = gFlicker & 1;
	cfg.gammaValue  = gGammaValue;
	cfg.sleepTime   = sleepTime;
	cfg.controller  = (joyCfg >> 10) & 1;
	cfg.dipSwitch0  = gDipSwitch0;
	cfg.dipSwitch1  = gDipSwitch1;
	cfg.dipSwitch2  = gDipSwitch2;
}

void initSettings() {
	memset(&cfg, 0, sizeof(ConfigData));
	cfg.emuSettings = AUTOPAUSE_EMULATION | AUTOLOAD_NVRAM;
	cfg.scaling     = SCALED;
	cfg.flicker     = 1;
	cfg.sleepTime   = 60*60*5;
	cfg.dipSwitch1  = 0x80;		// Lives, cabinet & demo sound.

	applyConfigData();
}

int loadSettings() {
	bytecopy_((u8 *)&cfg, (u8 *)SRAM+0x10000-sizeof(ConfigData), sizeof(ConfigData));
	if (strstr(cfg.magic, "cfg")) {
		applyConfigData();
		infoOutput("Settings loaded.");
		return 0;
	}
	else {
		updateConfigData();
		infoOutput("Error in settings file.");
	}
	return 1;
}

void saveSettings() {
	updateConfigData();

	bytecopy_((u8 *)SRAM+0x10000-sizeof(ConfigData), (u8 *)&cfg, sizeof(ConfigData));
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
		if ((file = fopen(romFilenames[game][i], "r"))) {
			if (doLoad) {
				fread(romArea, 1, romFilesizes[game][i], file);
				romArea += romFilesizes[game][i];
			}
			fclose(file);
			found = true;
		}
		else {
			for (j=0; j<GAMECOUNT; j++) {
				if (!(findFileInZip(gameZipNames[j], romFilenames[game][i]))) {
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
