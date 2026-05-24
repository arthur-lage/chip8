#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

uint16_t fetch(Chip8* cpu) {
    if(cpu->PC >= 4094){
        printf("PC out of limits! PC: %04X", cpu->PC);
        exit(1);
    }

    // reads 2 hex and forms the cpu instruction
    uint16_t opcode = cpu->memory[cpu->PC] << 8 | cpu->memory[cpu->PC + 1];

    // moves to the next 2 hex
    cpu->PC += 2;

    return opcode;
}

void execute(Chip8 *cpu, uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t n = (opcode & 0x000F);
    uint8_t kk = (opcode & 0x00FF);
    uint16_t nnn = (opcode & 0x0FFF);

    switch (opcode & 0xF000) {
        case 0x0000:
            switch(opcode) {
                case 0x00E0:
                    // clear display
                    break;
                case 0x00EE:
                    cpu->PC = cpu->stack[SP];
                    cpu->SP -= 1;
                    break;
                }
            break;
        case 0x1000:
            cpu->PC = nnn;
            break;
        case 0x2000:
            cpu->SP += 1;
            cpu->stack[cpu->SP] = cpu->PC;
            cpu->PC = nnn;
            break;
        case 0x3000:
            if(cpu->V[x] == kk) {
                cpu->PC += 2;
            }
            break;
        case 0x4000:
            if(cpu->V[x] != kk) {
                cpu->PC += 2;
            }
            break;
        case 0x5000:
            if(cpu->V[x] == cpu->V[y]){
                cpu->PC += 2;
            }
            break;
        case 0x6000:
            cpu->V[x] = kk;
            break;
        case 0x7000:
            cpu->V[x] = cpu->V[x] + kk;
            break;
        case 0x8000:
            switch (opcode & 0xF00F) {
                case 0x8000:
                    cpu->V[x] = cpu->V[y];
                    break;
                case 0x8001:
                    cpu->V[x] = cpu->V[x] | cpu->V[y];
                    break;
                case 0x8002:
                    cpu->V[x] = cpu->V[x] & cpu->V[y];
                    break;
                case 0x8003:
                    cpu->V[x] = cpu->V[x] ^ cpu->V[y];
                    break;
                case 0x8004:
                    if(cpu->V[x] + cpu->V[y] > 255) {
                        V[0xF] = 1;
                        V[x] = cpu->V[x] + cpu->V[y];
                    }
                    break;
                case 0x8005:
                    if(cpu->V[x] > cpu->V[y]) {
                        cpu->V[0xF] = 1
                    } else {
                        cpu->V[0xF] = 0;
                    }
                    cpu->V[x] = cpu->V[x] - cpu->V[y];
                    break;
                case 0x8006:
                    // to do
                    break;
                case 0x8007:
                    if(cpu->V[y] > cpu->V[x]) {
                        cpu->V[0xF] = 1
                    } else {
                        cpu->V[0xF] = 0;
                    }
                    cpu->V[x] = cpu->V[y] - cpu->V[x];
                    break;
                case 0x800E:
                    // to do
                    break;
            }
            break;
        case 0xA000:
            cpu->I = nnn;
            break;
        case 0xB000:
            cpu->PC = nnn + cpu->V[0];
            break;
        case 0xC000:
            // socorro
            break;
        default:
            printf("Opcode desconhecido: %04X\n", opcode);
    }
}