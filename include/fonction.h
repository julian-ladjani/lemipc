/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	fonction header file
*/

#ifndef PSU_LEMIPC_2017_FONCTION_H
#define PSU_LEMIPC_2017_FONCTION_H

#include "struct.h"

int initialize_controller(lemipc_local_struct_t *local_struct);
int initialize_ai(lemipc_local_struct_t *local_struct);

void *controller_loop(void *ptr);

void ai_loop(lemipc_local_struct_t *local_struct);
int rand_a_b(int a, int b);

void init_display();
void clean_display();
void display_players(lemipc_shared_struct_t *shared_struct);

#endif //PSU_LEMIPC_2017_FONCTION_H
