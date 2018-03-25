/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	constant header file
*/

#ifndef PSU_LEMIPC_2017_CONSTANT_H
#define PSU_LEMIPC_2017_CONSTANT_H

#include <unistd.h>

typedef enum lemipc_type_e {
	LEMIPC_AI,
	LEMIPC_CONTROLLER
} lemipc_type_t;

typedef enum lemipc_controller_state_e {
	LEMIPC_CONTROLLER_STOP,
	LEMIPC_CONTROLLER_RUNNING,
} lemipc_controller_state_t;

typedef enum lemipc_player_state_e {
	LEMIPC_PLAYER_STOP,
	LEMIPC_PLAYER_RUNNING,
	LEMIPC_PLAYER_PLAY,
} lemipc_player_state_t;

#define lemipc_ftok_id (13)
#define map_lengh (80)
#define map_width (40)
#define max_players (10)
#define lemipc_player_names "123456789ABCDEFGHIJKLMNOPKRSTUVWXYZ"

#endif //PSU_LEMIPC_2017_CONSTANT_H
