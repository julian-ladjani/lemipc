/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	main source file
*/

#include <sys/shm.h>
#include <stdlib.h>
#include <signal.h>
#include "fonction.h"

static lemipc_local_struct_t local_struct;

static void get_shared_memory()
{
	local_struct.shared_struct = NULL;
	local_struct.shm_id = shmget(local_struct.ftok_key,
		sizeof(lemipc_shared_struct_t), SHM_R | SHM_W);
	if (local_struct.shm_id == -1)
		local_struct.type = LEMIPC_CONTROLLER;
	else
		local_struct.type = LEMIPC_AI;
}

static void wait_controller()
{
	while (local_struct.type == LEMIPC_CONTROLLER &&
		local_struct.controller_state == LEMIPC_CONTROLLER_RUNNING)
		usleep(100);
}

void sig_handler(int signo)
{
	if (signo == SIGINT) {
		if (local_struct.shared_struct == NULL)
			exit (84);
		local_struct.shared_struct->players[local_struct.player]
			.player_state = LEMIPC_PLAYER_STOP;
	}
}

int main(int ac, char **av)
{
	if (ac != 3 || atoi(av[2]) < 1)
		return (84);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (84);
	local_struct.ftok_key = ftok(av[1], lemipc_ftok_id);
	if (local_struct.ftok_key == -1)
		return (84);
	local_struct.path = av[1];
	local_struct.team_number = (unsigned int) atoi(av[2]);
	get_shared_memory();
	if (local_struct.type == LEMIPC_CONTROLLER)
		if (initialize_controller(&local_struct) == 84)
			return (84);
	if (initialize_ai(&local_struct) == 84)
		return (84);
	wait_controller();
	return (0);
}
