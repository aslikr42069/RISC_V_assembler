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
 size_t word_length = 0;
 size_t instruction_length = 0;
 instruction_count = sizeof(instruction_string) / sizeof(instruction_string[0]); 
 index = 0;
 size_t instructions_in_code = 0;

 for(size_t i = 0; i < word_count; i++){ /* Code for getting the amount of instructions in the source code */
  word_length = word_end[i] - word_start[i];
  for(size_t j = 0; j < instruction_count; j++){
   instruction_length = strnlen(instruction_string[j], 6);
   if(word_length == instruction_length){
    index = word_start[i];
    if(strncmp(input + index, instruction_string[j], word_length) == 0){
     instructions_in_code++;
     break;
    }
   }
  }
 }

 size_t instruction[instructions_in_code];
 size_t which_instruction[instructions_in_code];
 size_t index_of_instructions = 0;
 
 for(size_t i = 0; i < word_count; i++){ /* Code for getting where in the source code the instructions are located */
  word_length = word_end[i] - word_start[i];
  for(size_t j = 0; j < instruction_count; j++){
   instruction_length = strnlen(instruction_string[j], 6);
   if(word_length == instruction_length){
    index = word_start[i];
    if(strncmp(input + index, instruction_string[j], word_length) == 0){
     instruction[index_of_instructions] = i;
     which_instruction[index_of_instructions] = j; // Tells us which instruction it is
     index_of_instructions++;
     break;
    }
   }
  }
 }
 
 size_t number_count = 0;
 for(size_t i = 0; i < word_count; i++){ /* Code for getting amount of numbers in source code */
  if(input[word_end[i] - 1] >= '0' && input[word_end[i] - 1] <= '9'){
   number_count++;
  }
 }
 
 size_t number[number_count];
 index = 0;
 for(size_t i = 0; i < word_count; i++){ /* Code for getting amount position of numbers in source code */
  if(input[word_end[i] - 1] >= '0' && input[word_end[i] - 1] <= '9'){
   number[index] = i;
   index++;
  }
 }

 function symbol_table[function_count];


 for(size_t i = 0; i < function_count; i++){
  symbol_table->next = NULL;
 }

 function unorganized[function_count];
 for(size_t i = 0; i < function_count; i++){
  unorganized[i].start = word_start[function_index[i]];
  unorganized[i].end = word_end[function_index[i]];
  unorganized[i].length = word_end[function_index[i]] - word_start[function_index[i]];
  unorganized[i].word = function_index[i];
 }

 for(size_t i = 0; i < function_count; i++){
  index = hash(input, unorganized[i].start, unorganized[i].end) % function_count;
  unorganized[i].next = symbol_table[index].next;
  symbol_table[index] = unorganized[i];
 }

 printf("First instruction is: %s\n", instruction_string[which_instruction[0]]); // Test
}
