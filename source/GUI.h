#ifndef GUI_HEADER
#define GUI_HEADER

#ifdef __cplusplus
extern "C" {
#endif

extern u8 gGammaValue;

void setupGUI(void);
void enterGUI(void);
void exitGUI(void);
void quickSelectGame(void);
void nullUINormal(int key);
void nullUIDebug(int key);
void resetGame(void);

void uiNullNormal(void);
void uiMainMenu(void);
void uiFile(void);
void uiSettings(void);
void uiController(void);
void uiDisplay(void);
void uiDipswitches(void);
void uiAbout(void);
void uiLoadGame(void);

void controllerSet(void);
void swapABSet(void);

void scalingSet(void);
void gammaSet(void);
void fgrLayerSet(void);
void bgrLayerSet(void);
void sprLayerSet(void);

void coinASet(void);
void coinBSet(void);
void difficultSet(void);
void continueSet(void);
void cabinetSet(void);
void livesSet(void);
void demoSet(void);
void flipSet(void);
void serviceSet(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GUI_HEADER
