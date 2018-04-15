/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	initializer source file
*/

#include <pthread.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <string.h>
#include "fonction.h"

static void initialise_shared_struct(lemipc_local_struct_t *local_struct)
{
	lemipc_shared_struct_t *shared_struct = local_struct->shared_struct;

	memset(shared_struct->players, 0,
		max_players * sizeof(lemipc_player_t));
	memset(shared_struct->teams, 0,
		max_players * sizeof(lemipc_team_t));
	shared_struct->nb_player = 1;
}

int initialize_controller(lemipc_local_struct_t *local_struct)
{
	pthread_t tid;

	local_struct->sem_id = semget(local_struct->ftok_key, 1,
		IPC_CREAT | SHM_R | SHM_W);
	local_struct->msg_id = msgget(local_struct->ftok_key,
		IPC_CREAT | SHM_R | SHM_W);
	local_struct->shm_id = shmget(local_struct->ftok_key,
		sizeof(lemipc_shared_struct_t), IPC_CREAT | SHM_R | SHM_W);
	if (local_struct->shm_id == -1)
		return (84);
	local_struct->shared_struct = shmat(
		local_struct->shm_id, NULL, SHM_R | SHM_W);
	if (local_struct->shared_struct == NULL)
		return (84);
	semctl(local_struct->sem_id, 0, SETVAL, max_players);
	initialise_shared_struct(local_struct);
	if (pthread_create(&tid, NULL, controller_loop, local_struct) != 0)
		return (84);
	return (0);
}

static int get_empty_player(lemipc_shared_struct_t *shared_struct)
{
	for (int i = 0; i < max_players; i++) {
		if (shared_struct->players[i].player_state ==
			LEMIPC_PLAYER_STOP)
			return (i);
	}
	return (-1);
}

static void initialize_player(lemipc_local_struct_t *local_struct,
	int player, unsigned int team_id)
{
	lemipc_shared_struct_t *shared_struct = local_struct->shared_struct;

	shared_struct->players[player].player_name =
		lemipc_player_names[player];
	shared_struct->players[player].player_state = LEMIPC_PLAYER_RUNNING;
	shared_struct->players[player].team = get_team_by_id(team_id,
		shared_struct->teams);
	shared_struct->players[player].team->nb_player++;
	shared_struct->players[player].team_id =
		shared_struct->players[player].team->team_id;
	shared_struct->players[player].pos.x = rand_a_b(0, map_lengh - 1);
	shared_struct->players[player].pos.y = rand_a_b(0, map_width - 1);
}

int initialize_ai(lemipc_local_struct_t *local_struct)
{
	if (local_struct->type != LEMIPC_CONTROLLER) {
		local_struct->sem_id = semget(local_struct->ftok_key, 1,
			SHM_R | SHM_W);
		local_struct->msg_id = msgget(local_struct->ftok_key,
			SHM_R | SHM_W);
		local_struct->shm_id = shmget(local_struct->ftok_key,
			sizeof(lemipc_shared_struct_t), SHM_R | SHM_W);
	}
	local_struct->shared_struct = shmat(
		local_struct->shm_id, NULL, SHM_R | SHM_W);
	local_struct->player = get_empty_player(local_struct->shared_struct);
	if (local_struct->player == -1)
		return (84);
	initialize_player(local_struct,
		local_struct->player, local_struct->team_number);
	if (local_struct->type != LEMIPC_CONTROLLER)
		local_struct->shared_struct->nb_player++;
	ai_loop(local_struct);
	return (0);
}