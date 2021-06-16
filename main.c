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
 const char *input = "function: addi x1, x0, 100";
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
 printf("Function Count: %li\n", function_count);
}
