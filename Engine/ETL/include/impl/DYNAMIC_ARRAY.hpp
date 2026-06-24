#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP



template <typename T>
class DYNAMIC_ARRAY
{
    private:


    float GROWTH_FACTOR = 1.5;          // This is the growthFactor by how much the Array size incrementation will be multiplied with (must be a pos value) 
    T* ARR;                             // This is the Array pointer
    size_t ELEMENT_COUNT;               // This is the ElementCount 
    size_t ELEMENT_COUNT_CAPACITY;      // This is the ElementCountCapacity it tells how much Memory is actually allocated that can be used to store "X" amount of Elements



    public:
    // NOTE: THESE ARE THE METHODS PROVIDED BY DYNAMIC_ARRAY

    DYNAMIC_ARRAY()
    {
        ARR = nullptr;
        ELEMENT_COUNT = 0;
        ELEMENT_COUNT_CAPACITY = 0;
    }

    DYNAMIC_ARRAY(size_t SIZE)
    {
        size_t ACTUAL_SIZE = static_cast<size_t>(std::ceil(SIZE * this->GROWTH_FACTOR));
        ARR = new T[ACTUAL_SIZE];

        this->ELEMENT_COUNT = SIZE;
        this->ELEMENT_COUNT_CAPACITY = ACTUAL_SIZE;
    }

    DYNAMIC_ARRAY(size_t SIZE, float GROWTH_FACTOR)
    {
        this->GROWTH_FACTOR = GROWTH_FACTOR;

        size_t ACTUAL_SIZE = static_cast<size_t>(std::ceil(SIZE * this->GROWTH_FACTOR));
        ARR = new T[ACTUAL_SIZE];

        this->ELEMENT_COUNT = SIZE;
        this->ELEMENT_COUNT_CAPACITY = ACTUAL_SIZE;
    }

    ~DYNAMIC_ARRAY()
    {
        delete[] ARR;
    }


    // NOTE: UNDER THIS COMMET THE UTILITY METHODS ARE PROVIDED

    T* DATA(){ return this->ARR; }
    size_t SIZE(){ return this->ELEMENT_COUNT; }
    
    void RE_SIZE(size_t NEW_SIZE)
    {
        if(NEW_SIZE > this->ELEMENT_COUNT_CAPACITY){
            size_t ACTUAL_SIZE = static_cast<size_t>(std::ceil(NEW_SIZE * this->GROWTH_FACTOR));
            T* NEW_ARR = new T[ACTUAL_SIZE];

            for(size_t i = 0; i < ELEMENT_COUNT; ++i)
            {
                NEW_ARR[i] = ARR[i];
            }

            this->ELEMENT_COUNT = NEW_SIZE;
            this->ELEMENT_COUNT_CAPACITY = ACTUAL_SIZE;

            delete[] this->ARR;
            this->ARR = NEW_ARR;
        } else {
            this->ELEMENT_COUNT = NEW_SIZE;
        }
    }

    // NOTE: ASIGN OPERATOR
    DYNAMIC_ARRAY<T>& operator=(DYNAMIC_ARRAY<T>& OTHER)
    {
        if(this == &OTHER) return *this;
        if(OTHER.SIZE() == this->SIZE()){
            T* THIS_DATA = this->DATA();

            for(size_t i = 0; i < OTHER.SIZE(); ++i)
            {
                THIS_DATA[i] = OTHER.DATA()[i];
            }


            this->ELEMENT_COUNT = OTHER.SIZE();
            return *this;
        } else {
            this->RE_SIZE(OTHER.SIZE());
            T* THIS_DATA = this->DATA();

            for(size_t i = 0; i < OTHER.SIZE(); ++i)
            {
                THIS_DATA[i] = OTHER.DATA()[i];
            }

            this->ELEMENT_COUNT = OTHER.SIZE();

            return *this;
        }
    }


    // NOTE: COPY CONSTRCUTOR
    DYNAMIC_ARRAY(DYNAMIC_ARRAY<T>& OTHER) : 
    DYNAMIC_ARRAY()
    {
        *this = OTHER;
    }
};

#endif