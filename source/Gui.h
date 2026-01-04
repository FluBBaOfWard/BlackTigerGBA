#ifndef GUI_HEADER
#define GUI_HEADER

#ifdef __cplusplus
extern "C" {
#endif

void setupGUI(void);
void enterGUI(void);
void exitGUI(void);
void quickSelectGame(void);
void nullUINormal(int key);
void nullUIDebug(int key);
void resetGame(void);

void uiNullNormal(void);
void uiDipswitches(void);
void uiAbout(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GUI_HEADER
