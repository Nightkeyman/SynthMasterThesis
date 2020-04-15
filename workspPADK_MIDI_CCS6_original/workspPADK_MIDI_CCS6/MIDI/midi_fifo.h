/*
 * midi_fifo.h
 *
 *  Created on: 27 mar 2020
 *      Author: Jan
 */

#ifndef MIDI_FIFO_H_
#define MIDI_FIFO_H_

// push to fifo queue
void MIDI_push(unsigned char data);

// pull from fifo queue
unsigned char MIDI_pull(char offset);

// clear fifo queue
void MIDI_clear();

#endif /* MIDI_FIFO_H_ */
