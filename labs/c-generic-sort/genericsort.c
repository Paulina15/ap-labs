#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
char *datos[MAXLINES];

void quicksort(void *lineptr[], int left, int right,
     int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right, 
    int (*comp)(void *, void *));

int numcmp (const char *s1, const char *s2){
        double v1 = atof(s1);
        double v2 = atof(s2);
        if(v1 < v2)
            return -1;
        else if (v1 > v2)
            return 1;
        else
            return 0;
}

void imprimeArreglo(int size, char *results)
{
    FILE * reporte;
    reporte = fopen(results,"w");

    for (int i=0;i<size;i++){
         fprintf(reporte,"%s",(char*)datos[i]);
    }
    fclose(reporte);
    printf("Report is generated at: [%s]\n",results);
}

int main(int argc, char **argv)
{
    int number = 0;
    char* nombreArchivo;
    char* produceSalida;
    int sort = 0; 
    if (argc < 5 || argc > 6){ //validations
        printf("Error: numero invalido de argumentos \n");
        return 0;
    }

    if(argc == 5){
        number = 0;
        nombreArchivo = argv[1];
        if(strcmp(argv[2], "-mergesort") == 0){
            sort = 1;
        }else if(strcmp(argv[2], "-quicksort") == 0){
            sort = 2;
        }else{
            printf("no se introdujo el nombre de la funcion a llamar en la posicion esperada \n");
           return -1;
        }

        if (strcmp(argv[3], "-o") != 0)
        {
            printf("el formato de -o es incorrecto \n");
            return -1;
        }
        produceSalida = argv[4];
    }

    if(argc == 6){
        if(strcmp(argv[1], "-n") != 0){
            printf("no se encontro -n donde corresponde\n");
            return -1;
        }
        number = 1;
        nombreArchivo = argv[2];
        if(strcmp(argv[3], "-mergesort") == 0){
            sort = 1;
        }else if(strcmp(argv[3], "-quicksort") == 0){
            sort = 2;
        }else{
            printf("no se introdujo el nombre de la funcion a llamar en la posicion esperada \n");
            return -1;
        }
        if (strcmp(argv[4], "-o") != 0)
        {
            printf("el formato de -o es incorrecto \n");
            return -1;
        }
        produceSalida = argv[5];
    }

    FILE *archivo = fopen(nombreArchivo, "r");
    
    if(archivo == NULL){
        printf("Error con el nombre del archivo \n");
        return -1;
    }
    char line[500] = {0};
    int n = 0;
    while (fgets(line, 100, archivo))
    {
        datos[n] = (char*)malloc(strlen(line) + sizeof(char*));
        strcpy(datos[n], line);
        n++;
    }

    char *newstr = malloc(strlen(datos[n-1]+2));
    strcpy(newstr, datos[n-1]);
    datos[n-1] = strcat(newstr, "\n");

    if(fclose(archivo)) perror("No se pudo cerrar el archivo\n");
    
    if (sort == 1) //mergesort
    {
        mergesort((void **) datos, 0, n-1, (int(*)(void*, void*)) (number ? numcmp : strcmp));
        printf(" ordenando %s archivo con mergesort \n", nombreArchivo);
        imprimeArreglo(n, produceSalida);
        return 0;
    }else if(sort == 2){ //quicksort
        quicksort((void **) datos, 0, n-1, (int(*)(void*, void*)) (number ? numcmp : strcmp));
        printf(" ordenando %s archivo con quicksort \n", nombreArchivo);
        imprimeArreglo(n, produceSalida);
        return 0;
    }else{
        printf("Intentelo de nuevo \n");
    }

}