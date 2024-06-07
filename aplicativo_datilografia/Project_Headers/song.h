/*
 * song.h
 *
 *  Created on: Aug 8, 2023
 *      Author: mateu
 */

#ifndef SONG_H_
#define SONG_H_

#include "stdint.h"

#define C_7 2093
#define C_6	1046
#define C_5	523
#define G_6S 1661
#define G_6	1567
#define G_5S 831
#define G_5	784
#define G_4	392
#define G_4S 415
#define A_5 880
#define A_5S 932
#define A_6S 1864
#define A_4S 466
#define E_6 1318
#define E_5 659
#define D_5S 622
#define D_5 587
#define D_6S 1244
#define D_6 1175
#define F_5 698
#define F_6 1398
#define B_5 988

typedef struct SongTag
{
	uint16_t* notes;  	 //<! buffer de dados
	uint8_t* ticks;
	uint8_t noteToPlay ;       
	uint8_t lastNoteIdx;
	uint16_t mod;
	uint8_t fstTick;
} Song_type;

typedef enum songsTag{
	VICTORY_FANFARE,
	WINNER_SONG,
	LOOSER_SONG
} musicas_disponiveis;

void initSong(Song_type* song, musicas_disponiveis selected);
uint8_t adjustTick (Song_type *song);
int8_t nextNote (Song_type *song);
#endif /* SONG_H_ */
