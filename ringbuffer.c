/*
 * ringbuffer.c
 *
 *  Created on: Jun 23, 2021
 *      Author: ROJEK
 */

#include "ringbuffer.h"

RB_Status RB_Read(Ringbuffer_t *buffer, uint8_t *value)
{
	if(buffer->Head == buffer->Tail)
	{
		return RB_ERROR;
	}

	*value = buffer->buffer[buffer->Tail];

	buffer->Tail = (buffer->Tail + 1) % RING_BUFFER_SIZE;

	return RB_OK;
}

RB_Status RB_Write(Ringbuffer_t *buffer, uint8_t value)
{

	uint16_t HeadTmp;
	HeadTmp = (buffer->Head + 1) % RING_BUFFER_SIZE;

	if (HeadTmp == buffer->Tail)
	{
		return RB_ERROR;
	}

	buffer->buffer[buffer->Head] = value;
	buffer->Head = HeadTmp;

	return RB_OK;
}

void RB_Flush(Ringbuffer_t *buffer)
{
	buffer->Head = 0;
	buffer->Tail = 0;
}
