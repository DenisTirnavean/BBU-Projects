#include <stdio.h>
int main()
{
    int i,n,numar_curent,suma=0;
    //citim cate numere urmeaza sa citim
    printf("Cate numere doresti sa citesti? n=");
    scanf("%d",&n);

    //citim cele n numere de la tastatura
    for(i=1;i<=n;i++)
    {
        scanf("%d",&numar_curent);
        //adaugam numarul curent la suma
        suma+=numar_curent;
    }
    // afisam suma
    printf("Suma numerelor este= %d",suma);
    return 0;
//lab 1 pb 10, lab 2 pb 9
}