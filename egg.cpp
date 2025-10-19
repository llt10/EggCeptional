#include <iostream>
#include <vector>
#include <string>
#include <memory>


class BadEggException {
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
    RegularEgg() { size = "Unknown"; flavor = "Plain"; }
    RegularEgg(const std::string& s, const std::string& f) {
        size = s;
        flavor = f;
    }

    virtual ~RegularEgg() {}

    std::string getSize() const { return size; }
    std::string getFlavor() const { return flavor; }

    virtual void eatEgg() const = 0;
};

class ScrambledEgg : public RegularEgg {
public:
    ScrambledEgg() {
        size = "Medium";
        flavor = "Smooth";
    }

    void eatEgg() const override {
        std::cout << "You eat the scrambled egg. It's soft and fluffy!\n";
    }
};

class BoiledEgg : public RegularEgg {
public:
    BoiledEgg() {
        size = "Large";
        flavor = "Savory";
    }

    void eatEgg() const override {
        std::cout << "You eat the boiled egg. It's firm and tasty!\n";
    }
};

class RottenEgg : public RegularEgg {
public:
    RottenEgg() {
        size = "Small";
        flavor = "Putrid";
    }

    void eatEgg() const override {
        throw BadEggException();
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
            std::cout << "Carton is full!\n";
    }

    void eatNextEgg() {
        if (eggs.empty()) {
            std::cout << "No more eggs left!\n";
            return;
        }

        auto egg = std::move(eggs.back());
        eggs.pop_back();

        try {
            egg->eatEgg();
        } catch (const BadEggException& e) {
            std::cout << "Warning: " << e.what() << "\n";
        }
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

