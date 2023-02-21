#ifndef THEORA_H
#define THEORA_H

#include <ogg/ogg.h>
#include <SDL2/SDL.h>
#include "ensivideo.h"

#define NBTEX 30

struct TextureDate {
    unsigned char *plane[3]; // copy of plane are contiguous, thus
			     // stride is width
    double timems; // expiration date of the frame, in ms
};


extern struct streamstate *theorastrstate;

void *draw2SDL(void *arg);
void theora2SDL(struct streamstate *s);

extern int windowsx;
extern int windowsy;

#endif
