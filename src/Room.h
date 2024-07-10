#ifndef ROOM_H
#define ROOM_H

#include "Item.h"

#include <vector>
#include <iostream>
#include <string>

class Room {
 public:
    Room(const std::string& description, bool canExit);
    Room::~Room();
    virtual void roomDescription() const = 0;
    virtual void showPlayerOptions() = 0;
    virtual void actions() = 0;
    void showInventory(std::vector<Item*>& items);
    void addToInventory(std::vector<Item*>& items, Item* item);
    int playerChoice();
    void unlockExit();
 
 protected:
    std::string description;
    std::vector<Item*> items;
    int choice;
    bool canExit;
};


#endif //ROOM_H
