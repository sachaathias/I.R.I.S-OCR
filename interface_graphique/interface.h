#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <signal.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
//#include <ctypes.c>
#include "../Tests/tests_functions.h"
#include "../XOR/xor.h"

int UI(int argc, char *argv[]);
void on_BT_START_clicked(GtkButton *b);
void on_BT_TRAIN_clicked(GtkButton* b);
void on_BT_XOR_clicked(GtkButton* b);
void on_BT_SHOW_clicked(GtkButton* b);
void on_BT_CHOOSE_file_set(GtkFileChooserButton *f);
void on_quit_clicked(GtkButton* b);

#endif
