/*
 * pressed_keys_fifo.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Jakub
 */

#ifndef PRESSED_KEYS_FIFO_H_
#define PRESSED_KEYS_FIFO_H_

#define MIDI_POLY_MAX 12

// push to fifo queue
void pressedkeys_push(float data);

// pull from fifo queue
float pressedkeys_pull(char offset);

// get the actual index of element from specified offset
unsigned char pressedkeys_index_of(char offset);

// clear fifo queue
void pressedkeys_clear();

// delete note from fifo
int pressedkeys_delete(float freq);

#endif /* PRESSED_KEYS_FIFO_H_ */
