
#include <gtk/gtk.h>

void okPressed(GtkWidget *widget, gpointer label)
{
	printf("OK\n");
}

void cancelPressed(GtkWidget *widget, gpointer label)
{
	printf("Cancel\n");
}

//MAIN-------------------------------------
int main(int argc,char* argv[])
{
	//mainwindow
	GtkWidget *window;
	
	GtkWidget *frame;
	
	//buttons
	GtkWidget *butOk;
	GtkWidget *butCancel;
	
	//combo boxes
	GtkWidget *comboResolution;
	
    gtk_init(&argc,&argv);

	//create window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Config");
	gtk_widget_set_size_request(window, 600, 400);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
	
	//frame
	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window),frame);
	
	//OK button
	butOk = gtk_button_new_with_label("OK");
	gtk_widget_set_size_request(butOk,80,35);
	gtk_fixed_put(GTK_FIXED(frame),butOk,200,350);
	
	//Cancel button
	butCancel = gtk_button_new_with_label("Cancel");
	gtk_widget_set_size_request(butCancel,80,35);
	gtk_fixed_put(GTK_FIXED(frame),butCancel,300,350);
	
	//Resolution
	
	gtk_widget_show_all(window);

	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(butOk, "clicked", G_CALLBACK(okPressed),NULL);
	g_signal_connect(butCancel, "clicked", G_CALLBACK(cancelPressed),NULL);
	
	gtk_main();
	
    return 0;
}
//-----------------------------------------
