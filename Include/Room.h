#ifndef ROOM_H
#define ROOM_H

#include "Item.h"
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

void clearScreen();

class Room {
public:
    Room(const std::string& description, bool canExit = false, bool lose = false);
    virtual ~Room();
    virtual void roomDescription() const = 0;
    virtual void showPlayerOptions() = 0;
    virtual void actions() = 0;
    void showInventory();
    void addToInventory(Item* item);
    int playerChoice(int min, int max);
    void unlockExit();
    bool canExit() const { return _canExit; }
    bool hasLost() const { return lose; }

protected:
    std::string _description;
    std::vector<Item*> _items;
    int _choice;
    bool _canExit;
    bool lose;
};

class Cell : public Room {
public:
    Cell(const std::string& description, int lockKey, bool canExit = false, bool lose = false);
    void roomDescription() const override;
    void showPlayerOptions() override;
    void actions() override;

private:
    int _lockKey;
};

class Hallway : public Room {
public:
    Hallway(const std::string& description, const std::string& passPhrase, bool canExit = false, bool lose = false);
    void roomDescription() const override;
    void showPlayerOptions() override;
    void actions() override;

private:
    std::string _passPhrase;
    int _numGuesses = 0;
};

class Cave : public Room {
public:
    Cave(const std::string& description, bool canExit = false, bool lose = false);
    ~Cave();
    void roomDescription() const override;
    void showPlayerOptions() override;
    void actions() override;

private:
    Item* _key;
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
