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
    std::cout << "1. Show inventory-" << std::endl;
    std::cout << "2. Inspect Rock on ground:" << std::endl;
    std::cout << "3. Talk to old man sitting in the corner" << std::endl;
    std::cout << "4. Check clock" << std::endl;
    std::cout << "5. Attempt to unlock lock on door- " << std::endl;
}

void Cell::actions() {
    int choice = playerChoice(1, 5);
    switch (choice) {
        case 1:
            showInventory();
            break;
        case 2:
            std::cout << "The rock appears to be stuck to the ground, you notice the numbers 123 scratched in" << std::endl;
            break;
        case 3:
            std::cout << "The old man stares blankly at you" << std::endl;
            break;
        case 4:
            std::cout << "The clock appears to have froze on 4am" << std::endl;
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

//Hallway class implementations
Hallway::Hallway(const std::string& description, std::string passPhrase) : Room(description), _passPhrase(passPhrase) {}

void Hallway::roomDescription() const {
    std::cout << _description << std::endl;
}

void Hallway::showPlayerOptions() {
    std::cout << "desc" << std::endl;
    std::cout << "1." << std::endl;
    std::cout << "2." << std::endl;
    std::cout << "3." << std::endl;
    std::cout << "4." << std::endl;
    std::cout << "5." << std::endl;
}

void Hallway::actions() {
    int choice = playerChoice(1, 5);
    switch (choice) {
        case 1:
            showInventory();
            break;
        case 2:
            std::cout << " " << std::endl;
            break;
        case 3:
            std::cout << " " << std::endl;
            break;
        case 4:
            std::cout << " " << std::endl;
            break;
        case 5:
            std::string attempt;
            std::cout << "Enter the the passphrase to whisper to the troll";
            std::cin >> attempt;
            if (attempt == tolower(_passPhrase)) {
                unlockExit();
                std::cout << "The troll lets you out!" << std::endl;
            } else {
                std::cout << "The troll stands there silently...." << std::endl;
            }
            break;
    }
}

//Cave implementations

Cave::Cave(const std::string& description) : Room(description) {}

void Cave::roomDescription() const {
    std::cout << _description << std::endl;
}

void Cave::showPlayerOptions() {
    std::cout << "desc" << std::endl;
    std::cout << "1." << std::endl;
    std::cout << "2." << std::endl;
    std::cout << "3." << std::endl;
    std::cout << "4." << std::endl;
    std::cout << "5." << std::endl;
}

void Cave::actions() {
    int choice = playerChoice(1, 5);
    switch (choice) {
        case 1:
            showInventory();
            break;
        case 2:
            std::cout << " " << std::endl;
            break;
        case 3:
            std::cout << " " << std::endl;
            break;
        case 4:
            std::cout << " " << std::endl;
            break;
        case 5:
            //checks if player has found the key and lets out if yes otherwise doesn't
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
