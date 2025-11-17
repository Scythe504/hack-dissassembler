## Hack-Disassembler (hdasm)

A simple Hack machine-code disassembler for the Nand2Tetris computer.
Takes a .hack binary file (16-bit machine instructions) and converts it back into Hack assembly (.asm).

##### Supports:

- A-instructions (@value)

- C-instructions (dest=comp;jump)

- All comp/dest/jump combinations

Clean output compatible with the Hack CPU emulator

### Setup

##### Prerequisites

- CMake (≥ 3.16)
- C++20 capable compiler (g++, clang++, MSVC)
- Ninja (optional)

##### Build

From the project root:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

or with Ninja:

```sh
mkdir build
cd build
cmake -G Ninja ..
ninja
```

This will produce the executable:
```
hdasm
```
##### Usage

Run the disassembler on a .hack file:

```sh
./hdasm Add.hack
```

By default, it outputs to the same filename with .asm extension:

```
Add.hack → Add.asm
```

To specify an output file:

```sh
./hdasm Add.hack -o Add_output.asm
```
### Example

##### Input (Add.hack):
```verilog
0000000000000010
1110110000010000
0000000000000011
1110000010010000
0000000000000000
1110001100001000
```

##### Output (Add.asm):
```verilog
@2
D=A
@3
D=D+A
@0
M=D
```