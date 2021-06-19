const char * instruction_string[] = {
"lui",
"auipc",
"jal",
"jalr",
"beq",
"bne",
"blt",
"bge",
"bltu",
"bgeu",
"lb",
"lh",
"lw",
"lbu",
"lhu",
"sb",
"sh",
"sw",
"addi",
"slti",
"sltiu",
"xori",
"ori",
"andi",
"slli",
"srli",
"srai",
"add",
"sub",
"sll",
"slt",
"sltu",
"xor",
"srl",
"sra",
"or",
"and",
"fence",
"ecall",
"ebreak",
"lwu",
"ld",
"sd",
"slli",
"srli",
"srai",
"addiw",
"slliw",
"srliw",
"sraiw",
"addw",
"subw",
"sllw",
"srlw",
"sraw",
"mul",
"mulh",
"mulhsu",
"mulhu",
"div",
"divu",
"rem",
"remu",
"mulw",
"divw",
"divuw",
"remw",
"remuw",
};



const uint8_t instruction_argument_count[] = {
2,
2,
2,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
2,
0,
0,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3
};
