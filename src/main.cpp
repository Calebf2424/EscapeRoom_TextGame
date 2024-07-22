#include "Room.h"
#include "Item.h"

int main() {
    // Create rooms with descriptions, lock keys, and items
    Cell* cell = new Cell("You are in a dark cell with damp walls.", 1234);
    Hallway* hallway = new Hallway("You find yourself in a narrow hallway with flickering lights.", "tail");
    Cave* cave = new Cave("You enter a vast cave with echoes of dripping water.");
    Highway* highway = new Highway("You find yourself on the highway outside of the jail.");

    // Create RunRoom object and add rooms
    RunRoom game;
    game.addRoom(cell);
    game.addRoom(hallway);
    game.addRoom(cave);
    game.addRoom(highway);

    // Start the game
    game.start();

    // Cleanup dynamically allocated memory
    delete cell;
    delete hallway;
    delete cave;
    delete highway;

    return 0;
}
