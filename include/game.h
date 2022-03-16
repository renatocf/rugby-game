#ifndef GAME_H
#define GAME_H

// Internal headers
#include "position.h"
#include "direction.h"
#include "dimension.h"
#include "field.h"
#include "item.h"
#include "map.h"
#include "spy.h"

// Structs

/**
 * A game represents a field with two players: an attacker and a defender.
 * The attacker and the defender try to compete with each other.
 */
typedef struct game* Game;

/**
 * A player strategy is a function to determine the direction of a player
 * given its current position in a Field. Aditionally, players can spy
 * on its opponent positions **at most** MAX_NUMBER_SPIES times.
 */
typedef direction_t (*PlayerStrategy)(position_t, Spy);

// Functions
Game new_game(
    dimension_t field_dimension,
    size_t max_number_spies,
    PlayerStrategy attacker_strategy,
    PlayerStrategy defender_strategy);

Game new_game_from_map(
    Map map,
    size_t max_number_spies,
    PlayerStrategy attacker_strategy,
    PlayerStrategy defender_strategy);

void delete_game(Game game);
void print_game(Game game);
void play_game(Game game, size_t max_turns);

#endif // GAME_H
