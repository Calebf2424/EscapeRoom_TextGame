#include "Room.h"

// Room class implementations
Room::Room(const std::string& description, bool canExit, bool lose)
    : _description(description), _canExit(canExit), lose(lose) {}

Room::~Room() {}

void Room::showInventory() {
    std::cout << "Inventory:" << std::endl;
    if (_items.empty()) {
        std::cout << "Inventory is empty" << std::endl;
    }
    for (const auto& item : _items) {
        std::cout << "- " << item->getName() << ": " << item->getDescription() << std::endl;
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
Cell::Cell(const std::string& description, int lockKey, bool canExit, bool lose)
    : Room(description, canExit, lose), _lockKey(lockKey) {}

void Cell::roomDescription() const {
    std::cout << _description << std::endl;
}

void Cell::showPlayerOptions() {
    std::cout << "Make your choice to explore:" << std::endl;
    std::cout << "1. Show inventory" << std::endl;
    std::cout << "2. Inspect rock on ground" << std::endl;
    std::cout << "3. Talk to old man sitting in the corner" << std::endl;
    std::cout << "4. Check clock" << std::endl;
    std::cout << "5. Attempt to unlock lock on door" << std::endl;
}

void Cell::actions() {
    int choice = playerChoice(1, 5);
    switch (choice) {
        case 1:
            showInventory();
            break;
        case 2:
            std::cout << "The rock appears to be stuck to the ground, you notice the numbers 123 scratched in." << std::endl;
            break;
        case 3:
            std::cout << "The old man stares blankly at you." << std::endl;
            break;
        case 4:
            std::cout << "The clock appears to have frozen at 4am." << std::endl;
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

Cave::~Cave() {
    delete _key;
}

// Hallway class implementations
Hallway::Hallway(const std::string& description, const std::string& passPhrase, bool canExit, bool lose)
    : Room(description, canExit, lose), _passPhrase(passPhrase) {}

void Hallway::roomDescription() const {
    std::cout << _description << std::endl;
}

void Hallway::showPlayerOptions() {
    std::cout << "Choose what you want to do:" << std::endl;
    std::cout << "1. Show inventory" << std::endl;
    std::cout << "2. Check words scratched on wall" << std::endl;
    std::cout << "3. Check stone on ground" << std::endl;
    std::cout << "4. Talk to rat in the corner" << std::endl;
    std::cout << "5. Try guessing password" << std::endl;
}

void Hallway::actions() {
    int choice = playerChoice(1, 5);
    switch (choice) {
        case 1:
            showInventory();
            break;
        case 2:
            std::cout << "You see scratched into the wall a curving line" << std::endl;
            break;
        case 3:
            std::cout << "You see a small note under the rock that says: \"remember to always wag with joy\"" << std::endl;
            break;
        case 4:
            std::cout << "The rat stares at you and moves its tail a bit." << std::endl;
            break;
        case 5:
            std::string attempt;
            std::cout << "Choose the passphrase to whisper in the speaker: (type all leters in lower case and ensure no extra spaces) "; //will add function to do this later, toLower, ignore extra spaces by using 2 pointer
            std::cin >> attempt;

            if (attempt == _passPhrase) {
                unlockExit();
                std::cout << "The light flashes green and the door unlocks!" << std::endl;
            } else if (_numGuesses >= 3) {
                std::cout << "An alarm starts flashing above your head and you hear the sound of guards coming to get you..." << std::endl;
                lose = true;
            } else {
                std::cout << "The light flashes red a few times... it didn't appear to set off any alarms." << std::endl;
                _numGuesses++;
            }
            break;
    }
}

// Cave class implementations
Cave::Cave(const std::string& description, bool canExit, bool lose)
    : Room(description, canExit, lose) {
        _key = new Item("Key", "A shiny silver key.");
    }

void Cave::roomDescription() const {
    std::cout << _description << std::endl;
}

void Cave::showPlayerOptions() {
    std::cout << "Choose what to do in the cave:" << std::endl;
    std::cout << "1. Show inventory" << std::endl;
    std::cout << "2. Go in the pool of water" << std::endl;
    std::cout << "3. Walk down dark path" << std::endl;
    std::cout << "4. Feel along wall" << std::endl;
}

void Cave::actions() {
    int choice = playerChoice(1, 4);
    switch (choice) {
        case 1:
            showInventory();
            break;
        case 2:
            std::cout << "You go to search if there's anything in the water and all of a sudden you are trapped..." << std::endl;
            lose = true;
            break;
        case 3:
            if (_items.empty()) {
                std::cout << "You walk down the path and notice something shiny on the ground... it's a key!" << std::endl;
                addToInventory(_key);
                std::cout << "Key added to inventory." << std::endl;
            } else {
                std::cout << "You walk down the path again... there doesn't appear to be anything else here." << std::endl;
            }
            break;
        case 4:
            if (_items.empty()) {
                std::cout << "You notice a keyhole on the wall; this could be your way out." << std::endl;
            } else {
                std::cout << "You used your key on the wall and a small door opened!" << std::endl;
                unlockExit();
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
    if (_hasWon) {
        std::cout << "You escaped to freedom!" << std::endl;
    } else {
        std::cout << "You failed to escape!" << std::endl;
    }
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
    while (current) {
        move();
        if (current->room->hasLost()) break; // Use getter to access lose
        if (current->room->canExit()) {  // Use getter to access _canExit
            if (!current->next) {
                _hasWon = true;
                break;
            }
            current = current->next;
        }
    }
    Game::end();
}

void RunRoom::move() {
    if (current) {
        current->room->roomDescription();
        current->room->showPlayerOptions();
        current->room->actions();
    }
}
