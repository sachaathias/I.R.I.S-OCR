#ifndef H_FILE
#define H_FILE

typedef struct s_List List;
struct s_List
{
    List *next; /* pointeur sur le reste de la liste */
    void *data; /* pointeur sur une donnée générique */
};

List *
list_create (void *data);

List *
list_prepend(List *old, void *data);

List *
list_append(List *list, void *data);

List *
list_remove_first(List *list);

void
list_destroy(List *list);

int
list_length(List *list);

#endif

