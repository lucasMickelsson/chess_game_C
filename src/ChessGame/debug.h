#ifndef DEBUGH
#define DEBUGH

#ifdef DEBUGON
#define DEBUG(msg) printf("DEBUG: %s\n", msg)
#else
#define DEBUG(msg)
#endif // DEBUGON

#endif // DEBUGH