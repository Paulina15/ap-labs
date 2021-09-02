#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>


// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
long calc(int operator, int nValues, int *values) {
    long cont = values[2];
    printf("%ld", cont);
    for (int i = 3; i < nValues; i++){
        if(operator == 1){
            printf(" + %i", values[i]);
            cont = cont + values[i];
        }else if(operator == 2){
            printf(" - %i", values[i]);
            cont = cont - values[i];
        } else {
            printf(" * %i", values[i]);
            cont = cont * values[i];
        }
    }
   
    return cont;
}

int main(int argc, char*argv[]) {
    if(argc >= 3){
        int val[argc];
        int operator = 0;
        if(strcmp("add", argv[1]) == 0){
            operator = 1;
        }else if(strcmp("sub", argv[1]) == 0){
            operator = 2;     
        }else if(strcmp("mult", argv[1]) == 0){
            operator = 3;
        }else{
            printf("No es valido \n");
            return 0;
        }

        for (int i = 2; i < argc; ++i) {
            for(int j=0; j< strlen(argv[i]); j++){
                if(!isdigit(argv[i][j])){
                    printf("Usas un character no valido \n");
                }
            }
            val[i]=atoi(argv[i]);   
        }
        
        long result=calc(operator,argc,val);
        printf(" = %ld \n", result);
    }else{
        printf("operacion no valida, vuelve a intentarlo\n");
    }

    return 0;
    
}
