/* @Author
Student Name: <Ekin Tasyurek>
Student ID : <150190108>
Date: <11.11.2020> */
/*
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "counter.h"

using namespace std;

	
int Counter::findindex(Token *arr,char elem[]){
	for(int i=0; i < ARRAY_SIZE; i++){
		if(!(strcmp((arr+i)->token,elem))){
			return i;
		}
	}
	return -1;
} /*With the strcmp function, we checked whether token has the same string as char array or not.
    We later use this function in read_and_count while we're reading tokens from pi_approximate file */

bool Counter::contains(char *token, char target){

	for(int i=0; i<TOKEN_LENGTH; i++){
		if(token[i] == target){
			return true;
		}
	}
	return false;
}/*In this function, we checked if the char array contains a specific char. 
   In this question we use it to check the '.' in 3.14...*/

void Counter::read_and_count(){
	const char* filename;
	FILE* pi;
	filename = "pi_approximate";
	pi = fopen(filename, "rb"); //Opened the file pi approximate

	int i = 0;

	Token temp_token;

	while (fgets(temp_token.token, 3, pi))
	{	

		if (temp_token.token[1]== '\n'){
			break;
		}	//Checked if the file is over or not; after our last token '79/n', fgets takes'9/n/n' 

		int index = findindex(token_array, temp_token.token); 

		if(contains(temp_token.token,'.')==false){

		if (index == -1){

			token_array[i]= temp_token;
			token_array[i].count = 1;
			token_count++;
			i++;
		} //If we encountered this token for the first time, we create a place in our token array and set its count to 1.
		else{

			token_array [index].count++;
        } //If we encountered this token before, we increment the count

		}
			
		fseek(pi, -1, SEEK_CUR); /*We need to change our position again 
								 We checked 'ab', 'ab*c'
								 To check 'bc', we need to be in 'a*bc', hence -1 */
	}

}


Token *Counter::get_most_common_three(){
	int current_count=0, highest_count_1=0, highest_count_2=0, highest_count_3=0;
	int highest_index_1=0, highest_index_2=0, highest_index_3=0;

	static Token most_common_three_array[3];

	for(int i=0; i<ARRAY_SIZE; i++){
		current_count=token_array[i].count;
		if(current_count>=highest_count_1){
			highest_count_1=current_count;
			highest_index_1=i;
		} //If our token's count is bigger than the other ones we encountered, we take its index

	} 
	most_common_three_array[0] = token_array[highest_index_1];

	for(int j=0; j<ARRAY_SIZE; j++){
		current_count=token_array[j].count;
		if((current_count>=highest_count_2) && (j!=highest_index_1)){
			highest_count_2=current_count;
			highest_index_2=j;
		}//If our token's count is bigger than the other ones we encountered and its not the some token as first one, we take its index

	}
	most_common_three_array[1] = token_array[highest_index_2];

	for(int k=0; k<ARRAY_SIZE; k++){
		current_count=token_array[k].count;
		if((current_count>=highest_count_3) && (k!=highest_index_1) && (k!=highest_index_2)){
			highest_count_3=current_count;
			highest_index_3=k;
		}//If our token's count is bigger than the other ones we encountered and its not the some token as first or second one, we take its index

	}

	most_common_three_array[2] = token_array[highest_index_3];

return most_common_three_array;
}
