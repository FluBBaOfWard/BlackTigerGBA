#include <gba.h>

#include "BlackTiger.h"
#include "Gfx.h"
#include "BlackTigerVideo/BlackTigerVideo.h"
#include "ARMZ80/ARMZ80.h"


int packState(void *statePtr) {
	int size = blkTgrSaveState(statePtr, &blkTgrVideo_0);
	size += Z80SaveState(statePtr+size, &Z80OpTable);
//	size += Z80SaveState(statePtr+size, &Z80CPU1);
	return size;
}

void unpackState(const void *statePtr) {
	int size = blkTgrLoadState(&blkTgrVideo_0, statePtr);
	size += Z80LoadState(&Z80OpTable, statePtr+size);
//	size += Z80LoadState(&Z80CPU1, statePtr+size);
}

int getStateSize() {
	int size = blkTgrGetStateSize();
	size += Z80GetStateSize();
//	size += Z80GetStateSize();
	return size;
}
