#include "Room.h"

// Room class implementations
Room::Room(const std::string& description, bool canExit) : _description(description), _canExit(canExit) {}
Room::~Room() {}

void Room::showInventory() {
    std::cout << "Inventory:" << std::endl;
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
    std::cout << "1. Show inventory "<< std::endl;
    std::cout << "2. " << std::endl;
    std::cout << "3. " << std::endl;
    std::cout << "4. " << std::endl;
    std::cout << "5. " << std::endl;
}

void Cell::actions() {
    int choice = playerChoice(1, 6);
    switch (choice) {
        case 1:
            showInventory(_items);
            break;
        case 2:
        //choice 2 code;
            break;
        case 3:
            break;
        //choice 3 code;
        case 4:
        //choice 4 code;
            break;
        case 5:
        //choice 5 code;
            break;
        case 6:
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
