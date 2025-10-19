#include <iostream>
#include <vector> 
#include <string> 
#include <cctype>
#include <stdexcept>
#include <memory>


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

class Carton {
    private: 
    std::vector<std::unique_ptr<RegularEgg>> eggs;

    public: 
    void addEgg(std::unique_ptr<RegularEgg> egg) {
        if (eggs.size() < 12)
        eggs.push_back(std::move(egg));
        else 
        std::cout << "Carton = full" <<std::endl;
    }
    void nextEgg() {
        if (eggs.empty()) {
            std::cout << "No more eggs left!" << std::endl; 
        }
        return;
    }
    auto egg = std::move(eggs.back());
    eggs.pop_back();

    try {
        egg-> eatEgg();
    } catch (const RottenEgg& e) {
        std::cout << "Warning: " << e.what() << std::endl;
    }
};

int main() {
    Carton carton;
    
    carton.addEgg(std::make_unique<ScrambledEgg>());
    carton.addEgg(std::make_unique<BoiledEgg>());
    carton.addEgg(std::make_unique<RottenEgg>());

    carton.eatNextEgg();  
    carton.eatNextEgg(); 
    carton.eatNextEgg();  
    carton.eatNextEgg();  

    return 0;
}

