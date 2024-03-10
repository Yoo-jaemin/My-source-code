
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "buffer.h"

void buffer_init(s_Queue* queue)
{
	queue->size = MAX_QUEUE_SIZE;
	queue->read_pos  = 0;
	queue->write_pos = 0;
}

void buffer_en_queue(s_Queue* queue, uint8_t ch)
{
	queue->buffer[queue->write_pos] = ch;
	queue->write_pos = (++queue->write_pos)%MAX_QUEUE_SIZE;
}

// for ascii
uint8_t buffer_de_queue(s_Queue* queue)
{
	uint8_t ch = 0;
	if (queue->read_pos == queue->write_pos)
		return ch;
    else {
		ch = queue->buffer[queue->read_pos];
		queue->read_pos = (++queue->read_pos)%MAX_QUEUE_SIZE;
	}
	return ch;
}

// for binary
bool buffer_de_queue_bool(s_Queue* queue, uint8_t* ch)
{
   	if (queue->read_pos == queue->write_pos)
        return false;
    else {
        *ch = queue->buffer[queue->read_pos];
        queue->read_pos = (++queue->read_pos)%MAX_QUEUE_SIZE;
    }
    return true;
}
