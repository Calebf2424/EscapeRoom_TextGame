#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    Item(const std::string& _name, const std::string& _description);
    std::string getName() const;
    std::string getDescription() const;

private:
    std::string _name;
    std::string _description;
};

#endif
