#ifndef INTERFACE_H
#define INTERFACE_H

int UI(int argc, char *argv[]);
void on_BT_START_clicked(GtkButton *b);
void on_BT_TRAIN_clicked(GtkButton* b);
void on_BT_XOR_clicked(GtkButton* b);
void on_BT_SHOW_clicked(GtkButton* b);
void on_BT_CHOOSE_file_set(GtkFileChooserButton *f);
void on_quit_clicked(GtkButton* b);

#endif
