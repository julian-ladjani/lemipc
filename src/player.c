/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	player source file
*/

#include "struct.h"

lemipc_player_t *get_player_by_pos(lemipc_player_t *players,
	int posx, int posy)
{
	for (int i = 0; i < max_players; i++) {
		if (players[i].pos.x == posx && players[i].pos.y == posy &&
			players[i].player_state != LEMIPC_PLAYER_STOP) {
			return (&(players[i]));
		}
	}
	return (NULL);
}

int get_player_team_by_pos(lemipc_player_t *players,
	int posx, int posy)
{
	lemipc_player_t *player = get_player_by_pos(players, posx, posy);

	if (player == NULL)
		return (-1);
	return (player->team_id);
}