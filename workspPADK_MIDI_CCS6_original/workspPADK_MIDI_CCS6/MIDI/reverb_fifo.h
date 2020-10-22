/*
 * reverb_fifo.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Jakub
 */

#ifndef REVERB_FIFO_H_
#define REVERB_FIFO_H_

#define reverb_buff_length 3001
// push to fifo queue
void reverb_push(float data);

// pull from fifo queue
float reverb_pull(int offset);

// clear fifo queue
void reverb_clear();


#endif /* REVERB_FIFO_H_ */
