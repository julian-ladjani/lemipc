/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	controller source file
*/

#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include "struct.h"
#include "fonction.h"

int get_next_player(lemipc_shared_struct_t *shared_struct, int offset)
{
	if (offset >= max_players)
		offset = 0;
	while (offset < max_players) {
		if (shared_struct->players[offset].player_state ==
			LEMIPC_PLAYER_RUNNING)
			return (offset);
		offset++;
	}
	return (0);
}

static void wait_player(lemipc_local_struct_t *local_struct, int player)
{
	lemipc_shared_struct_t *shared_struct = local_struct->shared_struct;
	lemipc_player_t *player_struct =
		&(shared_struct->players[local_struct->player]);

	semctl(local_struct->sem_id, 0, SETVAL, player);
	while (semctl(local_struct->sem_id, 0, GETVAL, 0) != max_players &&
		player_struct->player_state == LEMIPC_PLAYER_RUNNING) {
		usleep(10);
	}
}

void *controller_loop(void *ptr)
{
	lemipc_local_struct_t *local_struct = ptr;
	int current_player = max_players;

	local_struct->controller_state = LEMIPC_CONTROLLER_RUNNING;
	usleep(100);
	init_display();
	while (local_struct->shared_struct->nb_player > 0) {
		display_players(local_struct->shared_struct);
		current_player = get_next_player(local_struct->shared_struct,
			current_player + 1);
		wait_player(local_struct, current_player);
		usleep(5000);
	}
	shmctl(local_struct->shm_id, IPC_RMID, NULL);
	msgctl(local_struct->msg_id, IPC_RMID, NULL);
	semctl(local_struct->sem_id, 0, IPC_RMID);
	clean_display();
	local_struct->controller_state = LEMIPC_CONTROLLER_STOP;
	return (NULL);
}