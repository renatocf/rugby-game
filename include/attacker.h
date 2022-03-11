#ifndef ATTACKER_H
#define ATTACKER_H

// Internal headers
#include "position.h"
#include "spy.h"

// Functions

/**
 * Main algorithm to move Attacker player in a Game.
 * Given the player position, it should decide the next direction
 * they will take in the field.
 */
direction_t execute_attacker_strategy(position_t attacker_position,
                                      Spy defender_spy);

#endif // ATTACKER_H
