
uint32_t *generate_machine_code(char *input, size_t word_count, size_t *words[], size_t number_count, ssize_t *number, size_t instructions_in_code, size_t *instruction, size_t *which_instruction, size_t function_count, function *symbol_table[], size_t line_count, size_t *line){
 
 size_t actual_instruction_count = instructions_in_code;
 
 for(size_t i = 0; i < instructions_in_code; i++){
  if(which_instruction[i] == 68){
   // If the instruction is call, then run this code
   actual_instruction_count++;
  }
 }

 uint32_t machine_code[actual_instruction_count];
 size_t current_number = 0;
 size_t current_line = 1;
 size_t current_instruction = 0;
 for(size_t i = 0; i < actual_instruction_count; i++){
  if(current_line < line_count && words[instruction[current_instruction]][0] >= line[current_line]){
   current_line++;
  }
  switch(which_instruction[i]){
   case 0:/* lui */
    if(number[current_number] > 31){
     printf("Error: Line %li. Register provided is greater than registers available.\n", current_line);
     exit(1);
    }
    machine_code[i] = 55 | (number[current_number] & 0x1F) << 6 | (number[current_number + 1] & 0xFFFFF) << 11;
    current_number += 2;
    current_instruction++;
    break;
   case 1:/* auipc */
    break;
   case 2:/* jal */
    break;
   case 3:/* jalr */
    break;
   case 4:/* beq */
    break;
   case 5:/* bne */
    break;
   case 6:/* blt */
    break;
   case 7:/* bge */
    break;
   case 8:/* bltu */
    break;
   case 9:/* bgeu */
    break;
   case 10:/* lb */
    break;
   case 11:/* lh */
    break;
   case 12:/* lw */
    break;
   case 13:/* lbu */
    break;
   case 14:/* lhu */
    break;
   case 15:/* sb */
    break;
   case 16:/* sh */
    break;
   case 17:/* sw */
    break;
   case 18:/* addi */
    break;
   case 19:/* slti */
    break;
   case 20:/* sltiu */
    break;
   case 21:/* xori */
    break;
   case 22:/* ori */
    break;
   case 23:/* andi */
    break;
   case 24:/* slli */
    break;
   case 25:/* srli */
    break;
   case 26:/* srai */
    break;
   case 27:/* add */
    break;
   case 28:/* sub */
    break;
   case 29:/* sll */
    break;
   case 30:/* slt */
    break;
   case 31:/* sltu */
    break;
   case 32:/* xor */
    break;
   case 33:/* srl */
    break;
   case 34:/* sra */
    break;
   case 35:/* or */
    break;
   case 36:/* and */
    break;
   case 37:/* fence */
    break;
   case 38:/* ecall */
    break;
   case 39:/* ebreak */
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

