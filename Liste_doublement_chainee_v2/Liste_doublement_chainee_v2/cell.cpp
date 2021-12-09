#include <stdlib.h>

#include "cell.h"

struct Cell* cell_new(void* p_data) {

	/* Allouer un espace memoire pour une nouvelle cellule */

	struct Cell* p_new = (struct Cell*)malloc(sizeof(*p_new));

	/* Verifier si la call malloc a fonctionné */

	if (p_new != NULL) {

		/* Initialiser les données membres de nouvelle cellule avec les donnees en parametre */

		p_new->p_data = p_data;
		p_new->p_next = NULL;
		p_new->p_prev = NULL;

	}

	return p_new;

}

void cell_pointing_each_other(struct Cell* p_head, struct Cell* p_tail) {

	p_head->p_next = p_tail;
	p_tail->p_prev = p_head;

}

struct Cell* cell_return_next(struct Cell* p_cell) {

	return p_cell->p_next;

}

struct Cell* cell_return_prev(struct Cell* p_cell) {

	return p_cell->p_prev;

}

void cell_chaining_update_after_insertion(struct Cell* p_current, struct Cell* p_new) {

	p_new->p_next = p_current;
	p_new->p_prev = p_current->p_prev;
	p_current->p_prev->p_next = p_new;
	p_current->p_prev = p_new;

}

void cell_chaining_update_before_deletion(struct Cell* p_cell) {

	/* Mettre à jour les chainages "comme si la cellule à supprimer n'existait plus"
					   1- La cellule qui suit la cellule courante (temp) doit pointer vers cell qui precede temp
					   2- La cellule qui precede temp doit pointer vers celle qui suit temp
	*/

	p_cell->p_next->p_prev = p_cell->p_prev;
	p_cell->p_prev->p_next = p_cell->p_next;

}

void* cell_get_data(struct Cell* p_cell) {

	return p_cell->p_data;

}

void cell_display(struct Cell* p_cell, void (*p_display)(void* p_data)) {

	p_display(p_cell->p_data);

}

void cell_del(struct Cell* p_cell, void (*p_del)(void* p_data)) {

	if (p_cell == NULL) return;

	/* Si p_del est NULL -> Cellule vide -> pas de donnee à supprimer */

	if (p_del != NULL)
		
		p_del(p_cell->p_data);

	free(p_cell);
	p_cell = NULL;

}