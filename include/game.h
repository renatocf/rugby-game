#ifndef GAME_H
#define GAME_H

// Internal headers
#include "dimension.h"
#include "field.h"
#include "player.h"

// Structs

/**
 * A game represents a field with two players: an attacker and a defender.
 * The attacker and the defender try to compete with each other.
 */
typedef struct game* Game;

// Functions
Game new_game(dimension_t field_dimension, size_t max_number_spies);
void delete_game(Game game);
void print_game(Game game);
void play_game(Game game, size_t max_turns);

#endif // GAME_H
