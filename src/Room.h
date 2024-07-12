#ifndef ROOM_H
#define ROOM_H

#include "Item.h"

#include <vector>
#include <iostream>
#include <string>

class Room {
 public:
    Room(const std::string& description, bool canExit = false);
    ~Room();
    virtual void roomDescription() const = 0;
    virtual void showPlayerOptions() = 0;
    virtual void actions() = 0;
    void showInventory(std::vector<Item*>& _items);
    void addToInventory(std::vector<Item*>& _items, Item* item);
    int playerChoice(int min, int max);
    void unlockExit();
 
 protected:
    std::string _description;
    std::vector<Item*> _items;
    int _choice;
    bool _canExit;
};








class Game {
 public:
   void start();
   void end();
   void move();

 private:
   bool _haswon
};

#endif //ROOM_H
