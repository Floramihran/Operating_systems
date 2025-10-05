#include <stdio.h>
#include <stdlib.h>

int main(){
	char **strings;
	int initial_size = 3;
	int new_size = 5;

	strings = (char **)malloc(initial_size * sizeof(char *));

	if (strings == NULL){
		printf("Memory allocation failed!\n");
		return 1;
	}

	for (int i = 0; i < initial_size; i++){
		strings[i] = (char *)malloc(50 * sizeof(char));
		if(strings[i] == NULL){
			printf("Memory allocation for string %d failed!\n", i);
			for (int j = 0; j < i; j++){
				free(strings[j]);
			}
			free(strings);
			return 1;
		}
	}

	printf("Enter 3 strings: ");
	for (int i = 0; i < initial_size; i++){
		scanf("%s", strings[i]);
	}
	
	char **temp = (char **)realloc(strings, new_size * sizeof(char *));

	if (temp == NULL){
		printf("Memory reallocation failed!\n");

		for(int i = 0; i < initial_size; i++){
			free(strings[i]);
		}
		free(strings);
		return 1;
	}else{
		strings = temp;
	}


	 for (int i = initial_size ; i < new_size; i++){

                strings[i] = (char *)malloc(50 * sizeof(char));

		if(strings[i] == NULL){                                                            
			printf("Memory allocation for string %d failed!\n", i);

			for (int j = 0; j < i; j++){
                                free(strings[j]);
                        }
                        free(strings);
                        return 1;
                }
        }
	
	printf("Enter 2 more strings: ");
       for (int i = initial_size; i < new_size; i++){
       		scanf("%s", strings[i]);
       }

       printf("All strings: ");
       for(int i = 0; i < new_size; i++){
       	        printf("%s ", strings[i]);
       }
       printf("\n");

	for (int i = 0; i < new_size; i++){
		free(strings[i]);
	}
	free(strings);

	return 0;

}
