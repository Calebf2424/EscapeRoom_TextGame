#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    Item(std::string& _name, std::string& _description);
    std::string getName();
    std::string getDescription();

private:
    std::string _name;
    std::string _description;
};

#endif
