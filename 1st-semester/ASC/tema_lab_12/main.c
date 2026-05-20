
/*
Problema 12
Se dau doua siruri de caractere de lungimi egale. Se cere sa se calculeze si sa se afiseze rezultatele intercalarii literelor, pentru cele doua intercalari posibile (literele din primul sir pe pozitii pare, respectiv literele din primul sir 
pe pozitii impare)
*/

#include <stdio.h>
#include <string.h>
void intercal(char* a, char* b,char* sir_intercalat);
int main() {

	
    char s1[]="xxxxx",s2[]="00000", s3[100]="";
    //prima intercalare
    intercal(s1,s2,s3);
    printf(s3);
    printf("\n");
    //a doua intercalare
    intercal(s2,s1,s3);
    printf(s3);
    return 0;
}