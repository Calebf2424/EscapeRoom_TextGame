//test
//toBeChanged
#include "Room.h"
#include "Item.h"

int main() {
    // Create rooms with descriptions, lock keys, and items
    Cell* cell1 = new Cell("You are in a dark cell with damp walls.", 1234);

    // Create RunRoom object and add rooms
    RunRoom game;
    game.addRoom(cell1);
    game.addRoom(cell2);

    // Start the game
    game.start();

    // Cleanup dynamically allocated memory
    delete cell1;

    return 0;
}
