#include <stdlib.h>
#include <stdio.h>

int fibo(int n){
	if(n<2){
		return n;
	}else{
		return fibo(n-1)+fibo(n-2);
	}
}

int main(){
	int a;
	printf("Calcul d'un terme de la suite de Fibonacci selon l'indice choisi\n");
	printf("Entrez l'indice du terme à calculer\n"); 
	scanf("%d",&a);
	printf("%d\n",fibo(a));
	return EXIT_SUCCESS;
}


