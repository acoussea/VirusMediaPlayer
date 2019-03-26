#include <gtk/gtk.h>

/*static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;
  GtkWidget *laimage;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  laimage = gtk_image_new_from_file("oue.jpeg");
	gtk_container_add (GTK_CONTAINER (window), laimage);

  gtk_widget_show_all (window);
}*/

static void activate(GtkApplication *app, gpointer user_data){
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *limage;
	GtkWidget *buttonleft;
	GtkWidget *buttonright;
	
	window = gtk_application_window_new(app);
  gtk_window_set_title (GTK_WINDOW (window), "MediaPlayer");
  gtk_window_set_default_size (GTK_WINDOW (window), 1280, 860);

	box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add (GTK_CONTAINER (window), box);

	buttonleft = gtk_button_new_with_label ("Left");
	gtk_container_add (GTK_CONTAINER (box), buttonleft);	
  //g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

	limage = gtk_image_new_from_file("oue.jpeg");
	gtk_container_add (GTK_CONTAINER (box), limage);

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
