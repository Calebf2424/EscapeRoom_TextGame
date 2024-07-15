#ifndef ROOM_H
#define ROOM_H

#include "Item.h"

#include <vector>
#include <iostream>
#include <string>

class Room {
public:
    Room(const std::string& description, bool canExit = false);
    virtual ~Room();
    virtual void roomDescription() const = 0;
    virtual void showPlayerOptions() = 0;
    virtual void actions() = 0;
    void showInventory(std::vector<Item*>& _items);
    void addToInventory(std::vector<Item*>& _items, Item* item);
    int playerChoice(int min, int max);
    void unlockExit();
    bool _canExit;

protected:
    std::string _description;
    std::vector<Item*> _items;
    int _choice;
};

class Cell : public Room {
public:
    Cell(const std::string& description, int lockKey);
    void roomDescription() const override;
    void showPlayerOptions() override;
    void actions() override;

private:
    int _lockKey;
};

class Game {
public:
    virtual void start();
    virtual void end();
    virtual ~Game() = default;

protected:
    bool _hasWon;
};

class RunRoom : public Game {
public:
    void addRoom(Room* room);
    void start() override;
    void move();

private:
    struct Node {
        Room* room;
        Node* next;
        Node(Room* r) : room(r), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* current = nullptr;
};

#endif // ROOM_H
