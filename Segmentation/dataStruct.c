#include <stdio.h>
#include <stdlib.h>
#include "dataStruct.h"


List *list_create (void *data)
{
	List *list = malloc(sizeof(list)); 
	// allocation (en vert sur le diagramme) et affectation
	// à la variable list (en bleu)
	if (list)  /* si l'allocation a réussi */
	{
		// affectation du champ data (en rouge) *
		list->data = data;

		//affectation du champ next à la liste vide */
		list->next = NULL;
	}
	return list;
}


List *list_prepend(List *old, void *data)
{
    List *list = list_create(data);
    if (list)
	list->next = old;
    return list;
}

List *list_append(List *list, void *data)
{
    List **plist = &list;
    while (*plist)
       plist = &(*plist)->next;
    *plist = list_create(data);
    if (*plist)
       return list;
    else
       return NULL;
}

List *
list_remove_first(List *list)
{
    List *first = list;
    list = list->next;
    free(first);
    return list;
}
void list_destroy(List *list)
{
    while (list)
       list = list_remove_first(list);
}

int list_length(List *list)
{
    int length = 0; 
    while (list)
     {
       length++;
       list = list->next;
     }
    return length;
}
int main()
{
	return 0;
}
