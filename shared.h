#ifndef SHARED_H
#define SHARED_H

template <class T>
class Shared_ptr {
private:
    T* m;
    int* count;

public:
    Shared_ptr() : m(nullptr), count(nullptr) {}

     Shared_ptr(T* p) : m(p), count(new int(1)) {}

    Shared_ptr(const Shared_ptr& other) : m(other.m), count(other.count) {
        if (count) {
            ++(*count);
        }
    }

    Shared_ptr(Shared_ptr&& other)  : m(other.m), count(other.count) {
        other.m = nullptr;
        other.count = nullptr;
    }

    Shared_ptr& operator=(const Shared_ptr& other) {
        if (this != &other) {
            this->~Shared_ptr();
            m = other.m;
            count = other.count;
            if (count) {
                ++(*count);
            }
        }
        return *this;
    }
    ~Shared_ptr() {
        if(m&&--(*count)==0){
            delete m;
            delete count;
        }
    }
};

#endif // SHARED_H
