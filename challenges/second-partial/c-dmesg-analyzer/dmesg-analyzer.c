#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPORT_FILE "report.txt"
#define HASHSIZE 100000

void analizeLog(char *logFile, char *report);

struct nlist{
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s){
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++){
        hashval = *s + 31 * hashval;
    }
    return hashval%HASHSIZE;
}

struct nlist *lookup(char *s){
    struct nlist *np;
    
    for (np = hashtab[hash(s)]; np != NULL; np = np->next){
        if(strcmp(s, np->name) == 0){
            return np;
        }
    }
    return NULL;
}

struct nlist *install(char *name, char *defn){
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL){
        np = (struct nlist *) malloc(sizeof(*np));
        if(np == NULL || (np->name = strdup(name))==NULL){
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }else{     //already there
        char *newSize;
        newSize = np->defn;
        np->defn = malloc(strlen(np->defn) + strlen(defn) + 50000);
        strcpy(np->defn, newSize);
        strcat(np->defn, "    ");
        strcat(np->defn, defn);
        return NULL;
    }

    if((np->defn = strdup(defn)) == NULL){
        return NULL;
    }
    return np;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Faltan argumentos\n");
        return 1;
    }

    analizeLog(argv[1], REPORT_FILE);
    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    FILE *archivo;
    char *linea = NULL;
    char *linea_1;
    char *linea_2;
    size_t length = 0;
    ssize_t lectura;

    archivo = fopen(logFile, "r");
    if (archivo == NULL){
        printf("\nError de apertura del archivo. \n\n");
    }

    while ((lectura = getline(&linea, &length, archivo) != -1)){
        linea_1 = strdup(linea);
        linea_2 = strdup(linea);
        char *token;
        char *token1;
        char * linea_hora;
        char * linea_resto;
        char * nueva;
        token = strtok(linea, "]");
        linea_hora = strdup(token);
        token = strtok(NULL, ":");
        linea_resto = strtok(NULL, "");
        if (linea_resto == NULL)
        {
            linea_resto = token;
        }
        token1 = strtok(linea_2, "]");
        token1 = strtok(NULL, "");
        if(token != NULL){
            nueva = malloc(strlen(linea_hora) + strlen(linea_resto) +4);
            strcpy(nueva,linea_hora);
            strcat(nueva,"]");
            strcat(nueva,linea_resto);
            if(strcmp(token, token1) == 0){
                install("General", linea_1);
            }else{
                install(token, nueva);
            }
        }
        
    }  
    fclose(archivo);

    archivo = fopen(REPORT_FILE, "w");

    if(archivo == NULL){
        printf("Error para crear el archivo");
    }

    for (int i = 0; i < HASHSIZE; i++){
        if(hashtab[i]!=NULL){
            fprintf(archivo, "%s\n", hashtab[i]->name);
            fprintf(archivo, "    %s\n", hashtab[i]->defn);
        }
    }
    printf("Report is generated at: [%s]\n", report);
}
