#pragma once

#include "cell.h"
#include "client.h"

struct Ldc* ldc_new(void);
void ldc_insert(struct Ldc* p_list, void* p_data, int (*p_compare)(void* p_data1, void* p_data2));
void ldc_remove(struct Ldc* p_list, void* p_data, int (*p_compare)(void* p_data1, void* p_data2), void (*p_delete)(void* p_data));
int ldc_is_data_in_list(struct Ldc* p_list, void* p_data, int (*p_compare)(void* p_data1, void* p_data2));
void ldc_display_asc(struct Ldc* p_list, void (*p_display)(void* p_data));
void ldc_display_desc(struct Ldc* p_list, void (*p_display)(void* p_data));
void ldc_del(struct Ldc* p_list, void (*p_delete)(void* p_data));

struct Ldc {

	struct Cell* p_head;	// pointe vers la premiere cellule de la liste (cell fictive dont cell_prev est NULL)
	struct Cell* p_tail;  // pointe vers la derniere cellule de la liste (cell fictive dont cell_next est NULL)
	int length;			// indique le nombre de cellule dans la liste (y compris les 2 cellules fictives vides)

};