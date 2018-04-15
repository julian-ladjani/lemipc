/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	ai_distance source file
*/

#include <math.h>
#include "struct.h"

int distance(double x1, double y1, double x2, double y2)
{
	return ((int) hypot(x2 - x1, y2 - y1));
}

lemipc_vector_t *get_shortest_friend(lemipc_player_t *players,
	lemipc_player_t *player)
{
	lemipc_vector_t *short_pos = NULL;
	double short_distance = 999999;
	lemipc_vector_t pos = player->pos;

	for (int i = 0; i < max_players; i++) {
		if (players[i].team_id == player->team_id &&
			players[i].player_state != LEMIPC_PLAYER_STOP &&
			distance(pos.x, pos.y, player[i].pos.x, player[i]
				.pos.y) < short_distance) {
			short_distance = distance(pos.x, pos.y,
				player[i].pos.x, player[i].pos.y);
			short_pos = &(player[i].pos);
		}
	}
	return (short_pos);
}

lemipc_vector_t *get_shortest_enemy(lemipc_player_t *players,
	lemipc_player_t *player)
{
	lemipc_vector_t *short_pos = NULL;
	double short_distance = 99999;
	lemipc_vector_t pos = player->pos;

	for (int i = 0; i < max_players; i++) {
		if (players[i].team_id != player->team_id &&
			players[i].player_state != LEMIPC_PLAYER_STOP &&
			distance(pos.x, pos.y, player[i].pos.x, player[i]
				.pos.y) < short_distance) {
			short_distance = distance(pos.x, pos.y,
				player[i].pos.x, player[i].pos.y);
			short_pos = &(player[i].pos);
		}
	}
	return (short_pos);
}
