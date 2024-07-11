#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class Item {
 public:
    Item(const std::string& name, const std::string& description);
    std::string getName() const;
    std::string getDescription() const;

 protected:
    std::string _name;
    std::string _desc;
};


#endif //Item_H
