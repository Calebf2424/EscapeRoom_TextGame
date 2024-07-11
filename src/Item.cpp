#include "Item.h"

Item::Item(const std::string& name, const std::string& description) : _name(name), _description(description) {}

std::string Item::getName() const {
    return _name;
}

std::string Item::getDescription() const {
    return _description;
}