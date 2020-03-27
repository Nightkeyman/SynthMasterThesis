/*
 * midi_fifo.c
 *
 *  Created on: 27 mar 2020
 *      Author: Jan
 */
#include "midi_fifo.h"

#define MIDI_buff_length 3
volatile unsigned char MIDI_buff[MIDI_buff_length] = {{0}};
unsigned char MIDI_buff_iterator = 0;

void MIDI_push(unsigned char data){ // 600 nanoseconds
	MIDI_buff_iterator++;
    if (MIDI_buff_iterator >= MIDI_buff_length)
    	MIDI_buff_iterator = 0;
    MIDI_buff[MIDI_buff_iterator] = data;
}

unsigned char MIDI_pull(char offset){

	int index = 0;
	if (MIDI_buff_iterator + offset >= 0)
		index = MIDI_buff_iterator + offset ;
	else
		index = MIDI_buff_length + MIDI_buff_iterator + offset;
	return MIDI_buff[index];

}
void MIDI_clear(){
	unsigned char i = 0;
	for (i = 0; i < MIDI_buff_length; i++)
		MIDI_buff[i] = 0;
}


