#ifndef PLAYER_H
#define PLAYER_H

// Standard headers
#include <stdbool.h>

// Internal headers
#include "position.h"

// Structs

/**
 * A player is represented by a symbol and its current position in a field.
 */
typedef struct player* Player;

// Functions
Player new_player(char symbol);
void delete_player(Player player);

char get_player_symbol(Player player);
position_t get_player_position(Player player);
void set_player_position(Player player, position_t new_position);

bool equal_players(Player p1, Player p2);

#endif // PLAYER_H
