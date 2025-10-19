#include <iostream>
#include <vector> 
#include <string> 
#include <cctype>
#include <stdexcept>


class RottenEgg {
    public: 
    const char* what() const noexcept {
        return "You almost ate a rotten egg!";
    }
};

class RegularEgg {
    protected:
    std::string size;
    std::string flavor;


    public:
    RegularEgg() { size = "No clue"; flavor = "Regular";}
    RegularEgg(const std::string& s, const std::string& f) {
        size = s;
        flavor = f;
    }

    virtual ~RegularEgg() {} 
    std::string getSize() const {return size;}
    std::string fetFlavor() const {return flavor;}

    virtual void eatEgg() const =0;
};

class ScrambledEgg : public RegularEgg {
    public:
    ScrambledEgg() {
        size = "Medium";
        flavor = "Smooth";
    }
    void eatEgg() const override {
        std::cout << "This is a scrambled egg. It's soft and fluffy!" << std::endl;
    }
};

class BoiledEgg : public RegularEgg {
    public:
    BoiledEgg() {
        size = "Large";
        flavor = "Savory";
    }
    void eatEgg() const override{
        std::cout << "This is a boiled egg!" << std::endl;
    }
};


int main() {

}

