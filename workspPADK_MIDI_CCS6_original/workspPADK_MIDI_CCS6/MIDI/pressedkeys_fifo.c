/*
 * pressedkeys_fifo.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Jakub
 */
#include "pressedkeys_fifo.h"

volatile float pressedkeys_buff[MIDI_POLY_MAX] = {{0.0}};
unsigned char pressedkeys_buff_iterator = 0;

void pressedkeys_mute(float freq) {
	int i = 0;
	for (i = 0; i< MIDI_POLY_MAX; i++) {
		if (pressedkeys_buff[i] >= freq-0.5 && pressedkeys_buff[i] <= freq+0.5) {
			pressedkeys_buff[i] = 0;
			break;
		}
	}
}

int pressedkeys_delete(float freq) {
	int i = 0;
	for (i = 0; i< MIDI_POLY_MAX; i++) {
		if (pressedkeys_buff[i] >= freq-0.5 && pressedkeys_buff[i] <= freq+0.5) {
			return i;
		}
	}
	return -1;
}

void pressedkeys_push(float data){
	pressedkeys_buff_iterator++;
    if (pressedkeys_buff_iterator >= MIDI_POLY_MAX)
    	pressedkeys_buff_iterator = 0;
    pressedkeys_buff[pressedkeys_buff_iterator] = data;
}

float pressedkeys_pull(char offset){

	char index = 0;
	if (pressedkeys_buff_iterator + offset >= 0)
		index = pressedkeys_buff_iterator + offset ;
	else
		index = MIDI_POLY_MAX + pressedkeys_buff_iterator + offset;
	return pressedkeys_buff[index];

}
unsigned char pressedkeys_index_of(char offset){
	char index = 0;
	if (pressedkeys_buff_iterator + offset >= 0)
		index = pressedkeys_buff_iterator + offset ;
	else
		index = MIDI_POLY_MAX + pressedkeys_buff_iterator + offset;
	return index;
}

void pressedkeys_clear(){
	unsigned char i = 0;
	for (i = 0; i < MIDI_POLY_MAX; i++)
		pressedkeys_buff[i] = 0;
}




