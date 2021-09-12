#ifndef BLACKTIGER_HEADER
#define BLACKTIGER_HEADER

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This saves a complete state of the running machine
 * to the statePtr.
 * @param  *statePtr: Where to save the state.
 * @return The size of the state.
 */
int packState(void *statePtr);

/**
 * This loads a complete state of the running machine
 * from the statePtr.
 * @param  *statePtr: Where to load the state from.
 */
void unpackState(const void *statePtr);

/**
 * This returns the total state size of the running machine.
 * @return The size of the state.
 */
int getStateSize(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // BLACKTIGER_HEADER
