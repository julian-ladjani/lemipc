/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	ai_algo source file
*/

#include "struct.h"
#include "fonction.h"

lemipc_dir_t get_dir(lemipc_player_t *player, int posx, int posy, int dir)
{
	if (dir == 1 && player->pos.x < (posx - 1))
		return (LEMIPC_UP);
	if (dir == 2 && player->pos.x > (posx + 1))
		return (LEMIPC_DOWN);
	if (dir == 3 && player->pos.y > (posy + 1))
		return (LEMIPC_LEFT);
	if (dir == 4 && player->pos.y < (posy - 1))
		return (LEMIPC_RIGHT);
	return (LEMIPC_NONE);
}

int check_dir(lemipc_player_t *players, lemipc_dir_t dir, int posx, int posy)
{
	if (dir == LEMIPC_UP)
		posx++;
	if (dir == LEMIPC_DOWN)
		posx--;
	if (dir == LEMIPC_RIGHT)
		posy++;
	if (dir == LEMIPC_LEFT)
		posy--;
	if (get_player_by_pos(players, posx, posy) == NULL &&
		posx >= 0 && posx < map_lengh &&
		posy >= 0 && posy < map_width)
		return (1);
	return (0);
}

void goto_dir(lemipc_player_t *player, lemipc_dir_t dir)
{
	if (dir == LEMIPC_UP)
		player->pos.x++;
	if (dir == LEMIPC_DOWN)
		player->pos.x--;
	if (dir == LEMIPC_RIGHT)
		player->pos.y++;
	if (dir == LEMIPC_LEFT)
		player->pos.y--;
}

void goto_pos(lemipc_player_t *player, int posx, int posy,
	lemipc_player_t *players)
{
	lemipc_dir_t dir = LEMIPC_NONE;

	for (int i = 3; i >= 0; i--) {
		dir = get_dir(player, posx, posy, i);
		if (dir != LEMIPC_NONE && check_dir(players, dir,
			player->pos.x, player->pos.y) == 1) {
			goto_dir(player, dir);
			return;
		}
	}
}

void ai_algo(lemipc_player_t *player, lemipc_player_t *players)
{
	lemipc_vector_t *friend_pos = get_shortest_friend(players, player);
	lemipc_vector_t *enemy_pos = get_shortest_enemy(players, player);

	if (friend_pos != NULL && distance(friend_pos->x, friend_pos->y,
		player->pos.x, player->pos.y) > 2) {
		goto_pos(player, friend_pos->x, friend_pos->y, players);
		return;
	}
	if (friend_pos != NULL && distance(friend_pos->x, friend_pos->y,
		player->pos.x, player->pos.y) < 2) {
		if (enemy_pos != NULL && distance(enemy_pos->x, enemy_pos->y,
			player->pos.x, player->pos.y) > 1) {
			goto_pos(player, enemy_pos->x, enemy_pos->y, players);
			return;
		}
	}
}