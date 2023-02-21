#ifndef ENSIVIDEO_H
#define ENSIVIDEO_H

#include <stdbool.h>
#include <ogg/ogg.h>
#include <theora/theora.h>
#include <theora/theoradec.h>
#include <vorbis/codec.h>
#include "uthash.h"

enum streamtype { TYPE_UNKNOW, TYPE_THEORA, TYPE_VORBIS };

struct theora_decode {
    th_info info;
    th_comment comment;
    th_setup_info *setup;
    th_dec_ctx *ctx;
};

struct vorbis_decode {
    vorbis_info info;
    vorbis_comment comment;
    vorbis_dsp_state dsp;
    vorbis_block block;
};

struct streamstate {
    int serial; // numéro du stream, utile pour le hash
    ogg_stream_state strstate; // automate de décodage du stream
    enum streamtype strtype;
    ogg_packet packet; // packet extrait du stream
    int nbpacket; // nb de packet complet extrait du stream
    int nbpacketoutsync; // nb de packet complet extrait du stream
    bool headersRead;
    struct theora_decode th_dec;
    struct vorbis_decode vo_dec;
    UT_hash_handle hh;
};


#endif
