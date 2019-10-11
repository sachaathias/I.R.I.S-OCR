#include <stdio>


// Declaration de la structurem file
typedef struct Element Element;
struct Element

{
	    int nombre;
	    Element *suivant;
};

typedef struct File File;
struct File
{
	Element *premier;
};

// Declaration de la methode Enfilage

void enfiler(File *file, int nvNombre)
{
	Element *nouveau = malloc(sizeof(*nouveau));
	if (file == NULL || nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	nouveau->nombre = nvNombre;
	nouveau->suivant = NULL;

	if (file->premier != NULL) /* La file n'est pas vide */
	{
		/* On se positionne à la fin de la file */
		Element *elementActuel = file->premier;
		while (elementActuel->suivant != NULL)
		{
			elementActuel = elementActuel->suivant;
		}

		elementActuel->suivant = nouveau;
	}

	else /* La file est vide, notre élément est le premier */
	{
		file->premier = nouveau;
	}
}

// Declaration de la methode Defilage

int defiler(File *file)
{
	if (file == NULL)
	{
		exit(EXIT_FAILURE);
	}
	int nombreDefile = 0;
	
	/* On vérifie s'il y a quelque chose à défiler */
	if (file->premier != NULL)
	{
		Element *elementDefile = file->premier;
		nombreDefile = elementDefile->nombre;
		file->premier = elementDefile->suivant;
		free(elementDefile);
	}
	return nombreDefile;
}
