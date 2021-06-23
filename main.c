#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "instructions.h"
#include "word_manipulation.h"




int main(int argc, char *argv[]){
 if(argc != 3){
  printf("Incorrect usage of program.\nCorrect usage is: %s [INPUT_FILE_NAME] [OUTPUT_FILE_NAME]\n", argv[0]);
  return 0;
 }
 
 FILE *file = fopen(argv[1], "r");
 if(file == NULL){
  printf("Error, file %s could not be opened!\n", argv[1]);
 }
 fseek(file, 0, SEEK_END);
 size_t string_length = (size_t) ftell(file);
 rewind(file);
 size_t bytes_read = 0;
 char *input = (char *) malloc(sizeof(char) * string_length);
 bytes_read = fread(input, 1, string_length, file);
 if(bytes_read != string_length){
  puts("Error reading file\n");
  return 0;
 }
 fclose(file);
 
 size_t word_count = 0;
 size_t index = 0;

 size_t comment_count = 0;
 for(size_t i = 0; i < string_length; i++){ /* Code for counting the number of comments */
  if(input[i] == '#'){
   comment_count++;
  }
 }

 index = 0;
 size_t comment_start[comment_count];
 for(size_t i = 0; i < string_length; i++){ /* Code for getting where a comment starts */
  if(input[i] == '#'){
   comment_start[index] = i;
   index++;
  }
 }
 size_t comment_end[comment_count];
 
 size_t line_count = 1;
 for(size_t i = 0; i < string_length; i++){
  if(input[i] == '\n'){
   line_count++;
  }
 }

 size_t line[line_count]; // Array telling us the index of the string in which the newlines lie
 line[0] = 0; // Just saying that the first line starts at the first character
 if(line_count > 1){
 index = 1;
 for(size_t i = 0; i < string_length; i++){
  if(input[i] == '\n'){
   line[index] = i;
   index++;
   }
  }
 }

 
 for(size_t i = 0; i < comment_count; i++){ /* Code for getting where comments end */
  index = comment_start[i];
  while(input[index] != '\n' && index < string_length){ 
   index++;
  }
  comment_end[i] = index; 
 }
 
 index = 0;
 word_count = count_words(input, string_length, comment_start, comment_end, comment_count);
 size_t word_start[word_count];
 size_t word_end[word_count];

 for(size_t i = 0; i < string_length; i++){ /* Code for getting indexes of the start of words */
  if(comment_count > 0){
   for(size_t j = 0; j < comment_count; j++){
    if((i >= comment_start[j]) && (i < comment_end[j])){
     i++;
    } else{
     if((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')){ 
      word_start[index] = i;
      index++;
      while(((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')) && i < string_length){
       i++;
      }
     }
    }
   }
  } else{
   if((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')){ 
      word_start[index] = i;
      index++;
      while(((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')) && i < string_length){
       i++;
      }
    }
  }
 }

 index = 0;
 for(size_t i = 0; i < word_count; i++){ /* Code for getting indexes of the end of words */
  index = word_start[i];
  while(((input[index] >= '0' && input[index] <= '9') || (input[index] >= 'A' && input[index] <= 'Z') || (input[index] >= 'a' && input[index] <= 'z')) && index < string_length){
   index++;
  }
  word_end[i] = index;
 }
 
 size_t function_count = 0;
 for(size_t i = 0; i < word_count; i++){ /* Code for checking the number of functions */
  if(word_end[i] != string_length){
   if(input[word_end[i]] == ':'){
    function_count++;
   }
  }
 }
 
 size_t function_index[function_count]; // This tells us which index of either word_start or word_end the functions declaration are at
 index = 0;
 for(size_t i = 0; i < word_count; i++){ /* Code for getting the index of words that are function declarations the array of words */
  if(word_end[i] != string_length){
   if(input[word_end[i]] == ':'){
    function_index[index] = i;
    index++;
   }
  }
 }
 
 
 size_t instruction_count = 0;
 instruction_count = sizeof(instruction_string) / sizeof(instruction_string[0]);
 index = 0;
 size_t instructions_in_code = 0; 

 riscv_instruction *instruction_table[instruction_count];
 riscv_instruction unorganized_instructions[instruction_count]; // Start of code for making hash table of instructions

 for(size_t i = 0; i < instruction_count; i++){
  instruction_table[i] = NULL;
 }

 for(size_t i = 0; i < instruction_count; i++){
  unorganized_instructions[i].length = strlen(instruction_string[i]);
  unorganized_instructions[i].index = i;
 }

 for(size_t i = 0; i < instruction_count; i++){
  index = hash(instruction_string[i], 0, unorganized_instructions[i].length) % instruction_count;
  unorganized_instructions[i].next = instruction_table[index];
  instruction_table[index] = &unorganized_instructions[i];
 }

 riscv_instruction *instruction_search;

 for(size_t i = 0; i < word_count; i++){ // Code for counting number of instructions in code
  instruction_search = lookup_instruction(input, instruction_table, instruction_count, word_start[i], word_end[i]);
  if(instruction_search != NULL){
   instructions_in_code++;
  }
 }

 size_t instruction[instructions_in_code];
 size_t which_instruction[instructions_in_code];
 index = 0;

 for(size_t i = 0; i < word_count; i++){ // Code for identfying position and identity of instructions in code
  instruction_search = lookup_instruction(input, instruction_table, instruction_count, word_start[i], word_end[i]);
  if(instruction_search != NULL){
   instruction[index] = i;
   which_instruction[index] = instruction_search->index;
   index++;
  }
 }


 size_t number_count = 0;
 for(size_t i = 0; i < word_count; i++){ /* Code for getting amount of numbers in source code */
  if(input[word_start[i]] >= '0' && input[word_start[i]] <= '9'){
   number_count++;
  }
  if(input[word_start[i]] == 'x'){
   if((word_end[i] - word_start[i]) > 1){
    if(input[word_start[i] + 1] >= '0' && input[word_start[i] + 1] <= '9'){
     number_count++;
    }
   }
  }
 }
 printf("Number Count: %li\n", number_count);
 
 size_t number[number_count];
 index = 0;
 for(size_t i = 0; i < word_count; i++){ /* Code for getting amount position of numbers in source code */
  if(input[word_start[i]] >= '0' && input[word_start[i]] <= '9'){
   number[index] = i;
   index++;
  }
  if(input[word_start[i]] == 'x'){
   if((word_end[i] - word_start[i]) > 1){
    if(input[word_start[i] + 1] >= '0' && input[word_start[i] + 1] <= '9'){
     number[index] = i;
     index++;
    }
   }
  }
 }


 function *symbol_table[function_count]; // Start of code for making the symbol table,
                                         // which contains the function names

 for(size_t i = 0; i < function_count; i++){
  symbol_table[i] = NULL;
 }

 function unorganized[function_count];

 for(size_t i = 0; i < function_count; i++){
  unorganized[i].index = function_index[i];
  unorganized[i].start = word_start[function_index[i]];
  unorganized[i].end = word_end[function_index[i]];
  unorganized[i].length = word_end[function_index[i]] - word_start[function_index[i]];
 }

 
 for(size_t i = 0; i < function_count; i++){
  index = hash(input, unorganized[i].start, unorganized[i].end) % function_count;
  unorganized[i].next = symbol_table[index];
  symbol_table[index] = &unorganized[i];
 }

 
 size_t words[word_count][3]; // word[0][0] = the position of the start of the first word
                              // word[0][1] = the position of the end of the first word
                              // word[0][2] = the type of word of the first word

 for(size_t i = 0; i < word_count; i++){
  words[i][0] = word_start[i];
  words[i][1] = word_end[i];
  words[i][2] = OTHER;
 }
 
 for(size_t i = 0; i < instructions_in_code; i++){
  words[instruction[i]][2] = INSTRUCTION;
 }
 
 for(size_t i = 0; i < number_count; i++){
  words[number[i]][2] = NUMBER;
 }

 for(size_t i = 0; i < function_count; i++){
  words[function_index[i]][2] = FUNCTION_DECLARATION;
 }
 
 function *search;
 for(size_t i = 0; i < word_count; i++){
  if(words[i][2] == OTHER){
   search = lookup_function(input, symbol_table, function_count, words[i][0], words[i][1]);
   if(search != NULL){
    words[i][2] = FUNCTION_CALL;
   }
  }
 }

 index = 0;
 size_t current_line = 1;
 size_t argument_count = 0;
 size_t num_index = 0;


 for(size_t i = 0; i < word_count; i++){ /* Code for checking code correctness */
  if(current_line < line_count && word_start[i] >= line[current_line] /* Code for getting current line */ ){
   current_line++;
  }
  switch(words[i][2]){
   case INSTRUCTION:
    argument_count = 0;
    while((i + argument_count + 1 < word_count) && words[i + argument_count + 1][2] == instruction_arg_type[which_instruction[index]]){
     argument_count++;
    }
    if(argument_count != instruction_argument_count[which_instruction[index]]){
     printf("Error: Line %li. Wrong amount of arguments supplied. Expected %i, recieved %li\n", current_line, instruction_argument_count[which_instruction[index]], argument_count);
     exit(1);
    }
    if(words[i + argument_count][2] != instruction_arg_type[which_instruction[index]] && instruction_argument_count[which_instruction[index]] > 0){
     printf("Error: Line %li. Wrong type of argument supplied to instruction\n", current_line);
     printf("Argument Type 1 %li, 2: %li\n", words[i + 1 + argument_count][2], instruction_arg_type[which_instruction[index]]);
     exit(1);
    }
    index++;
    break;
   case NUMBER:
    if(input[word_start[number[num_index]]] == 'x'){
     number[num_index] = number_return(input, word_start[number[num_index]] + 1, word_end[number[num_index]], current_line);
    }else{
     number[num_index] = number_return(input, word_start[number[num_index]], word_end[number[num_index]], current_line);
    }
    num_index++;
    break;
   case FUNCTION_DECLARATION:
    break;
   case FUNCTION_CALL:
    break;
   case OTHER:
    printf("Error: Unrecognized symbol at line %li\n", current_line);
    exit(1);
    break;
  } 
 } 
 
 
 printf("First instruction is: %s\n", instruction_string[which_instruction[0]]); // Test
}

