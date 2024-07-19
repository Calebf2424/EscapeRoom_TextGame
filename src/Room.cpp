#include "Room.h"


//clear console
void clearScreen() {
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}
// Room class implementations
Room::Room(const std::string& description, bool canExit, bool lose)
    : _description(description), _canExit(canExit), lose(lose) {}

Room::~Room() {}

void Room::showInventory() {
    clearScreen();
    std::cout << "Inventory:\n";
    if (_items.empty()) {
        std::cout << "Inventory is empty\n";
    } else {
        for (const auto& item : _items) {
            std::cout << "- " << item->getName() << ": " << item->getDescription() << "\n";
        }
    }
    std::cout << "\n";
}

void Room::addToInventory(Item* item) {
    _items.push_back(item);
}

int Room::playerChoice(int min, int max) {
    int choice;
    while (true) {
        std::cout << "Enter your choice (" << min << "-" << max << "): ";
        std::cin >> choice;

        // Check if input is a number and within range
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any extra input
            return choice;
        }
    }
}

void Room::unlockExit() {
    _canExit = true;
}

// Cell class implementations
Cell::Cell(const std::string& description, int lockKey, bool canExit, bool lose)
    : Room(description, canExit, lose), _lockKey(lockKey) {}

void Cell::roomDescription() const {
    clearScreen();
    std::cout << _description << "\n";
}

void Cell::showPlayerOptions() {
    std::cout << "\nMake your choice to explore:\n";
    std::cout << "1. Show inventory\n";
    std::cout << "2. Inspect rock on ground\n";
    std::cout << "3. Talk to old man sitting in the corner\n";
    std::cout << "4. Check clock\n";
    std::cout << "5. Attempt to unlock lock on door\n";
}

void Cell::actions() {
    int choice = playerChoice(1, 5);
    switch (choice) {
        case 1:
            showInventory();
            break;
        case 2:
            std::cout << "The rock appears to be stuck to the ground, you notice the numbers 123 scratched in.\n";
            break;
        case 3:
            std::cout << "The old man stares blankly at you.\n";
            break;
        case 4:
            std::cout << "The clock appears to have frozen at 4am.\n";
            break;
        case 5:
            int attempt;
            std::cout << "Enter the key to unlock: ";
            std::cin >> attempt;
            if (attempt == _lockKey) {
                unlockExit();
                std::cout << "Unlocked!\n";
            } else {
                std::cout << "Incorrect key!\n";
            }
            break;
    }
    std::cout << "\n";
}

Cave::~Cave() {
    delete _key;
}

// Hallway class implementations
Hallway::Hallway(const std::string& description, const std::string& passPhrase, bool canExit, bool lose)
    : Room(description, canExit, lose), _passPhrase(passPhrase) {}

void Hallway::roomDescription() const {
    clearScreen();
    std::cout << _description << "\n";
}

void Hallway::showPlayerOptions() {
    std::cout << "Choose what you want to do:\n";
    std::cout << "1. Show inventory\n";
    std::cout << "2. Check words scratched on wall\n";
    std::cout << "3. Check stone on ground\n";
    std::cout << "4. Talk to rat in the corner\n";
    std::cout << "5. Try guessing password\n";
}

void Hallway::actions() {
    int choice = playerChoice(1, 5);
    switch (choice) {
        case 1:
            showInventory();
            break;
        case 2:
            std::cout << "You see scratched into the wall a curving line\n";
            break;
        case 3:
            std::cout << "You see a small note under the rock that says: \"remember to always wag with joy\"\n";
            break;
        case 4:
            std::cout << "The rat stares at you and moves its tail a bit.\n";
            break;
        case 5:
            std::string attempt;
            std::cout << "Choose the passphrase to whisper in the speaker: (type all leters in lower case and ensure no extra spaces) "; //will add function to do this later, toLower, ignore extra spaces by using 2 pointer
            std::cin >> attempt;

            if (attempt == _passPhrase) {
                unlockExit();
                std::cout << "The light flashes green and the door unlocks!\n";
            } else if (_numGuesses >= 3) {
                std::cout << "An alarm starts flashing above your head and you hear the sound of guards coming to get you...\n";
                lose = true;
            } else {
                std::cout << "The light flashes red a few times... it didn't appear to set off any alarms.\n";
                _numGuesses++;
            }
            break;
    }
    std::cout << "\n";
}

// Cave class implementations
Cave::Cave(const std::string& description, bool canExit, bool lose)
    : Room(description, canExit, lose) {
        _key = new Item("Key", "A shiny silver key.");
    }

void Cave::roomDescription() const {
    clearScreen();
    std::cout << _description << "\n";
}

void Cave::showPlayerOptions() {
    std::cout << "Choose what to do in the cave:\n";
    std::cout << "1. Show inventory\n";
    std::cout << "2. Go in the pool of water\n";
    std::cout << "3. Walk down dark path\n";
    std::cout << "4. Feel along wall\n";
}

void Cave::actions() {
    int choice = playerChoice(1, 4);
    switch (choice) {
        case 1:
            showInventory();
            break;
        case 2:
            std::cout << "You go to search if there's anything in the water and all of a sudden you are trapped...\n";
            lose = true;
            break;
        case 3:
            if (_items.empty()) {
                std::cout << "You walk down the path and notice something shiny on the ground... it's a key!\n";
                addToInventory(_key);
                std::cout << "Key added to inventory.\n";
            } else {
                std::cout << "You walk down the path again... there doesn't appear to be anything else here.\n";
            }
            break;
        case 4:
            if (_items.empty()) {
                std::cout << "You notice a keyhole on the wall; this could be your way out.\n";
            } else {
                std::cout << "You used your key on the wall and a small door opened!\n";
                unlockExit();
            }
            break;
    }
    std::cout << "\n";
}

// Game class implementations
void Game::start() {
    _hasWon = false;
    std::cout << "Game started!\n";
}

void Game::end() {
    if (_hasWon) {
        std::cout << "You escaped to freedom!\n";
    } else {
        std::cout << "You failed to escape!\n";
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
        
        std::cout << "Press Enter to continue..." << std::endl;
        if (std::cin.rdbuf()->in_avail() > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.get();
    }
}
