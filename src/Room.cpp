#include "Room.h"

// Room class implementations
Room::Room(const std::string& description, bool canExit) : _description(description), _canExit(canExit) {}
Room::~Room() {}

void Room::showInventory() {
    std::cout << "Inventory:" << std::endl;
    if (_items.empty()) {
      std::cout << "Inventory is empty" << std::endl;
    }
    for (const auto& item : _items) {
        std::cout << "- " << item->getName() << item->getDescription() << std::endl;
    }
}

void Room::addToInventory(Item* item) {
    _items.push_back(item);
}

int Room::playerChoice(int min, int max) {
    int choice;
    do {
        std::cout << "Enter your choice (" << min << "-" << max << "): ";
        std::cin >> choice;
    } while (choice < min || choice > max);
    return choice;
}

void Room::unlockExit() {
    _canExit = true;
}

// Cell class implementations
Cell::Cell(const std::string& description, int lockKey) : Room(description), _lockKey(lockKey) {}

void Cell::roomDescription() const {
    std::cout << _description << std::endl;
}

void Cell::showPlayerOptions() {
    std::cout << "Make your choice to explore:" << std::endl;
    std::cout << "1. Show inventory-"<< std::endl;
    std::cout << "2. Inspect Rock on ground:" << std::endl;
    std::cout << "3.  Talk to old man sitting in the corner" << std::endl;
    std::cout << "4. Check clock" << std::endl;
    std::cout << "5. Attempt to unlock lock on door- " << std::endl;
}

void Cell::actions() {
    int choice = playerChoice(1, 4);
    switch (choice) {
        case 1:
            showInventory();
            break;
        case 2:
            "The rock appears to be stuck to the ground, you notice the numbers 123 scratched in" << std::endl;
            break;
        case 3:
            "The old man stares blankly at you" << std::endl;
            break;
        case 4:
            "The clock appears to have froze on 4am" << std::endl;
            break;
        case 5:
            int attempt;
            std::cout << "Enter the key to unlock: ";
            std::cin >> attempt;
            if (attempt == _lockKey) {
                unlockExit();
                std::cout << "Unlocked!" << std::endl;
            } else {
                std::cout << "Incorrect key!" << std::endl;
            }
            break;
    }
}

// Game class implementations
void Game::start() {
    _hasWon = false;
    std::cout << "Game started!" << std::endl;
}

void Game::end() {
    _hasWon = true;
    std::cout << "Game ended!" << std::endl;
}

// RunRoom class implementations
void RunRoom::addRoom(Room* room) {
    Node* newNode = new Node(room);
    if (!head) {
        head = newNode;
        current = head;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void RunRoom::start() {
    Game::start();
    current = head;
    while (current && !_hasWon) {
        move();
        if (current->room->_canExit) {
            current = current->next;
        }
    }
    Game::end();
}

void RunRoom::move() {
    if (current) {
        current->room->showPlayerOptions();
        current->room->actions();
    }
}
