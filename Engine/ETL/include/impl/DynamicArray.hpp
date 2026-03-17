#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cmath>

template <typename T>
class DynamicArray
{
    private:

    // Member variables of the DynamicArray Class

    float growthFactor = 1.5;       // This is the growthFactor by how much the Array size incrementation will be multiplied with (must be a pos value) 
    T* Arr;                         // This is the Array pointer
    size_t elementCount;            // This is the ElementCount 
    size_t elementCountCapacity;    // This is the ElementCountCapacity it tells how much Memory is actually allocated that can be used to store how many Elements

    size_t getActualSize(size_t size, float grwothFactor)
    {
        size_t actualSize = static_cast<size_t>(std::round(size * growthFactor));
        return actualSize;
    }

    void copyOldToNew(T* newArr)
    {
        for(size_t i = 0; i < elementCount; ++i)
        {
            newArr[i] = Arr[i];
        }
    }

    void safetyScale(float& scale)
    {
        if(scale < 1.0f)
        {
            scale = 1.0f;
        }
    }

    public:
     
    DynamicArray(size_t size)
    {
        safetyScale(this->growthFactor);
        size_t actualSize = getActualSize(size, this->growthFactor);
        Arr = new T[actualSize];
        elementCount = size;
        elementCountCapacity = actualSize;
    }

    DynamicArray(size_t size, float scaleFactor)
    {
        safetyScale(this->growthFactor);
        safetyScale(scaleFactor);
        this->growthFactor = scaleFactor;
        size_t actualSize = static_cast<size_t>(std::round(size * growthFactor));
        this->Arr = new T[actualSize];
        this->elementCount = size;
        elementCountCapacity = actualSize;
    }

    ~DynamicArray(){ delete[] Arr; }

    T* data(){ return this->Arr; }
    size_t size(){ return this->elementCount; }

    void resize(size_t resize)
    {
        T* NewArr;
        if(resize > elementCountCapacity)
        {
            size_t actualSize = getActualSize(resize, this->growthFactor);
            NewArr = new T[actualSize];
            copyOldToNew(NewArr);
            delete[] Arr;
            Arr = NewArr;
            elementCount = resize;
        } else{
            elementCount = resize;
        }
    }
};

#endif