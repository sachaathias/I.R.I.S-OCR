#include <gtk/gtk.h>


    int
main(int argc, char *argv [])
{
    GtkWidget *main_window = NULL;
    GtkBuilder *builder = NULL;
    GError *error = NULL;
    gchar *filename = NULL;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    filename =  g_build_filename ("interface.glade", NULL);

    gtk_builder_add_from_file (builder, filename, &error);
    g_free (filename);
    if (error)
    {
	gint code = error->code;
	g_printerr("%s\n", error->message);
	g_error_free (error);
	return code;
    }

    main_window = GTK_WIDGET(gtk_builder_get_object (builder, "MainWindow"));

    g_signal_connect (G_OBJECT (main_window), "destroy", (GCallback)gtk_main_quit, NULL);

    gtk_widget_show_all (main_window);

    gtk_main();

    return 0;
}
