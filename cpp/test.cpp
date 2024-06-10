#include <iostream>
using namespace std;

class Human {
public:
    Human() {
        printf("%p conctruct1\n", this);
        size = 5;
        ages = new int[size];
        Fill_array();
    }

    Human(int size) {
        printf("%p conctruct2\n", this);
        this->size = size;
        ages = new int[size];
        Fill_array();
    }

    Human(const Human &other) {
        printf("%p copy\n", this);
        copy_array(other);
    }

    Human & operator=(const Human &other) {
        printf("%p operator\n", this);
        delete[] this->ages;
        copy_array(other);
        return *this;
    }

    ~Human() {
        printf("%p destruct\n", this);
        delete[] this->ages;
    }
    void Print() {
        printf("this: %p\nsize: %d\narr: ", this, size);
        for (int i = 0; i<size ; i++) {
            printf("%d ", ages[i]);
        }
        printf("\n");
    }

    typedef struct {
        const char* title;
        bool isActive;
    } Tab;

    Tab *list;
private:
    int *ages;
    int size;
    

    void Fill_array() {
        for (int i = 0; i<size ; i++) {
            ages[i] = i;
        }
    }

    void copy_array(const Human &other) {
        this->size = other.size;
        this->ages = new int[other.size];
        for (int i = 0; i<this->size ; i++) {
            this->ages[i] = other.ages[i];
        }
    }
};

void foo(Human human) {
    human.Print();
}

int main() {
    Human a(7);
    Human b = a;
    b.list = new Human::Tab[2] {
        { "Length", true}, 
        { "Temperature", false}, 
    };
    foo(b);
    
    delete[] b.list;
    return 0;
}