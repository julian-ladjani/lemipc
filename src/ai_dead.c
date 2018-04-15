/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	ai_dead source file
*/

#include <stdlib.h>
#include "struct.h"
#include "fonction.h"

int rand_a_b(int a, int b)
{
	return (rand() % (b - a) + a);
}

static int nb_times_in_array(int value, int *array, int size)
{
	int count = 0;

	for (int i = 0; i < size; i++) {
		if (array[i] == value)
			count++;
	}
	return (count);
}

int check_dead_first_player(lemipc_player_t *players,
	lemipc_player_t *player)
{
	lemipc_vector_t pos = player->pos;
	int around[8];

	around[0] = get_player_team_by_pos(players, pos.x + 1, pos.y);
	around[1] = get_player_team_by_pos(players, pos.x - 1, pos.y);
	around[2] = get_player_team_by_pos(players, pos.x, pos.y + 1);
	around[3] = get_player_team_by_pos(players, pos.x, pos.y - 1);
	around[4] = get_player_team_by_pos(players, pos.x + 1, pos.y + 1);
	around[5] = get_player_team_by_pos(players, pos.x - 1, pos.y + 1);
	around[6] = get_player_team_by_pos(players, pos.x + 1, pos.y - 1);
	around[7] = get_player_team_by_pos(players, pos.x - 1, pos.y - 1);
	for (int i = 0; i < 8; i++)
		if (around[i] > -1 &&
			nb_times_in_array(around[i], around, 8) > 1)
			return (around[i]);
	return (-1);
}