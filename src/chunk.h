#ifndef QED_CHUNK_H
#define QED_CHUNK_H

#include "common.h"
#include "value.h"

// Operation codes
// Our bytecode instructions
typedef enum {
	OP_CONSTANT,
	OP_RETURN,
} OpCode;

// An array of instructions
// This is where instructions for a program are stored
typedef struct {
	int count;
	int capacity;
	uint8_t *code;
	ValueArray constants;
} Chunk;

void init_chunk(Chunk *chunk);
void free_chunk(Chunk *chunk);
void write_chunk(Chunk *chunk, uint8_t byte);
int add_constant(Chunk *chunk, Value constant);

#endif