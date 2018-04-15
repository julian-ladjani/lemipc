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

void stop_all_players(lemipc_shared_struct_t *shared_struct);
void *controller_loop(void *ptr);

void ai_loop(lemipc_local_struct_t *local_struct);
int rand_a_b(int a, int b);

void init_display();
void clean_display();
void display_players(lemipc_shared_struct_t *shared_struct);
void print_char_nb_times(int nb_char, char c, int posx, int posy);
void print_score(lemipc_team_t *teams, int nb_player,
	lemipc_player_t *players);

lemipc_team_t *get_team_by_id(int team_id, lemipc_team_t *teams);

lemipc_player_t *get_player_by_pos(lemipc_player_t *players,
	int posx, int posy);
int get_player_team_by_pos(lemipc_player_t *players,
	int posx, int posy);
int check_dead_first_player(lemipc_player_t *players,
	lemipc_player_t *player);
lemipc_vector_t *get_shortest_enemy(lemipc_player_t *players,
	lemipc_player_t *player);
lemipc_vector_t *get_shortest_friend(lemipc_player_t *players,
	lemipc_player_t *player);
double distance(double x1, double y1, double x2, double y2);
void ai_algo(lemipc_player_t *player, lemipc_player_t *players);

#endif //PSU_LEMIPC_2017_FONCTION_H
