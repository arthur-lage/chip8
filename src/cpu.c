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
                    cpu->PC = cpu->stack[cpu->SP];
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
                        cpu->V[0xF] = 1;
                        cpu->V[x] = cpu->V[x] + cpu->V[y];
                    }
                    break;
                case 0x8005:
                    if(cpu->V[x] > cpu->V[y]) {
                        cpu->V[0xF] = 1;
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
                        cpu->V[0xF] = 1;
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
        case 0x9000:
            if (cpu->V[x] != cpu->V[y]) {
                cpu->PC += 2;
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
        case 0xD000:
            // TO DO
            break;
        case 0xE000:
            switch(opcode & 0xF0FF) {
                case 0xE09E:
                    if(cpu->keypad[cpu->V[x]] == 1) {
                        cpu->PC += 2;
                    }
                    break;
                case 0xE0A1:
                    if(cpu->keypad[cpu->V[x]] != 1) {
                        cpu->PC += 2;
                    }
                    break;
            }
            break;
        case 0xF000:
            switch(opcode & 0xF0FF) {
                case 0xF007:
                    cpu->V[x] = cpu->delay_timer;
                    break;
                case 0xF00A:
                    // to do wait for key press
                    break;
                case 0xF015:
                    cpu->delay_timer = cpu->V[x];
                    break;
                case 0xF018:
                    cpu->sound_timer = cpu->V[x];
                    break;
                case 0xF01E:
                    cpu->I += cpu->V[x];
                    break;
                case 0xF029:
                    // to do set vx to digit
                    break;
                case 0xF033:
                    cpu->memory[cpu->I] = cpu->V[x] / 100;
                    cpu->memory[cpu->I+1] = (cpu->V[x] / 10) % 10;
                    cpu->memory[cpu->I+2] = cpu->V[x] % 10;
                    break;
                case 0xF055:
                    for (int i = 0; i< x; i++) {
                        cpu->memory[cpu->I + i] = cpu->V[i];
                    }
                    break;
                case 0xF065:
                    for(int i = 0; i < x; i++) {
                        cpu->V[i] = cpu->memory[cpu->I + i];
                    }
                    break;
            }
            break;
        default:
            printf("Opcode desconhecido: %04X\n", opcode);
    }
}