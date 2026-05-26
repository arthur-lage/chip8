# CHIP-8 Emulator

A CHIP-8 emulator written in C from scratch, built as a learning project to understand how emulators and low-level computer architecture work.

### Features

- Full CHIP-8 instruction set implementation
- SDL3 rendering
- Keyboard input mapping
- ROM loading support

### Building

Requires w64devkit and SDL3.

```bash
make
./emulator.exe roms/pong.ch8
```

### References

- [Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#0.1)