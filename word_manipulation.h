size_t count_words(char *input, size_t string_length, size_t *comment_start, size_t *comment_end, size_t comment_count){
 size_t word_count = 0;
 uint8_t not_comment = 1;
 for(size_t i = 0; i < string_length; i++){
  not_comment = 1;
  if((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')){
   for(size_t j = 0; j < comment_count; j++){
    if((i >= comment_start[j]) && (i < comment_end[j])){
     not_comment = 0;
    }
   }
   if(not_comment == 1){
    word_count++;
   }
   while(((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')) && i < string_length){
    i++;
   }
  }
 }
 return word_count;
}

size_t hash(char *input, size_t start, size_t end){
 size_t hash_return = 5381;

 for(size_t i = start; i < end; i++){
  hash_return = ((hash_return << 5) + hash_return) + input[i];
 }
 return hash_return;
}

typedef struct function{
 size_t index;
 size_t start;
 size_t end;
 size_t length;
 struct function *next;

}function;

typedef struct riscv_instruction{
 size_t length;
 size_t index;
 struct riscv_instruction *next;
}riscv_instruction;

function *lookup_function(char *input, function *function_table[], size_t function_count, size_t fn2_start, size_t fn2_end){
 size_t index = hash(input, fn2_start, fn2_end) % function_count;
 function *tmp = function_table[index];
 while((tmp != NULL) && (strncmp(input + tmp->start, input + fn2_start, tmp->length) != 0)){
  tmp = tmp->next;
 }
 return tmp;
} 

riscv_instruction *lookup_instruction(char *input, riscv_instruction *instruction_table[], size_t instruction_count, size_t start, size_t end){
 size_t index = hash(input, start, end) % instruction_count;
 riscv_instruction *tmp = instruction_table[index];
 while((tmp != NULL) && (strncmp(instruction_string[tmp->index], input + start, tmp->length) != 0)){
  tmp = tmp->next;
 }
 return tmp;
}

intmax_t number_return(char *input, size_t start, size_t end, size_t current_line){
 intmax_t current_digit = 1;
 intmax_t number = 0;
 for(size_t i = start; i < end; i++){
  if((input[i] < '0') || (input[i] > '9')){
   printf("Error: Line %li, non-number in token that was interpreted as number\n", current_line);
   exit(1);
  }
 }

 for(size_t i = start; i < end - 1; i++){
  current_digit = current_digit * 10;
 }


 for(size_t i = start; i < end; i++){
  number += (input[i] - '0') * current_digit;
  current_digit = current_digit / 10;
 }
 if(start > 0){
  if(input[start - 1] == '-'){
   number = number * -1;
  }
 }
 return number;
}

