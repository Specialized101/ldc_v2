#include <iostream>
#include <stdlib.h>

#include "ldc.h"
#include "cell.h"
#include "client.h"


struct Ldc* ldc_new() {

	/* Allouer un espace memoire d'un pointeur d'objet de type Ldc */

	struct Ldc* p_new = (struct Ldc*)malloc(sizeof(*p_new));

	/* Verifier si la call à la fonction malloc a renvoyé une adresse */

	if (p_new != NULL) {

		/* Initialiser les données membres de la nouvelle liste */

		p_new->p_head = NULL;
		p_new->p_tail = NULL;
		p_new->length = 0;

	}

	/* Creer les cellules fictives de debut et fin de liste
	   Et recupérer les adresses retrournées dans les données membres correspondantes de la nouvelle liste */

	p_new->p_head = cell_new(NULL);
	p_new->p_tail = cell_new(NULL);

	if (p_new->p_head != NULL && p_new->p_tail != NULL) {

		/* Initialiser les données membres des 2 cellules fictives:
				  NULL <-- head <--> tail --> NULL
		   Incrementer la longueur de la liste apres chaque ajout de cellule */

		cell_pointing_each_other(p_new->p_head, p_new->p_tail);
		p_new->length = 2;

	}

	return p_new;

}

void ldc_insert(struct Ldc* p_list, void* p_data, int (*p_compare)(void* p_data1, void* p_data2)) {

	if (p_list == NULL) return;

	/* Verifier si les donnees que l'on souhaite inserer ne sont pas deja dans la liste */

	if (ldc_is_data_in_list(p_list, p_data, p_compare) == 1) {

		printf("\nLes donnees n'ont pas pu etre ajoutees, elles sont deja dans la liste.\n");
		return;

	}

	/* Rechercher la cellule courante = dont la clé est strictement supérieur à celle donnée en parametre
	Debuter la recherche à la cellule qui suit celle de tete de liste (head) */

	struct Cell* p_temp = cell_return_next(p_list->p_head);

	int found = 0;

	while (p_temp != p_list->p_tail && p_compare(p_data, cell_get_data(p_temp)) >= 0) {

		/* Passer à la cellule suivante */

		p_temp = cell_return_next(p_temp);

	}

	/* Creer une nouvelle cellule qui va contenir les donnees à inserer */

	struct Cell* p_new = cell_new(p_data);

	if (p_new != NULL) {

		/* Mettre à jour les chainages */

		cell_chaining_update_after_insertion(p_temp, p_new);

		/* Incrementer la longueur de la liste */

		p_list->length++;

	}

}

void ldc_remove(struct Ldc* p_list, void* p_data, int (*p_compare)(void* p_data1, void* p_data2), void (*p_delete)(void* p_data)) {

	if (p_list == NULL) return;

	/* Verifier si les donnees à supprimer sont dans la liste */

	if (ldc_is_data_in_list(p_list, p_data, p_compare) == 0) {
	
		printf("\nLes donnees n'ont pas pu etre supprimees, elles ne sont pas dans la liste.\n");
		return;
	
	}

	/* Rechercher la cellule contenant les donnees à supprimer:
	Debuter la recherche à la cellule suivant la tete de liste */

	struct Cell* p_temp = cell_return_next(p_list->p_head);
	int found = 0;

	/* Fin de boucle quand la cellule recherchée est trouvée ou que la cellule est cours n'existe pas */

	while (p_temp != NULL && found == 0) {

		/* Comparer les donnees */

		if (p_compare(p_data, cell_get_data(p_temp)) == 0) {

			/* Mettre à jour les chainages */

			cell_chaining_update_before_deletion(p_temp);

			/* Supprimer la cellule courante */

			cell_del(p_temp, p_delete);

			/* Decrementer la longueur de la liste */

			p_list->length--;

			/* Sortir de la boucle */

			found = 1;

		}
		else {

			/* Si les donnees ne correspondent pas, passer à la cellule suivante */

			p_temp = cell_return_next(p_temp);

		}

	}

}

int ldc_is_data_in_list(struct Ldc* p_list, void* p_data, int (*p_compare)(void* p_data1, void* p_data2)) {

	/* Demarrer la recherche de correspondance à la cellule suivante la cellule vide de tete de liste */

	struct Cell* p_temp = cell_return_next(p_list->p_head);

	int found = 0;

	/* Boucler autant de fois qu'il y a de donnees de la liste (-2 cellules vides) */

	for (int i = 0; i < p_list->length - 2; i++) {

		if (p_compare(p_data, cell_get_data(p_temp)) == 0) {

			/* Si les donnees correspondent -> sortie de boucle */

			found = 1;

		}

		/* Passer à la cellule suivante */

		p_temp = cell_return_next(p_temp);

	}

	/* return 0: Les donnees ne sont pas dans la liste
	   return 1: Les donnees sont dans la liste
	*/

	return found;

}

void ldc_display_asc(struct Ldc* p_list, void (*p_display)(void* p_data)) {

	/* Verifier si la liste existe et qu'elle contient au moins 1 donnee */

	if (p_list != NULL && p_list->length > 2) {

		/* Debuter l'affichage à la cellule suivant la tete de liste: la cellule contenant la premiere donnee */

		struct Cell* p_temp = cell_return_next(p_list->p_head);

		printf("\n**********AFFICHAGE ORDRE CROISSANT**********\n");

		/* Boucler autant de fois qu'il y a de cellules: longueur de liste moins 2 cellules fictives vides */

		for (int i = 0; i < p_list->length - 2; i++) {

			cell_display(p_temp, p_display);

			p_temp = cell_return_next(p_temp);

		}

	}
	else {

		printf("\nLa liste est vide.\n");

	}

}

void ldc_display_desc(struct Ldc* p_list, void (*p_display)(void* p_data)) {

	if (p_list != NULL && p_list->length > 2) {

		/* Debuter l'affichage à la cellule precendant la fin de liste: la cellule contenant la dernier donnee */

		struct Cell* p_temp = cell_return_prev(p_list->p_tail);

		printf("\n**********AFFICHAGE ORDRE DECROISSANT**********\n");

		for (int i = 0; i < p_list->length - 2; i++) {

			cell_display(p_temp, p_display);

			p_temp = cell_return_prev(p_temp);

		}

	}
	else {

		printf("\nLa liste est vide.\n");

	}

}

void ldc_del(struct Ldc* p_list, void (*p_delete)(void* p_data)) {

	if (p_list != NULL) {

		/* Debuter la suppression à la cellule suivant la tete de liste (premiere donnee) */

		struct Cell* p_temp = cell_return_next(p_list->p_head);

		/* Boucler autant de fois qu'il y a de cellule non vide, 0 si la liste est vide */

		for (int i = 0; i < p_list->length - 2; i++) {

			/* L'ordre des 3 operations suivantes est important:
			   Si on commencait par l'operation 3, lors de l'operation 2, le pointeur p_temp pointerait
			   vers une cellule ayant été supprimée (via cell_del(p_del))

			   1- Stocker le pointeur de la cellule en cours dans une variable intermediaire (del) */

			struct Cell* p_del = p_temp;

			/* 2- Passer à la cellule suivante */

			p_temp = cell_return_next(p_temp);

			/* 3- Supprimer la cellule courante */

			cell_del(p_del, p_delete);

		}

		/* Supprimer les cellules fictives de tete et de fin de liste */

		cell_del(p_list->p_head, NULL);
		cell_del(p_list->p_tail, NULL);

		/* Liberer l'espace memoire de la liste */

		free(p_list);
		p_list = NULL;

	}

}