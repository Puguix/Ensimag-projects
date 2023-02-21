#include <time.h>
#include <assert.h>
#include "ensivorbis.h"
#include "ensitheora.h"
#include "stream_common.h"
#include "synchro.h"

bool fini = false;


struct timespec datedebut;

int msFromStart() {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, & now);

    return (int)((now.tv_sec - datedebut.tv_sec)*1000.0 +
	      (now.tv_nsec - datedebut.tv_nsec)/1000000.0);
}


void pageReader(FILE *vf, ogg_sync_state *pstate, ogg_page *ppage) {
    // lire une page theora
    int res = ogg_sync_pageout( pstate, ppage);
    char *buffer= NULL;
    assert(res != -1);
    // si une page n'est pas disponible, lire des données dans le fichier
    while(res != 1 && ! fini) {
	buffer = ogg_sync_buffer( pstate, 4096 );
	assert(buffer);
	int bytes = fread( buffer, 1, 4096, vf );
	if (bytes == 0 && feof( vf )) {
	    printf("fin du fichier\n");
	    fini = true;
	    exit(EXIT_FAILURE); // ou juste return ?
	}
	if (bytes > 0)
	    // écriture des données dans l'automate de décodage
	    ogg_sync_wrote( pstate, bytes );
	    
	res = ogg_sync_pageout( pstate, ppage );
    }
    
}

struct streamstate *getStreamState(ogg_sync_state *pstate, ogg_page *ppage,
				   enum streamtype type) {
    // trouver le stream associé à la page ou le construire
    int serial = ogg_page_serialno( ppage );
    int bos = ogg_page_bos( ppage );

    struct streamstate *s= NULL;
    if (bos) { // début de stream
	s = malloc(sizeof(struct streamstate));
	s->serial = serial;
	s->nbpacket = 0;
	s->nbpacketoutsync = 0;
	s->strtype = TYPE_UNKNOW;
	s->headersRead = false;
	int res = ogg_stream_init( & s->strstate, serial );
	th_info_init(& s->th_dec.info);
	th_comment_init(& s->th_dec.comment);
	vorbis_info_init( & s->vo_dec.info);
	vorbis_comment_init( & s->vo_dec.comment);
	assert(res == 0);

	// proteger l'accès à la hashmap

	if (type == TYPE_THEORA)
	    HASH_ADD_INT( theorastrstate, serial, s );
	else
	    HASH_ADD_INT( vorbisstrstate, serial, s );

    } else {
	// proteger l'accès à la hashmap

	if (type == TYPE_THEORA)
	    HASH_FIND_INT( theorastrstate, & serial, s );
	else	
	    HASH_FIND_INT( vorbisstrstate, & serial, s );    

	assert(s != NULL);
    }
    assert(s != NULL);

    return s;
}

int addPageGetPacket(ogg_page *ppage, struct streamstate *s) {

    // ajout de la page dans le stream
    int res = ogg_stream_pagein( & s->strstate, ppage );
    assert(res == 0);
    
    // retirer un packet du stream
    int respac = ogg_stream_packetout( & s->strstate, & s->packet );
    return respac;
}

int getPacket(struct streamstate *s) {
    // retirer un packet du stream
    int respac = ogg_stream_packetout( & s->strstate, & s->packet );
    return respac;
}


/* decode headers and update stream structure */
/* create additional threads if the stream is of the right type */
/* return 1, if the packet is fully handled 
   otherwise return 0;
 */

int decodeAllHeaders(int respac, struct streamstate *s, enum streamtype type) {
    // if the packet is complete, decode it
    if (respac == 1 && (! s->headersRead) &&
	s->strtype != TYPE_VORBIS) {
	// try to detect if the packet contain a theora header
	int res = th_decode_headerin(& s->th_dec.info,
				 & s->th_dec.comment,
				 & s->th_dec.setup,
				 & s->packet);

	if (res != TH_ENOTFORMAT) {
	    // this is a theora
	    if (res > 0 )  {
		// this a theora header
		// there are 3 headers
		s->strtype = TYPE_THEORA;
		// we have finish with the packet
		return 1;
	    }

            // premier packet de données theora
	    // allocation du contexte
	    s->th_dec.ctx = th_decode_alloc(& s->th_dec.info,
					    s->th_dec.setup);
	    assert(s->th_dec.ctx != NULL);
	    assert(s->strtype == TYPE_THEORA);
	    s->headersRead = true;

	    if (type == TYPE_THEORA) {
		// lancement du thread gérant l'affichage (draw2SDL)
	        // inserer votre code ici !!

		assert(res == 0);		     
	    }
	}
    }
    if (respac == 1 && (! s->headersRead)
	&& s->strtype != TYPE_THEORA) {
	int res = vorbis_synthesis_headerin(& s->vo_dec.info,
					& s->vo_dec.comment,
					& s->packet);

	if (res ==  OV_ENOTVORBIS && s->strtype == TYPE_VORBIS) {
	    // first packet
	    res = vorbis_synthesis_init(& s->vo_dec.dsp,
					& s->vo_dec.info);
	    assert(res == 0);
	    res = vorbis_block_init(& s->vo_dec.dsp,
				    & s->vo_dec.block);
	    assert(res == 0);
	    s->headersRead = true;
	} else if (res == 0) {
	    // lecture de l'entete vorbis
	    s->strtype = TYPE_VORBIS;
	    // ce packet a été complètement traitée
	    return 1;
	}
    }
    return 0;
}
