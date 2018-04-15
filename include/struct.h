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

typedef struct lemipc_team_s {
	int team_id;
	int color;
	int nb_player;
	int nb_kill;
	lemipc_team_state_t team_state;
} lemipc_team_t;

typedef struct lemipc_vector_s {
	int x;
	int y;
} lemipc_vector_t;

typedef struct lemipc_player_s {
	lemipc_team_t *team;
	int team_id;
	char player_name;
	lemipc_vector_t pos;
	lemipc_player_state_t player_state;
} lemipc_player_t;

typedef struct lemipc_shared_struct_s {
	int nb_player;
	lemipc_player_t players[max_players];
	lemipc_team_t teams[max_players];
} lemipc_shared_struct_t;

typedef struct lemipc_local_struct_s {
	lemipc_type_t type;
	int player;
	lemipc_shared_struct_t *shared_struct;
	lemipc_controller_state_t controller_state;
	unsigned int team_number;
	int shm_id;
	int sem_id;
	int msg_id;
	key_t ftok_key;
} lemipc_local_struct_t;

#endif //PSU_LEMIPC_2017_STRUCT_H
