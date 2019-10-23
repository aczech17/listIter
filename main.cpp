#include <vector>
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class orderIterator :public std::vector<T>::iterator
{
//public: //DEBUG
    typedef typename std::vector<T>::iterator iterator;

    iterator current;
    std::vector<T>* owner;
public:
    T& operator*()
    {
        return *current;
    }
    explicit orderIterator(std::vector<T>& vec)
    {
        owner = &vec;
        current = owner->begin();
        for(auto i = owner->begin(); i!= owner->end(); ++i)
        {
            if(*i<*current) current = i;
        }
    }//CONSTRUCTOR
    orderIterator& operator++()
    {
        for(auto i = current+1; i!=owner->end(); ++i)
            if(*i == *current && i!=current)
            {
                current = i;
                return *this;
            }

        auto newCurrent = owner->begin();
        while(newCurrent != owner->end() && *newCurrent <= *current)
            newCurrent++;
        if(newCurrent == owner->end() )
        {
            current = owner->end();
            return *this;
        }

        for(auto i = owner->begin(); i!=owner->end(); ++i)
        {
            if(*i>*current && *i<*newCurrent)
                newCurrent = i;
        }
        current = newCurrent;
        return *this;
    }

    bool operator==(const iterator i) const
    {
        return current == i;
    }
    bool operator!=(const iterator i) const
    {
        return current != i;
    }
};

int main()
{
    std::vector <int> myVec{1,4,8,8};

    orderIterator<int> oi(myVec);
    while( oi != myVec.end() )
    {
        cout << *oi << " ";
        ++oi;
    }
}