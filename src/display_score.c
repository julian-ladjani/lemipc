/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	display_score source file
*/

#include <ncurses.h>
#include "struct.h"
#include "fonction.h"

static void print_separator(int separator)
{
	if (separator == 1)
		printw(", ");
}

static void print_players(lemipc_player_t *players, int team_id,
	lemipc_team_t *teams)
{
	char separator = 0;
	lemipc_team_t *team;

	printw(" ");
	team = get_team_by_id(team_id, teams);
	attron(COLOR_PAIR(team->color));
	printw("(");
	for (int i = 0; i < max_players; i++) {
		if (players[i].player_state != LEMIPC_PLAYER_STOP &&
			players[i].team_id == team_id) {
			print_separator(separator);
			printw("%c", players[i].player_name);
			separator = 1;
		}
	}
	printw(")");
	attroff(COLOR_PAIR(team->color));
}

void print_score(lemipc_team_t *teams, int nb_player,
	lemipc_player_t *players)
{
	int posy_base_offset = map_width + 3;
	int posy_offset = map_width + 3;

	for (int i = 0; i < max_players; i++) {
		print_char_nb_times(map_lengh + 4, ' ', 0,
			posy_base_offset + i);
		if (teams[i].team_state != LEMIPC_TEAM_UNDEFINED) {
			mvprintw(posy_offset, 0,
				"## Team: %d, %d/%d player",
				teams[i].team_id, teams[i].nb_player,
				nb_player);
			print_players(players, teams[i].team_id, teams);
			printw(", %d kill", teams[i].nb_kill);
			print_char_nb_times(2, '#', map_lengh + 2,
				posy_offset);
			posy_offset++;
		}
	}
	print_char_nb_times(map_lengh + 4, '#', 0, posy_offset);
}