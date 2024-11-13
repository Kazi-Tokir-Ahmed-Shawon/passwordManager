
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

const int INITIAL_CAPACITY = 10;

template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;

    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray() : data(new T[INITIAL_CAPACITY]), capacity(INITIAL_CAPACITY), size(0) {}
    ~DynamicArray() { delete[] data; }

    void push_back(const T& item) {
        if (size == capacity) {
            resize();
        }
        data[size++] = item;
    }

    int getSize() const { return size; }

    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const { return data[index]; }

    void remove(int index) {
        if (index >= 0 && index < size) {
            for (int i = index; i < size - 1; ++i) {
                data[i] = data[i + 1];
            }
            --size;
        }
    }
};

#endif 
