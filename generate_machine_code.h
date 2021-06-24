
uint32_t *generate_machine_code(char *input, size_t word_count, size_t *words[], size_t number_count, ssize_t *number, size_t instructions_in_code, size_t *instruction, size_t *which_instruction, size_t function_count, function *symbol_table[], size_t line_count, size_t *line, size_t actual_instruction_count){
 

 uint32_t machine_code[actual_instruction_count];
 size_t current_number = 0;
 size_t current_line = 1;
 size_t current_instruction = 0;
 for(size_t i = 0; i < actual_instruction_count; i++){
  if(current_line < line_count && words[instruction[current_instruction]][0] >= line[current_line]){
   current_line++;
  }
  switch(which_instruction[current_instruction]){
   case 0:/* lui */
    if(number[current_number] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 55 | ((number[current_number] & 0x1F) << 6) | (number[current_number + 1] & 0xFFFFF000);
    current_number += 2;
    current_instruction++;
    break;
   case 1:/* auipc */
    if(number[current_number] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 23 | ((number[current_number] & 0x1F) << 6) | (number[current_number + 1] & 0xFFFFF000);
    current_number += 2;
    current_instruction++;
    break;
   case 2:/* jal */
    if(number[current_number] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 111 | ((number[current_number] & 0x1F) << 6) | (number[current_number + 1] & 0xFF000) | ((number[current_number + 1] & 2048) << 9) | ((number[current_number + 1] & 0x7FE) << 11) | ((number[current_number + 1] & 0x100000) << 11);
    current_number += 2;
    current_instruction++;
    break;
   case 3:/* jalr */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 23 | ((number[current_number] & 0x1F) << 6) | (0 << 11) | ((number[current_number + 1] & 0x1F) << 14)| ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 4:/* beq */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 5:/* bne */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 6:/* blt */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 7:/* bge */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 8:/* bltu */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0x6 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 9:/* bgeu */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 99 | ((number[current_number] & 2048) >> 5) | ((number[current_number] & 0x1E) << 5) | (0x7 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0x7E0) << 19) | ((number[current_number] & 4096) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 10:/* lb */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 3 | ((number[current_number] & 0x1F) << 6) | (0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 11:/* lh */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 3 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 12:/* lw */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 3 | ((number[current_number] & 0x1F) << 6) | (0x2 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 13:/* lbu */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 3 | ((number[current_number] & 0x1F) << 6) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 14:/* lhu */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 3 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 15:/* sb */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0xFE0) << 19);
    current_number += 3;
    current_instruction++; 
    break;
   case 16:/* sh */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0xFE0) << 19);
    current_number += 3;
    current_instruction++; 
    break;
   case 17:/* sw */
    if(number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x2 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | ((number[current_number] & 0xFE0) << 19);
    current_number += 3;
    current_instruction++; 
    break;
   case 18:/* addi */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++; 
    break;
   case 19:/* slti */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x2 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 20:/* sltiu */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x3 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 21:/* xori */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 22:/* ori */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x6 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 23:/* andi */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x7 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0xFFF) << 19);
    current_number += 3;
    current_instruction++;
    break;
   case 24:/* slli */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 25:/* srli */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 26:/* srai */
    if(number[current_number] > 31 || number[current_number + 1] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 35 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x20 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 27:/* add */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 51 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 28:/* sub */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 51 | ((number[current_number] & 0x1F) << 6) | (0x0 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x20 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 29:/* sll */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 51 | ((number[current_number] & 0x1F) << 6) | (0x1 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 30:/* slt */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 51 | ((number[current_number] & 0x1F) << 6) | (0x2 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 31:/* sltu */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 51 | ((number[current_number] & 0x1F) << 6) | (0x3 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 32:/* xor */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 51 | ((number[current_number] & 0x1F) << 6) | (0x4 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 33:/* srl */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 51 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 34:/* sra */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 51 | ((number[current_number] & 0x1F) << 6) | (0x5 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x20 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 35:/* or */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 51 | ((number[current_number] & 0x1F) << 6) | (0x6 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 36:/* and */
    if(number[current_number] > 31 || number[current_number + 1] > 31 || number[current_number + 2] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 51 | ((number[current_number] & 0x1F) << 6) | (0x7 << 11) | ((number[current_number + 1] & 0x1F) << 14) | ((number[current_number + 2] & 0x1F) << 19) | (0x0 << 24);
    current_number += 3;
    current_instruction++;
    break;
   case 37:/* fence */ 
    machine_code[i] = 0xF | (0 << 6) | (0xFF << 19) | (0 << 27);
    current_instruction++;
    break;
   case 38:/* ecall */
    machine_code[i] = 115;
    break;
   case 39:/* ebreak */
    machine_code[i] = 1048691;
    break;
   case 40:/* lwu */
    break;
   case 41:/* ld */
    break;
   case 42:/* sd */
    break;
   case 43:/* slli */
    break;
   case 44:/* srli */
    break;
   case 45:/* srai */
    break;
   case 46:/* addiw */
    break;
   case 47:/* slliw */
    break;
   case 48:/* srliw */
    break;
   case 49:/* sraiw */
    break;
   case 50:/* addw */
    break;
   case 51:/* subw */
    break;
   case 52:/* sllw */
    break;
   case 53:/* srlw */
    break;
   case 54:/* sraw */
    break;
   case 55:/* mul */
    break;
   case 56:/* mulh */
    break;
   case 57:/* mulhsu */
    break;
   case 58:/* mulhu */
    break;
   case 59:/* div */
    break;
   case 60:/* divu */
    break;
   case 61:/* rem */
    break;
   case 62:/* remu */
    break;
   case 63:/* mulw */
    break;
   case 64:/* divw */
    break;
   case 65:/* divuw */
    break;
   case 66:/* remw */
    break;
   case 67:/* remuw */
    break;
   case 68:/* call */
    break;
   case 69:/* nop */
    break;
   case 70:/* not */
    break;
   case 71:/* mv */
    break;
  }
 }
}

