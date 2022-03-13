#ifndef SPY_H
#define SPY_H

// Standard headers
#include <stddef.h>

// Internal headers
#include "player.h"
#include "position.h"

// Structs

/**
 * A spy allows retrieving the position of a player and counts
 * the number of accesses.
 */
typedef struct spy* Spy;

// Functions
Spy new_spy(Player player);
void delete_spy(Spy spy);

position_t get_spy_position(Spy spy);
size_t get_spy_number_uses(Spy spy);

#endif // SPY_H
