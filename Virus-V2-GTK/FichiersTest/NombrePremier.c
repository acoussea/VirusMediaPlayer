#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool isPremier(int n){
	if(n<=1){
		return false;
	}else{
		for(int i=2;i<=n/2;i++){
			if((n!=i) && (n%i==0)){
				return false;
			}
		}
	}
	return true;
}

int main(){
	int a;
	printf("Affichage des nombres premiers entre 0 et un nombre choisi");
	printf("Entrez un nombre pour la borne supérieure de l'intervalle \n");
	scanf("%d",&a);
	for(int i=0;i<a;i++){
		if(isPremier(i)){
			printf("%d\n",i);
		}
	}
	return EXIT_SUCCESS;
}


