#ifndef STATIC_ARRAY_HPP
#define STATIC_ARRAY_HPP


template <typename T>
class StaticArray
{
    private:
    T* Arr;                         // This is the Array pointer
    size_t arraySize;               // This is the ElementCount 

    public:
    StaticArray(size_t size)
    {
        Arr = new T[size];
        arraySize = size;
    }

    ~StaticArray()
    {
        delete[] Arr;
    }

    T* GetArray()
    {
        return Arr;
    }

    T& operator[](size_t index)
    {
        if (index >= arraySize)
        {
            DEBUG_LOG("Index out of bounds !");
            throw std::out_of_range("Index out of range");
        }
        return Arr[index];
    }
};

#endif