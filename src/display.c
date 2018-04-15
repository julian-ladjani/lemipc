/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	display source file
*/

#include <ncurses.h>
#include "struct.h"
#include "fonction.h"

void init_display()
{
	initscr();
	noecho();
	curs_set(FALSE);
	start_color();
	init_color(8, 139, 72, 138);
	init_color(9, 211, 31, 87);
	init_pair(1, 0, COLOR_WHITE);
	init_pair(2, 1, COLOR_GREEN);
	init_pair(3, 2, COLOR_RED);
	init_pair(4, 3, COLOR_BLUE);
	init_pair(5, 4, COLOR_YELLOW);
	init_pair(6, 5, COLOR_CYAN);
	init_pair(7, 6, COLOR_MAGENTA);
	init_pair(8, 7, COLOR_BLUE);
	init_pair(9, 8, COLOR_WHITE);
	init_pair(10, 9, COLOR_WHITE);
}

void clean_display()
{
	endwin();
}

void print_char_nb_times(int nb_char, char c, int posx, int posy)
{
	move(posy, posx);
	for (int i = 0; i < nb_char; i++)
		addch(c);
}

void print_players(lemipc_shared_struct_t *shared_struct)
{
	lemipc_team_t *team;

	for (int i = 0; i < max_players; i++) {
		if (shared_struct->players[i].player_state !=
			LEMIPC_PLAYER_STOP) {
			team = get_team_by_id(
				shared_struct->players[i].team_id,
				shared_struct->teams);
			attron(COLOR_PAIR(team->color));
			print_char_nb_times(1,
				shared_struct->players[i].player_name,
				shared_struct->players[i].pos.x + 2,
				shared_struct->players[i].pos.y + 1);
			attroff(COLOR_PAIR(team->color));
		}
	}
}

void display_players(lemipc_shared_struct_t *shared_struct)
{
	int i;

	init_pair(max_players + 1, COLOR_BLUE, COLOR_BLUE);
	attron(COLOR_PAIR(max_players + 1));
	print_char_nb_times(map_lengh + 4, '#', 0, 0);
	print_char_nb_times(map_lengh + 4, '#', 0, map_width + 1);
	attroff(COLOR_PAIR(max_players + 1));
	for (i = 0; i < map_width; i++) {
		attron(COLOR_PAIR(max_players + 1));
		print_char_nb_times(2, '#', 0, i + 1);
		print_char_nb_times(2, '#', map_lengh + 2, i + 1);
		attroff(COLOR_PAIR(max_players + 1));
		print_char_nb_times(map_lengh, ' ', 2, i + 1);
		print_players(shared_struct);
	}
	print_char_nb_times(map_lengh + 4, '#', 0, map_width + 2);
	print_score(shared_struct->teams, shared_struct->nb_player,
		shared_struct->players);
	refresh();
}