/*
 * reverb_fifo.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Jakub
 */




#include "reverb_fifo.h"

volatile float reverb_buff[reverb_buff_length] = {{0.0}};
int reverb_buff_iterator = 0;

void reverb_push(float data){
	reverb_buff_iterator++;
    if (reverb_buff_iterator >= reverb_buff_length)
    	reverb_buff_iterator = 0;
    reverb_buff[reverb_buff_iterator] = data;
}

float reverb_pull(int offset){

	int index = 0;
	if (reverb_buff_iterator + offset >= 0)
		index = reverb_buff_iterator + offset ;
	else
		index = reverb_buff_length + reverb_buff_iterator + offset;
	return reverb_buff[index];

}
void reverb_clear(){
	unsigned char i = 0;
	for (i = 0; i < reverb_buff_length; i++)
		reverb_buff[i] = 0;
}
