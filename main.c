#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "instructions.h"


size_t count_words(const char *input, size_t string_length){
 size_t word_count = 0;
 for(size_t i = 0; i < string_length; i++){
  if((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')){
   word_count++;
   while(((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')) && i < string_length){
    i++;
   }
  }
 }
 return word_count;
}

int main(){
 const char *input = "addi x1, x0, 100\n";
 size_t word_count = 0;
 size_t string_length = strlen(input);
 
 word_count = count_words(input, string_length);
 size_t word_start[word_count];
 size_t word_end[word_count];
 
 size_t index = 0;
 printf("Word Count: %li\n", word_count); // Test

 for(size_t i = 0; i < string_length; i++){ /* Code for getting indexes of the start of words */
  if((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')){
   word_start[index] = i;
   index++;
   while(((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')) && i < string_length){
    i++;
   }
  }
 }
 
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
 
 printf("Line Count: %li\n", line_count); // Test
}
