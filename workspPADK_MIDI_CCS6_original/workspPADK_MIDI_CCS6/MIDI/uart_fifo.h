/*
 * uart_fifo.h
 *
 *  Created on: Mar 24, 2020
 *      Author: Jakub
 */

#ifndef UART_FIFO_H_
#define UART_FIFO_H_

#define UART_WAIT       1
#define UART_NO_WAIT    0

#define UART_buff_length 9
volatile unsigned char UART_buff[UART_buff_length] = {{0}};
unsigned char UART_buff_iterator = 0;

void UART_push(unsigned char data);
unsigned char UART_pull(  char offset);
void UART_clear();

void UART_push(unsigned char data){
	UART_buff_iterator++;
    if (UART_buff_iterator >= UART_buff_length)
    	UART_buff_iterator = 0;
    UART_buff[UART_buff_iterator] = data;
}

unsigned char UART_pull(char offset){
	offset = (offset - UART_buff_length + 1);
	int index = 0;
	if (UART_buff_iterator + offset >= 0)
		index = UART_buff_iterator + offset ;
	else
		index = UART_buff_length + UART_buff_iterator + offset;
	return UART_buff[index];

}
void UART_clear(){
	unsigned char i = 0;
	for (i = 0; i < UART_buff_length; i++)
		UART_buff[i] = 0;
}
unsigned char UART_checksum()
{
    return (unsigned char)(UART_pull(1) + UART_pull(2) + UART_pull(3) + UART_pull(4) + UART_pull(5) + UART_pull(6));
}
void UART_send(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4, unsigned char b5, unsigned char b6)
{
	unsigned char suma = (unsigned char)(b1 + b2 + b3 + b4 + b5 + b6);
	unsigned char bytes[UART_buff_length];
	bytes[0] = b0;
	bytes[1] = b1;
	bytes[2] = b2;
	bytes[3] = b3;
	bytes[4] = b4;
	bytes[5] = b5;
	bytes[6] = b6;
	bytes[7] = b0+1;
	bytes[8] = suma;

	//unsigned char bytes[] = { 0, 1,2,3,4,5 };
	UART_Write(bytes, 9, UART_NO_WAIT);
}


#endif /* UART_FIFO_H_ */
