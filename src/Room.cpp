#include "Room.h"
#include "Item.h"
#include <limits>

Room::Room(const std::string& description, bool canExit)
    : _description(description), _canExit(canExit) {}

Room::~Room() {
    for (auto item : _items) {
        delete item;
    }
}

void Room::showInventory(std::vector<Item*>& _items) {
    for (auto item : _items) {
        std::cout << "name: " << item->getName() <<  "description: " << item->getDescription() << std::endl;
    }
}

void Room::addToInventory(std::vector<Item*>& _items, Item* item) {
    _items.push_back(item);
}

int Room::playerChoice(int min, int max) {
    int input;
    while (true) {
        std::cout << "Enter a number for action: ";
        std::cin >> input;

        if (std::cin.fail() || input < min || input > max) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
            std::cout << "Invalid input. Please try again." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any extra input
            return input;
        }
    }
}

void Room::unlockExit() {
    _canExit = true; 
}
