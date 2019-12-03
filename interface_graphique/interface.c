#include <gtk/gtk.h>

GtkWidget *btnSegmentation;
GtkWidget *btnTrain;
GtkWidget *btnStart;
GtkWidget *btnQuit;
GtkWidget *btnSelectFile;
GtkWidget *textBox;
GtkWidget *previewImage;

int UI(int argc, char *argv [])
{
    GtkWidget *main_window = NULL;
    SGlobalData data;
    GError *error = NULL;
    gchar *filename = NULL;

    gtk_init(&argc, &argv);
    data.builder = gtk_builder_new();

    filename = g_build_filename("interface.glade", NULL);
    gtk_builder_add_from_file(data.builder, filename, &error);
    g_free(filename);

    if (error)
    {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free(error);
        return code;
    }

    gtk_builder_connect_signals(data.builder, &data);
    main_window = GTK_WIDGET(gtk_builder_get_object(data.builder, "window_main"));
    gtk_widget_show_all(main_window);

    text_view = (GtkTextView*)gtk_builder_get_object(data.builder, "textview1");
    buffer = gtk_text_view_get_buffer(text_view);
    gtk_text_buffer_set_text(buffer, "", strlen(""));

    btnSegmentation = GTK_WIDGET(gtk_builder_get_object(data.builder, "BT_SEGMENTATION"));
    btnTrain = GTK_WIDGET(gtk_builder_get_object(data.builder, "BT_TRAIN"));
    btnStart = GTK_WIDGET(gtk_builder_get_object(data.builder, "BT_START"));
    btnQuit = GTK_WIDGET(gtk_builder_get_object(data.builder, "BT_QUIT"));
    textBox = GTK_WIDGET(gtk_builder_get_object(data.builder, "textview1"));
    previewImage = GTK_WIDGET(gtk_builder_get_object(data.builder, "preview"));
    btnSelectFile = GTK_WIDGET(gtk_builder_get_object(data.builder, "BT_CHOOSE"));

    gtk_main();

    return EXIT_SUCCESS;
}

void interface_quit(GtkWidget* w, gpointer p_data)
{
    gtk_main_quit();
}
