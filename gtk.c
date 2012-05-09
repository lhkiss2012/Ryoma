#include <stdio.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <string.h> 
#include <locale.h> 

void hello(GtkWidget *widget,gpointer   data )
{
    g_print ("Hello World\n");
}

void Welcome(GtkWidget *widget,gpointer   data )
{
}

gint delete_event(GtkWidget *widget,GdkEvent  *event,gpointer   data )
{
    g_print ("delete event occurred\n");

    return FALSE;
}


void destroy(GtkWidget *widget,gpointer data)
{
    gtk_main_quit ();
}



int main(int argc,char *argv[])
{
    GtkWidget  *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *window1;
    GtkWidget   *image;

    
    gtk_set_locale();
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"^^^^^ Linux TaskManager ^^^^^");
    gtk_window_set_default_size(GTK_WINDOW(window),800,600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_widget_set_app_paintable(window1,TRUE);
    gtk_widget_realize(window1);

    window1 = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), window1);

    image=gtk_image_new_from_file("/home/lh/Desk/12.jpg");
    gtk_container_add(GTK_CONTAINER(window1),image);

    
    button1 = gtk_button_new_with_label(" ^^ »¶Ó­½øÈë ^^ ");
    gtk_fixed_put(GTK_FIXED(window1), button1, 620, 520);
    gtk_widget_set_size_request(button1, 120, 30);

    button2 = gtk_button_new_with_label(" ^^ ÍË ³ö ^^ ");
    gtk_fixed_put(GTK_FIXED(window1), button2, 620, 560);
    gtk_widget_set_size_request(button2, 120, 30);


    g_signal_connect(G_OBJECT(window), "delete_event",G_CALLBACK (delete_event), NULL);

    
    g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK (Welcome), NULL);
    g_signal_connect_swapped(G_OBJECT(button1), "clicked",G_CALLBACK(gtk_widget_destroy),window);

    g_signal_connect(G_OBJECT(button2), "clicked",G_CALLBACK (hello), NULL);
    g_signal_connect_swapped(G_OBJECT(button2), "clicked",G_CALLBACK(gtk_widget_destroy),window);
  
   
    gtk_widget_show_all(window);


    gtk_main ();
    
    return 0;
}