#ifndef STREAM_COMMON_H
#define STREAM_COMMON_H

#include "ensivideo.h"

extern bool fini;
extern pthread_t theora2sdlthread;
extern struct timespec datedebut;

int msFromStart();
void pageReader(FILE *vf, ogg_sync_state *pstate, ogg_page *ppage);
struct streamstate *getStreamState(ogg_sync_state *pstate, ogg_page *ppage,
				   enum streamtype type);
int addPageGetPacket(ogg_page *ppage, struct streamstate *s);
int getPacket(struct streamstate *s);
int decodeAllHeaders(int respac, struct streamstate *s, enum streamtype type);

#endif
