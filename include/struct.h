/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	struct header file
*/

#ifndef PSU_LEMIPC_2017_STRUCT_H
#define PSU_LEMIPC_2017_STRUCT_H

#include <sys/ipc.h>
#include "constant.h"

typedef struct lemipc_player_s {
	unsigned int team_id;
	char player_name;
	lemipc_player_state_t player_state;
} lemipc_player_t;

typedef struct lemipc_shared_struct_s {
	char map[map_width][map_lengh + 1];
	int nb_player;
	lemipc_player_t players[max_players];
} lemipc_shared_struct_t;

typedef struct lemipc_local_struct_s {
	lemipc_type_t type;
	int player;
	char *path;
	int player_x;
	int player_y;
	lemipc_shared_struct_t *shared_struct;
	lemipc_controller_state_t controller_state;
	unsigned int team_number;
	int shm_id;
	int sem_id;
	int msg_id;
	key_t ftok_key;
} lemipc_local_struct_t;


#endif //PSU_LEMIPC_2017_STRUCT_H
