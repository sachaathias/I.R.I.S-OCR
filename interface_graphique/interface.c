#include <gtk/gtk.h>

int main(int argc, char *argv [])
{
    GtkWidget *main_window = NULL;
    GtkBuilder *builder = NULL;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "interface.glade", NULL);

    gtk_widget_show_all(main_window);

    gtk_main();

    return 0;
}
