#include <gtk/gtk.h>
#include <stdlib.h>
#include <signal.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

GtkWidget *window_main;
GtkWidget *btnShowImage;
GtkWidget *btnSegmentation;
GtkWidget *btnTrain;
GtkWidget *btnStart;
GtkWidget *btnQuit;
GtkWidget *btnSelectFile;
GtkWidget *textBox;
GtkWidget *previewImage;
GtkBuilder *builder;

int main(int argc, char *argv [])
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("interface.glade");
    window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    gtk_builder_connect_signals(builder, NULL);

    btnSegmentation = GTK_WIDGET(gtk_builder_get_object(builder, "BT_SEGMENTATION"));
    btnTrain = GTK_WIDGET(gtk_builder_get_object(builder, "BT_TRAIN"));
    btnStart = GTK_WIDGET(gtk_builder_get_object(builder, "BT_START"));
    btnQuit = GTK_WIDGET(gtk_builder_get_object(builder, "BT_QUIT"));
    textBox = GTK_WIDGET(gtk_builder_get_object(builder, "textview1"));
    previewImage = GTK_WIDGET(gtk_builder_get_object(builder, "preview"));
    btnSelectFile = GTK_WIDGET(gtk_builder_get_object(builder, "BT_CHOOSE"));
    btnShowImage = GTK_WIDGET(gtk_builder_get_object(builder, "BT_SHOW"));

    gtk_widget_show(window_main);

    gtk_main();

    return EXIT_SUCCESS;
}

void on_btnShowImage_clicked(GtkButton *b)
{
}
void on_start_clicked(GtkButton* b)
{

}

void on_segmentation_clicked(GtkButton* b)
{


}

void on_quit_clicked(GtkButton* b)
{
    gtk_main_quit();
}
