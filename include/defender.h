#ifndef DEFENDER_H
#define DEFENDER_H

// Internal headers
#include "position.h"
#include "spy.h"

// Functions

/**
 * Main algorithm to move Defender player in a Game.
 * Given the player position, it should decide the next direction
 * they will take in the field.
 */
direction_t execute_defender_strategy(position_t defender_position,
                                      Spy attacker_spy);

#endif // DEFENDER_H
