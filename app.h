#ifndef APP_H
#define APP_H

#include <string>
struct App
{
   public:
    std::string name;      //0
    std::string category;  //1
    float rating;          //2
    int reviews_count;     //3
    float size;            //4
    std::string installs;  //5
    std::string type;      //6
    float price;           //7
    std::string update;    //8
};

#endif  // APP_H
