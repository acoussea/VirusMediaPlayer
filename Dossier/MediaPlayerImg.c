#include <gtk/gtk.h>

GtkWidget *limage;
GtkWidget *window;

static void changeimage(GtkButton* button, gpointer user_data){
	GtkWidget *image = GTK_WIDGET (user_data);
	gtk_image_set_from_file(GTK_IMAGE(limage), "situation.jpg");

	GtkWidget *dialog;
GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
gint res;

dialog = gtk_file_chooser_dialog_new ("Open File",
                                      GTK_WINDOW(window),
                                      GTK_FILE_CHOOSER_ACTION_OPEN,
                                      "_Annuler",
                                      GTK_RESPONSE_CANCEL,
                                      "_Ouvrir",
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);

res = gtk_dialog_run (GTK_DIALOG (dialog));
if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);
	printf("%s\n",filename);    
	//open_file (filename);
    //g_free (filename);
  }

gtk_widget_destroy (dialog);
}

static void activate(GtkApplication *app, gpointer user_data){
	//char tests[3][3] = {"11", "22", "33"};
	//for(int i=0; i<3; i++){printf("%s\n",tests[i]);} 
	GtkWidget *box;
	GtkWidget *boxImg;
	GtkWidget *buttonimgchooser;
	GtkWidget *buttonleft;
	GtkWidget *buttonright;
	
	window = gtk_application_window_new(app);
	gtk_window_set_title (GTK_WINDOW (window), "MediaPlayer");
	gtk_window_set_default_size (GTK_WINDOW (window), 900, 500);

	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add (GTK_CONTAINER (window), box);

	boxImg = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_pack_start (GTK_BOX (box), boxImg, TRUE, TRUE, 0);

	buttonleft = gtk_button_new_with_label ("<-");
	gtk_box_pack_start (GTK_BOX (boxImg), buttonleft, FALSE, FALSE, 0);	
	//g_signal_connect (buttonleft, "clicked", G_CALLBACK (changeimage), NULL);

	limage = gtk_image_new_from_file("oue.jpeg");
	gtk_box_pack_start (GTK_BOX (boxImg), limage, TRUE, TRUE, 0);

	buttonright = gtk_button_new_with_label ("->");
	gtk_box_pack_start (GTK_BOX (boxImg), buttonright, FALSE, FALSE, 0);	
	//g_signal_connect (buttonleft, "clicked", G_CALLBACK (changeimage), NULL);

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
