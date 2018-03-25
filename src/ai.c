/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	ai source file
*/

#include <stdlib.h>
#include "struct.h"

int rand_a_b(int a, int b)
{
	return (rand() % (b - a) + a);
}

static void wait_turn(lemipc_local_struct_t *local_struct)
{
	lemipc_shared_struct_t *shared_struct = local_struct->shared_struct;
	lemipc_player_t *player =
		&(shared_struct->players[local_struct->player]);

	while (player->player_state == LEMIPC_PLAYER_RUNNING)
		usleep(10);
}

static void ai_move(lemipc_local_struct_t *local_struct, int dir)
{
	switch (dir) {
		case 1:
			if (local_struct->player_x == 0)
				ai_move(local_struct, 2);
			local_struct->player_x--;
			break;
		case 2:
			if (local_struct->player_x >= map_width)
				ai_move(local_struct, 1);
			local_struct->player_x++;
			break;
		default:
			return;
	}
}

static void ai_turn(lemipc_local_struct_t *local_struct)
{
	lemipc_shared_struct_t *shared_struct = local_struct->shared_struct;
	lemipc_player_t *player =
		&(shared_struct->players[local_struct->player]);
	int dir = rand_a_b(0, 2);

	shared_struct->map[local_struct->player_y][local_struct->player_x]
		= ' ';
	ai_move(local_struct, dir);
	shared_struct->map[local_struct->player_y][local_struct->player_x]
		= player->player_name;
}

void ai_loop(lemipc_local_struct_t *local_struct)
{
	lemipc_shared_struct_t *shared_struct = local_struct->shared_struct;
	lemipc_player_t *player =
		&(shared_struct->players[local_struct->player]);

	while (player->player_state != LEMIPC_PLAYER_STOP) {
		wait_turn(local_struct);
		if (player->player_state == LEMIPC_PLAYER_STOP)
			break;
		ai_turn(local_struct);
		if (player->player_state == LEMIPC_PLAYER_STOP)
			break;
		player->player_state = LEMIPC_PLAYER_RUNNING;
	}
	shared_struct->map[local_struct->player_y][local_struct->player_x]
		= ' ';
	shared_struct->nb_player--;
}