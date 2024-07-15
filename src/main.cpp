//test
//toBeChanged
#include "Room.h"
#include "Item.h"

int main() {
    // Create items
    Item* key1 = new Item("Key", "A small rusty key.");
    Item* key2 = new Item("Golden Key", "A shiny golden key.");

    // Create rooms with descriptions, lock keys, and items
    Cell* cell1 = new Cell("You are in a dark cell with damp walls.", 1234);
    Cell* cell2 = new Cell("You are in a brighter cell with a window.", 5678);
    
    // Add items to rooms
    cell1->addToInventory(key1);
    cell2->addToInventory(key2);

    // Create RunRoom object and add rooms
    RunRoom game;
    game.addRoom(cell1);
    game.addRoom(cell2);

    // Start the game
    game.start();

    // Cleanup dynamically allocated memory
    delete key1;
    delete key2;
    delete cell1;
    delete cell2;

    return 0;
}
