#include <stdint.h>

typedef struct {
    uint8_t memory[4096];
    uint8_t V[16];
    uint16_t I;
    uint16_t PC;
    uint16_t stack[16];
    uint8_t SP;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t keypad[16];
    uint32_t display[64*32];
} Chip8;

uint16_t fetch(Chip8* cpu);
void execute(Chip8 *cpu, uint16_t opcode);