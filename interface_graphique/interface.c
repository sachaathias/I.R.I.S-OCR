#include <gtk/gtk.h>
#include <stdlib.h>
#include <signal.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "../Tests/tests_functions.h"

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

char* filename;

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

    g_object_unref(builder);

    gtk_widget_show(window_main);

    gtk_main();

    return EXIT_SUCCESS;
}

void on_BT_START_clicked(GtkButton *b)
{
    display_image_test(filename);

}
void on_BT_TRAIN_clicked(GtkButton* b)
{

}

void on_BT_SEGMENTATION_clicked(GtkButton* b)
{


}

void on_BT_SHOW_clicked(GtkButton* b)
{

}

void on_BT_CHOOSE_file_set(GtkFileChooserButton *f)
{
    filename =  gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f));
    printf("%s\n", filename);
    printf("folder name = %s\n", gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER(f));
}

void on_quit_clicked(GtkButton* b)
{
    gtk_main_quit();
}

