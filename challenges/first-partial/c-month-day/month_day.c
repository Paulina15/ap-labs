#include <stdio.h>
#include <stdlib.h>

/* month_name:  return name of n-th month */
char *month_name(int n) {

   static char *name[] = {
       "Illegal month",
       "January", "February", "March",
       "April", "May", "June",
       "July", "August", "September",
       "October", "November", "December"
   };

   return (n < 1 || n > 12) ? name[0] : name[n];
}

char *month_name(int n);
int month, day;

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* month_day function's prototype*/
void month_day(int year, int yearday, int *pmonth, int *pday);

void month_day(int year, int yearday, int *pmonth, int *pday){
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; i < 13; i++){
        if (yearday <= daytab[leap][i]){
            *pmonth = i;
            *pday = yearday;
            return;
        }
        else {
            yearday -= daytab[leap][i];
        }
    }
}

int main(int argc, char *argv[]) {
  if (argc < 3){
        printf("Faltan elementos");
        return 0;
    }
    int year = atoi(argv[1]);
    int yearday = atoi(argv[2]);
    if (yearday > 366){
        printf("A year has max 366 days, no more\n");
        return 0;
    }
    int *pmonth, *pday;
    pmonth = &month;
    pday = &day;
    month_day(year, yearday, pmonth, pday);
    char *m = month_name(month);
    printf("%s %d, %d\n", m, day, year); 
}