#include "Room.h"
#include "Item.h"

int main() {
    // Create rooms with descriptions, lock keys, and items
    Cell* cell1 = new Cell("You are in a dark cell with damp walls.", 1234);
    Hallway* hallway = new Hallway("You find yourself in a narrow hallway with flickering lights.", "open");
    Cave* cave = new Cave("You enter a vast cave with echoes of dripping water.");

    // Create RunRoom object and add rooms
    RunRoom game;
    game.addRoom(cell1);
    game.addRoom(hallway);
    game.addRoom(cave);

    // Start the game
    game.start();

    // Cleanup dynamically allocated memory
    delete cell1;
    delete hallway;
    delete cave;

    return 0;
}
