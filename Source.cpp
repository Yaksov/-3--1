#include <iostream>
#include <vector>
#include <memory>
#include <type_traits>

class Part {
protected:
    Part() {
        std::cout << "Part created.\n";
    }

public:
    virtual ~Part() {
        std::cout << "Part destroyed.\n";
    }

    virtual void display() const = 0;

    template <typename T>
    static std::shared_ptr<T> create() {
        static_assert(std::is_base_of<Part, T>::value, "T must derive from Part");
        return std::shared_ptr<T>(new T());
    }
};

class Assembly : public Part {
protected:
    Assembly() {
        std::cout << "Assembly created.\n";
    }

public:
    ~Assembly() override {
        std::cout << "Assembly destroyed.\n";
    }

    void display() const override {
        std::cout << "This is an Assembly.\n";
    }


    friend std::shared_ptr<Assembly> Part::create<Assembly>();
};

template <typename T, typename Container>
void createAndAdd(Container& container) {
    container.push_back(Part::create<T>());
}

int main() {
    std::vector<std::shared_ptr<Part>> storage;


    createAndAdd<Assembly>(storage);


    for (const auto& part : storage) {
        part->display();
    }

    return 0;
}

