/*
 * ringbuffer.h
 *
 *  Created on: Jun 23, 2021
 *      Author: ROJEK
 */

#ifndef INC_RINGBUFFER_H_
#define INC_RINGBUFFER_H_
#define RING_BUFFER_SIZE 128

typedef struct{
	uint8_t buffer[RING_BUFFER_SIZE];
	uint16_t Head;
	uint16_t Tail;
}Ringbuffer_t;

typedef enum
{
	RB_OK = 0,
	RB_ERROR = 1
}RB_Status;

RB_Status RB_Write(Ringbuffer_t *buffer, uint8_t value);
RB_Status RB_Read(Ringbuffer_t *buffer, uint8_t *value);
void RB_Flush(Ringbuffer_t *buffer);

#endif /* INC_RINGBUFFER_H_ */
