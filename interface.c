#include "interface.h"

GtkWidget *window_main;
GtkWidget *btnSegmentation;
GtkWidget *btnTrain;
GtkWidget *btnStart;
GtkWidget *btnQuit;
GtkWidget *btnSelectFile;
GtkWidget *textBox;
GtkWidget *previewImage;
GtkWidget *logo;
GtkWidget *scrol;
GtkWidget *fixed1;
GtkWidget *fixed_stk0;
GtkWidget *fixed_stk1;
GtkBuilder *builder;
GtkTextBuffer *TextBuffer;
GtkWidget *viewport;
GtkWidget *save;

char* filename = NULL;
char* c = NULL;

void on_save_clicked();
void on_changed_text();


int UI(int argc, char *argv [])
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
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    fixed_stk0 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_stk0"));
    fixed_stk1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_stk1"));
    logo = GTK_WIDGET(gtk_builder_get_object(builder, "logo"));
    viewport = GTK_WIDGET(gtk_builder_get_object(builder, "viewport"));
    scrol = GTK_WIDGET(gtk_builder_get_object(builder, "scrol"));
    save = GTK_WIDGET(gtk_builder_get_object(builder, "save"));

    TextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textBox));

    g_signal_connect(TextBuffer, "changed", G_CALLBACK(on_changed_text), NULL);

    gtk_widget_hide(save);

    g_object_unref(builder);

    /*GdkColor color;
    color.red = 0xcccc;
    color.green = 0xcccc;
    color.blue = 0xd900;
    gtk_widget_override_background_color(GTK_WIDGET(window_main), GTK_STATE_NORMAL, &color);*/

    gtk_widget_show(window_main);

    gtk_main();

    return EXIT_SUCCESS;
}

void on_BT_START_clicked()
{
    if(filename){
        c = Segmentation_GUI(filename);
        gtk_text_buffer_set_text(TextBuffer, (const gchar *) c, (gint) -1);
    }



}
void on_BT_TRAIN_clicked()
{
    train();
}

void on_BT_XOR_clicked()
{
    xor();
}


void on_BT_CHOOSE_file_set(GtkFileChooserButton *f)
{
    filename =  gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f));
    printf("%s\n", filename);
    printf("folder name = %s\n", gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER(f)));
    char cmd[2048];
    FILE *f1;
    int j, h, v;//, hor = 150, ver = 1;

    if(previewImage)
        gtk_container_remove(GTK_CONTAINER (fixed_stk0), previewImage);//remove old image

    sprintf(cmd, "identify -format %%wx%%h \"%s\"\n", filename);

    f1 = popen(cmd, "r");

    strcpy(cmd, "");
    fgets(cmd, 512, f1);
    fclose(f1);

    h = v = 1;

    if(strlen(cmd))
    {
        for(j = 0; j < (int)strlen(cmd)-1; j++) if (cmd[j] == 'x') break;
        if(cmd[j] == 'x')
        {
            cmd[j] = 0;
            sscanf(cmd, "%d", &h);
            sscanf(&cmd[j + 1], "%d", &v);
        }
    }

    if(h < 100 || v < 100)
    {
        printf("**** questionable image: %s\n", filename);
        return;
    }

    int width = 448;
    int height = 530;

    sprintf(cmd, "convert \"%s\" -resize %dx%d tmp.jpg", filename, width, height);
    system(cmd);

    //strcpy(filename, "tmp.jpg");

    sprintf(cmd, "identify -format %%wx%%h \"%s\"\n","tmp.jpg");
    f1 = popen(cmd, "r");
    strcpy(cmd, "");
    fgets(cmd, 512, f1);
    fclose(f1);

    if(strlen(cmd))
    {
        for(j = 0; j < (int)strlen(cmd)-1; j++) if (cmd[j] == 'x') break;
        if(cmd[j] == 'x')
        {
            cmd[j] = 0;
            sscanf(cmd, "%d", &v);
            sscanf(&cmd[j + 1], "%d", &v);
        }
    }


    previewImage = gtk_image_new_from_file("tmp.jpg");

    gtk_container_add(GTK_CONTAINER(fixed_stk0), previewImage);
    gtk_widget_show(previewImage);

    gtk_fixed_move(GTK_FIXED(fixed_stk0), previewImage, 0, 0);

    system("rm tmp.jpg");
}

void on_quit_clicked()
{
    system("rm -rv *.bmp");
    gtk_main_quit();
}

void on_save_clicked()
{

    GtkTextIter begin, end;
    gchar *text;

    gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(TextBuffer), &begin, (gint) 0);
    gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(TextBuffer), &end, (gint) -1);

    text =  gtk_text_buffer_get_text(GTK_TEXT_BUFFER(TextBuffer), &begin, &end, TRUE);
    printf("-------\n%s\n--------\n", text);
    FILE *file = fopen("results.txt", "w");
    fprintf(file, "%s", text);
    fclose(file);
    gtk_widget_hide(save);
}
void on_changed_text()
{
    printf("*** text changed\n");
    gtk_widget_show(save);
}

