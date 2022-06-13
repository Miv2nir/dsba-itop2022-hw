#ifndef APP_H
#define APP_H

#include <string>
struct App
{
   public:
    std::string name;
    std::string category;
    float rating;
    int reviews_count;
    float size;
    std::string installs;
    std::string type;
    float price;
    std::string update;
};

#endif  // APP_H
