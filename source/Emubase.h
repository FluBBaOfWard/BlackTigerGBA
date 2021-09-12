#ifndef EMUBASE
#define EMUBASE

typedef struct {				//(config struct)
	char magic[4];				//="CFG",0
	int emuSettings;
	int sleepTime;				// autoSleepTime
	u8 dipSwitch0;				//from cart.s
	u8 dipSwitch1;				//from cart.s
	u8 dipSwitch2;				//from cart.s
	u8 dipSwitch3;				//from cart.s
	u8 scaling;					//from gfx.s
	u8 flicker;					//from gfx.s
	u8 gammaValue;				//from gfx.s
	u8 controller;				//from io.s
	char currentPath[256];
} configdata;

#endif // EMUBASE
