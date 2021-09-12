#ifndef FILEHANDLING_HEADER
#define FILEHANDLING_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#define FILEEXTENSIONS ".zip"

int loadSettings(void);
void saveSettings(void);
int loadNVRAM(void);
void saveNVRAM(void);
void loadState(void);
void saveState(void);
bool loadGame(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // FILEHANDLING_HEADER
