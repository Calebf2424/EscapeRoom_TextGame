#include "Item.h"

Item::Item(std::string& name, std::string& description) : _name(name), _description(description) {}

std::string Item::getName() {
    return _name;
}

std::string Item::getDescription() {
    return _description;
}