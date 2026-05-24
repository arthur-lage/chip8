#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#define SDL_MAIN_HANDLED
#include <SDL3/SDL_main.h>

#include "display.h"
#include "cpu.h"

void loadROM (char* path, uint8_t memory[]) {
    FILE* rom = fopen(path, "rb");
    
    fseek(rom, 0, SEEK_END);
    long size = ftell(rom);
    rewind(rom);

    fread(&memory[0x200], 1, size, rom);
    fclose(rom);
}

int main (int argc, char *argv[]) {
    (void) argc;
    (void) argv;
    
    Display display;
    Chip8 cpu = {0};

    display_init(&display);

    bool isRunning = true;
    SDL_Event event;

    loadROM("roms/pong.ch8", cpu.memory);
    cpu.PC = 0x200;

    while (isRunning) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        // read and execute instruction from memory
        uint16_t opcode = fetch(&cpu);
        execute(&cpu, opcode);
    }

    display_quit(&display);
    
    return 0;
}