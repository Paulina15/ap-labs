
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mergesort(void *lineptr[], int left, int right,int (*comp)(void *, void *)) {
		if(left < right){
        int middle = (left + right) / 2;
        mergesort(lineptr, left, middle, (*comp));
        mergesort(lineptr, middle + 1, right, (*comp));
        merge(lineptr, left, right, (*comp));
    }
}

void merge(void *lineptr[], int left, int right, int (*comp)(void *, void *)){
    int mitad=((left+right)/2)+1;      
    for (int i=mitad;i<=right;i++)
    {
        for(int j=0;j<mitad;j++)
        {
            if ((*comp)(lineptr[i],lineptr[j])<0) {
                void* tmp=lineptr[i];
                lineptr[i]=lineptr[j]; 
                lineptr[j]=tmp;
                lineptr[j]=lineptr[j]; 
            }
        }
    }
}