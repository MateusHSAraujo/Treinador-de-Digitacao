/*
 * song.c
 *
 *  Created on: Aug 8, 2023
 *      Author: mateu
 */
#include "stdint.h"
#include "song.h"
#include "TPM.h"
#include "derivative.h"


static uint16_t victoryFanfare_notes[]={ C_6 , C_6 , C_6 , C_6 , G_5S , A_5S , C_6 , 0 , A_5S, C_6};
static uint8_t victoryFanfare_ticks[]={          1  , 1 ,  2    , 2 ,    2  ,  1 ,   1  , 1 ,  3 };

static uint16_t winnerSong_notes[]={G_4, C_5 , E_5 , G_5 , C_6 , E_6 , G_6 , E_6 , G_4S , C_5  , D_5S , G_5S , C_6 , D_6S , G_6S , D_6S , A_4S , D_5, F_5, A_5S, D_6 , F_6 , A_6S , A_6S , A_6S , A_6S, C_7 };
static uint8_t winnerSong_ticks[]={       1  ,  1  ,  1  ,  1 ,   1  ,  2 ,   2  ,  1   ,  1   ,  1   ,  1   ,  1  ,   1  ,  2   ,   2  ,  1   ,  1 ,  1,   1 ,  1  ,  1  ,  2   ,  1   ,  1   ,  1   ,   3  };

static uint16_t looserSong_notes[]={ C_6 , G_5 , E_5 , A_5 , B_5 , A_5 , G_5S , A_5S , G_5S, G_5 , F_5, G_5};
static uint8_t looserSong_ticks[]={          3  , 2 ,  2    , 2 ,    2  ,  2 ,   2  ,   2  ,  1  ,  1 ,  3 };


void initSong(Song_type* song, musicas_disponiveis selected){
	
	switch (selected){
		case VICTORY_FANFARE:
			song->notes = victoryFanfare_notes;
			song->ticks = victoryFanfare_ticks;
			song->noteToPlay = 0;
			song->lastNoteIdx = 9;
			song->mod=21800;
			song->fstTick = 1;
			break;
		
		case WINNER_SONG:
			song->notes = winnerSong_notes;
			song->ticks = winnerSong_ticks;
			song->noteToPlay = 0;
			song->lastNoteIdx = 26;
			song->mod=21845;
			song->fstTick = 1;
			break;
		
		case LOOSER_SONG:
			song->notes = looserSong_notes;
			song->ticks = looserSong_ticks;
			song->noteToPlay = 0;
			song->lastNoteIdx = 11;
			song->mod=21845;
			song->fstTick = 3;
			break;	
		
		default:
			break;
	}
	return;
	
}


uint8_t adjustTick (Song_type *song){
	uint8_t idx = song->noteToPlay;
	if (idx==song->lastNoteIdx) return 1;
	return song->ticks[idx];
}

int8_t nextNote (Song_type *song){
	if (song->noteToPlay > song->lastNoteIdx){
		TPM_config_especifica (1, 1489, 0b1111, 0, 0, 0, 0, 0, 0b101);
		TPM_CH_config_especifica (1, 1, 0b0000, 0);	
		TPM_config_especifica (0, 40960, 0b1111, 0, 0, 0, 0, 0, 0b111);
		return -1;
	}
	
	uint16_t noteFreq = song->notes[song->noteToPlay];
	uint8_t tick = adjustTick(song); 
	TPM_config_especifica (0, (song->mod)*tick, 0b1111, 0, 0, 0, 0, 0, 0b111);
	TPM_CH_config_especifica (0, 0, 0b0111, TPM0_CNT);
	
	if (noteFreq!=0){
		uint16_t mod1 = 20971520 / (noteFreq * 32);
		TPM_config_especifica (1, mod1, 0b1111, 0, 0, 0, 0, 0, 0b101);
		TPM_CH_config_especifica (1, 1, 0b1010, mod1/2); //MS_ELS = 1010 -> EPWM high true
	} else {
		TPM_CH_config_especifica (1, 1, 0b0000, 0); 
	}
	song->noteToPlay++;
	return 0;
}

