# RISC-V assembler
A standalone assembler for RISC-V assembly. Currently, the Instruction sets that have been implemented are: RV32I, RV64I, RV32M, RV64M, and the "call", "mv", and "nop" pseudoinstructions. This assembler does not have a linker, it is not made for any specific ABI, and it does not export the symbol table, and does not currently support assembler directives, although each of these should be simple enough to do

## Compiling
All you need is a C compiler and GNU make. Then you do:
```
git clone https://github.com/aslikr42069/RISC_V_assembler.git
cd RISC_V_assembler
make
```
and voila! You will have a binary file called "assemble", which you can use to assemble RISC-V assembly :))
