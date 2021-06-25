
void generate_machine_code(char *input, size_t word_count, size_t *word_start, size_t *word_end, intmax_t *number, size_t instructions_in_code, size_t *instruction, size_t *which_instruction, size_t function_count, function *symbol_table[], size_t line_count, size_t *line, size_t actual_instruction_count, uint32_t *machine_code){
 

 //uint32_t machine_code[actual_instruction_count];
 size_t current_number = 0;
 size_t current_line = 1;
 size_t instruction_offset = 0;
 function *which_function;
 for(size_t i = 0; i < instructions_in_code; i++){
  if(current_line < line_count && word_start[instruction[i]] >= line[current_line]){
   current_line++;
  }
  switch(which_instruction[i]){
   case 0:/* lui */
    if(number[current_number] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 55 | ((number[current_number] & 0x1F) << 6) | (number[current_number + 1] & 0xFFFFF000);
    current_number += 2;
    break;
   case 1:/* auipc */
    if(number[current_number] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 23 | ((number[current_number] & 0x1F) << 6) | (number[current_number + 1] & 0xFFFFF000);
    current_number += 2;
    break;
   case 2:/* jal */
    if(number[current_number] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 111 | ((number[current_number] & 0x1F) << 6) | (number[current_number + 1] & 0xFF000) | ((number[current_number + 1] & 2048) << 9) | ((number[current_number + 1] & 0x7FE) << 11) | ((number[current_number + 1] & 0x100000) << 11);
    current_number += 2;
    break;
   case 3:/* jalr */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 23 | ((number[current_number] & 0x1F) << 6) | (0 << 11) | ((number[current_number + 1] & 0x1F) << 14)| ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 4:/* beq */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    break;
   case 5:/* bne */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    break;
   case 6:/* blt */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    break;
   case 7:/* bge */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    break;
   case 8:/* bltu */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0x6 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    break;
   case 9:/* bgeu */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0x7 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    break;
   case 10:/* lb */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 3 | ((number[current_number] & 0x1F) << 6) | (0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 11:/* lh */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 3 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 12:/* lw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 3 | ((number[current_number] & 0x1F) << 6) | (0x2 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 13:/* lbu */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 3 | ((number[current_number] & 0x1F) << 6) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 14:/* lhu */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 3 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 15:/* sb */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0xFE0) << 19);
    current_number += 3;
    break;
   case 16:/* sh */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0xFE0) << 19);
    current_number += 3;
    break;
   case 17:/* sw */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x2 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0xFE0) << 19);
    current_number += 3;
    break;
   case 18:/* addi */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 19:/* slti */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x2 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 20:/* sltiu */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x3 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 21:/* xori */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 22:/* ori */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x6 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 23:/* andi */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x7 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 24:/* slli */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 25:/* srli */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 26:/* srai */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x20 << 24);
    current_number += 3;
    break;
   case 27:/* add */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 28:/* sub */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x20 << 24);
    current_number += 3;
    break;
   case 29:/* sll */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 30:/* slt */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x2 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 31:/* sltu */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x3 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 32:/* xor */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 33:/* srl */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 34:/* sra */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x20 << 24);
    current_number += 3;
    break;
   case 35:/* or */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x6 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 36:/* and */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x7 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 37:/* fence */ 
    machine_code[i + instruction_offset] = 0xF | (0 << 6) | (0xFF << 19) | (0 << 27);
    break;
   case 38:/* ecall */
    machine_code[i + instruction_offset] = 115;
    break;
   case 39:/* ebreak */
    machine_code[i + instruction_offset] = 1048691;
    break;
   case 40:/* lwu */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 3 | ((number[current_number] & 0x1F) << 6) | (0x6 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 41:/* ld */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 3 | ((number[current_number] & 0x1F) << 6) | (0x3 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 42:/* sd */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x3 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0xFE0) << 19);
    current_number += 3;
    break;
   case 43:/* slli */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 19 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x3F) << 19) | (0x0 << 25);
    current_number += 3;
    break;
   case 44:/* srli */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 19 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x3F) << 19) | (0x0 << 25);
    current_number += 3;
    break;
   case 45:/* srai */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 19 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x3F) << 19) | (0x10 << 25);
    current_number += 3;
    break;
   case 46:/* addiw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 27 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    break;
   case 47:/* slliw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 27 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 48:/* srliw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 27 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 49:/* sraiw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 27 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x20 << 24);
    current_number += 3;
    break;
   case 50:/* addw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 59 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 51:/* subw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 59 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x20 << 24);
    current_number += 3;
    break;
   case 52:/* sllw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 59 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 53:/* srlw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 59 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    break;
   case 54:/* sraw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 59 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x20 << 24);
    current_number += 3;
    break;
   case 55:/* mul */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 56:/* mulh */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 57:/* mulhsu */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x2 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 58:/* mulhu */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x3 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 59:/* div */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 60:/* divu */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 61:/* rem */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x6 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 62:/* remu */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 51 | ((number[current_number] & 0x1F) << 6) | (0x7 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 63:/* mulw */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 59 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 64:/* divw */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 59 | ((number[current_number] & 0x1F) << 6) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 65:/* divuw */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 59 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 66:/* remw */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 59 | ((number[current_number] & 0x1F) << 6) | (0x6 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 67:/* remuw */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 59 | ((number[current_number] & 0x1F) << 6) | (0x7 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x1 << 24);
    current_number += 3;
    break;
   case 68:/* call */
    which_function = lookup_function(input, symbol_table, function_count, word_start[instruction[i] + 1], word_end[instruction[i] + 1]);
    if(which_function->index > instruction[i]){
     if(which_function->index == (word_count - 1)){
      if(i == (instructions_in_code - 1)){
       machine_code[i + instruction_offset] = 23 | (0x1 << 6) | (0 & 0xFFFFF000);
       machine_code[i + instruction_offset + 1] = 23 | (0x1 << 6) | (0 << 11) | (0x1 << 14) | ((0 & 0xFFF) << 19);
      }else{
       for(size_t j = i; j < instructions_in_code; j++){
        machine_code[i + instruction_offset] = 23 | (0x1 << 6) | (((j - i) * 4) & 0xFFFFF000);
        machine_code[i + instruction_offset + 1] = 23 | (0x1 << 6) | (0 << 11) | (0x1 << 14) | ((((j - i) * 4) & 0xFFF) << 19);
       }
      }
     } else{
       size_t next_instruction_position = 0;
       while(instruction[next_instruction_position] < which_function->index){
        next_instruction_position++;
       }
       machine_code[i + instruction_offset] = 23 | (0x1 << 6) | (((next_instruction_position - i) * 4) & 0xFFFFF000);
       machine_code[i + instruction_offset + 1] = 23 | (0x1 << 6) | (0 << 11) | (0x1 << 14) | ((((next_instruction_position - i) * 4) & 0xFFF) << 19);
     }
    } else {
     size_t next_instruction_position = 0;
     while(instruction[next_instruction_position] < which_function->index){
      next_instruction_position++;
     }
     machine_code[i + instruction_offset] = 23 | (0x1 << 6) | (((i - next_instruction_position) * -4) & 0xFFFFF000);
     machine_code[i + instruction_offset + 1] = 23 | (0x1 << 6) | (0 << 11) | (0x1 << 14) | ((((i - next_instruction_position) * -4) & 0xFFF) << 19);
    }
    actual_instruction_count++;
    instruction_offset++;
    break;
   case 69:/* nop */
    machine_code[i + instruction_offset] = 19;
    break;
   case 70:/* not */
    if(number[current_number] > 31|| number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | (0xFFE << 19);
    current_number += 2;
    break;
   case 71:/* mv */
    if(number[current_number] > 31|| number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
     }
    machine_code[i + instruction_offset] = 35 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | (0x0 << 19);
    current_number += 2;
    break;
  }
 } 
}

