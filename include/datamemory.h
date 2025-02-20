#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <stdint.h>
#include <stddef.h>

#define MEMORY_SIZE 1024 * 1024 * 1
#define WORD_SIZE 4
#define BASE_ADDRESS 0x00000000

typedef struct DataMemory DataMemory;

struct DataMemory {
    uint8_t mem[MEMORY_SIZE];
    int32_t read_data;
};

uint32_t dmem_load(DataMemory *dmem, uint32_t address, size_t sizeInBytes);
void dmem_store(DataMemory *dmem, uint32_t address, int32_t data, size_t sizeInBytes);

#endif // DATAMEMORY_H