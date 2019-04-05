#include <stdlib.h>
#include <stdio.h>

int main(){
	char res = 'o';	

	do{
	int a = 0;
	int b = 0;
	char nb;

    	printf("Entrez la première valeur :");
    	scanf("%d", &a);
	printf("Entrez la deuxième valeur :");
    	scanf("%d", &b);
	printf("Entrez l'opérateur (+ - * /) :");
    	scanf(" %c", &nb);

	switch(nb){
		case '+': printf("Résultat:\n%d %c %d = %d\n", a, nb, b, a+b);
		break;
		case '-': printf("Résultat:\n%d %c %d = %d\n", a, nb, b, a-b);
		break;
		case '/': printf("Résultat:\n%d %c %d = %d\n", a, nb, b, a/b);
		break;
		case '*': printf("Résultat:\n%d %c %d = %d\n", a, nb, b, a*b);
		break;
		default:
		printf("Erreur: Opérateur non existant");
	}
	printf("Voulez vous continuer (o ou n)");
    	scanf(" %c", &res);

	}while(res != 'n');

	return EXIT_SUCCESS;
}
