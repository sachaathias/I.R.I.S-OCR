#include "interface.h"

GtkWidget *window_main;
GtkWidget *btnShowImage;
GtkWidget *btnSegmentation;
GtkWidget *btnTrain;
GtkWidget *btnStart;
GtkWidget *btnQuit;
GtkWidget *btnSelectFile;
GtkWidget *textBox;
GtkWidget *previewImage;
GtkWidget *fixed1;
GtkBuilder *builder;

char* filename = NULL;

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
    btnShowImage = GTK_WIDGET(gtk_builder_get_object(builder, "BT_SHOW"));
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));

    g_object_unref(builder);

    gtk_widget_show(window_main);

    gtk_main();

    return EXIT_SUCCESS;
}

void on_BT_START_clicked(GtkButton *b)
{
    if(filename)
        display_image_test(filename);
}
void on_BT_TRAIN_clicked(GtkButton* b)
{
    train();
}

void on_BT_XOR_clicked(GtkButton* b)
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
    int j, h, v, hor = 150, ver = 1;

    if(previewImage)
        gtk_container_remove(GTK_CONTAINER (fixed1), previewImage);//remove old image

    sprintf(cmd, "identify -format %%wx%%h \"%s\"\n", filename);

    f1 = popen(cmd, "r");

    strcpy(cmd, "");
    fgets(cmd, 512, f1);
    fclose(f1);

    h = v = 1;

    if(strlen(cmd))
    {
        for(j = 0; j<strlen(cmd)-1; j++) if (cmd[j] == 'x') break;
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
        for(j = 0; j<strlen(cmd)-1; j++) if (cmd[j] == 'x') break;
        if(cmd[j] == 'x')
        {
            cmd[j] = 0;
            sscanf(cmd, "%d", &v);
            sscanf(&cmd[j + 1], "%d", &v);
        }
    }


    previewImage = gtk_image_new_from_file("tmp.jpg");

    gtk_container_add(GTK_CONTAINER(fixed1), previewImage);
    gtk_widget_show(previewImage);

    gtk_fixed_move(GTK_FIXED(fixed1), previewImage, 617, 81);

    system("rm tmp.jpg");
}

void on_quit_clicked(GtkButton* b)
{
    gtk_main_quit();
}

