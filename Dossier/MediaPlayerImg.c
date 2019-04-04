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

int main (int argc, char **argv){
	GtkApplication *app;
	int status;

	app = gtk_application_new ("com.github.virusmediaplayer", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
