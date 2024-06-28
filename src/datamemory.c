#include <datamemory.h>

uint32_t dmem_load(DataMemory *dmem, uint32_t address, size_t sizeInBytes) {
    uint32_t data = 0;
    for (size_t i = 0; i < sizeInBytes; i++) {
        data |= dmem->mem[address - BASE_ADDRESS + i] << (8 * i);
    }
    return data;
}

void dmem_store(DataMemory *dmem, uint32_t address, int32_t data, size_t sizeInBytes) {
    for (size_t i = 0; i < sizeInBytes; i++) {
        dmem->mem[address - BASE_ADDRESS + i] = (data >> (8 * i)) & 0xFF;
    }
}