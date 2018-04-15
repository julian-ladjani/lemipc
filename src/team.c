/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	team source file
*/

#include "struct.h"

lemipc_team_t *get_team_by_id(int team_id, lemipc_team_t *teams)
{
	for (int i = 0; i < max_players; i++)
		if (teams[i].team_id == team_id &&
			teams[i].team_state != LEMIPC_TEAM_UNDEFINED)
			return (&(teams[i]));
	for (int i = 0; i < max_players; i++) {
		if (teams[i].team_state == LEMIPC_TEAM_UNDEFINED) {
			teams[i].color = i + 1;
			teams[i].team_state = LEMIPC_TEAM_DEFINED;
			teams[i].team_id = team_id;
			return (&(teams[i]));
		}
	}
	return (&(teams[0]));
}