#include <stdio.h>
#include <string.h>

int mystrlen(char *);
char *mystradd(char *, char *);
int mystrfind(char *, char *);

int main(int argc, char *argv[]) {
    if (argc==4 && strcmp(argv[1],"-find")==0){
         int buscar = mystrfind(argv[2], argv[3]);
        if (buscar > -1) {
            printf("['%s'] el string fue econtrado en la [%d] posicion\n", argv[3], buscar);
        } else {
            printf("El input no fue encontrado \n");
        }
        return 0;  
    }
    else if (argc==4 && strcmp(argv[1],"-add")==0){
        printf("Initial Lenght      : %d\n", mystrlen(argv[2]));
        char *added_word = mystradd(argv[2],argv[3]);
        printf("New String          : %s\n", added_word);
        printf("New length          : %d\n", mystrlen(added_word));
        return 0;
    }
    else if (argc==3 && strcmp(argv[1],"-add")==0){
        printf("Error. No tenemos ningun string para agregar. \n");
    }
    else if (argc==3 && strcmp(argv[1],"-find")==0){
        printf("Error. No tenemos un string que encontrar. \n");
    }
    else {
        printf("Error. Lo que introduciste como parametro es incorrecto \n");
    }
    return 0;
}