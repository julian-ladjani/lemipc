/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	ai source file
*/

#include <stdlib.h>
#include <sys/sem.h>
#include "struct.h"
#include "fonction.h"

static void wait_turn(lemipc_local_struct_t *local_struct)
{
	lemipc_shared_struct_t *shared_struct = local_struct->shared_struct;
	lemipc_player_t *player =
		&(shared_struct->players[local_struct->player]);

	while (semctl(local_struct->sem_id, 0, GETVAL, 0) !=
		local_struct->player &&
		player->player_state == LEMIPC_PLAYER_RUNNING) {
		usleep(10);
	}
}

static void ai_turn(lemipc_local_struct_t *local_struct)
{
	lemipc_shared_struct_t *shared_struct = local_struct->shared_struct;
	lemipc_player_t *player =
		&(shared_struct->players[local_struct->player]);

	ai_algo(player, shared_struct->players);
}

void increase_team_kill(lemipc_team_t *team)
{
	team->nb_kill++;
}

void ai_in_loop(lemipc_local_struct_t *local_struct)
{
	lemipc_shared_struct_t *shared_struct = local_struct->shared_struct;
	lemipc_player_t *player =
		&(shared_struct->players[local_struct->player]);
	int dead = 0;

	wait_turn(local_struct);
	dead = check_dead_first_player(shared_struct->players,
		player);
	if (dead > -1) {
		increase_team_kill(get_team_by_id(dead,
			shared_struct->teams));
		player->player_state = LEMIPC_PLAYER_STOP;
	}
	else
		ai_turn(local_struct);
	semctl(local_struct->sem_id, 0, SETVAL, max_players);
}

void ai_loop(lemipc_local_struct_t *local_struct)
{
	lemipc_shared_struct_t *shared_struct = local_struct->shared_struct;
	lemipc_player_t *player =
		&(shared_struct->players[local_struct->player]);

	while (player->player_state != LEMIPC_PLAYER_STOP) {
		ai_in_loop(local_struct);
	}
	player->team->nb_player--;
	if (player->team->nb_player == 0) {
		player->team->nb_kill = 0;
		player->team->team_state = LEMIPC_TEAM_UNDEFINED;
	}
	shared_struct->nb_player--;
}