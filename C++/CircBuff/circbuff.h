#ifndef CIRC_BUFF_H
#define CIRC_BUFF_H
#include <stdint.h>
#include <stdlib.h>
#include <cstring>
#define uint unsigned int
/* A circular buffer that can me be make with any type of data including classes
all types that the circular buffer can store must have proper assignment and copy
operators as well as constructors and destructors so that the circ buffer is memory safe
for the buffer to be printed while storing a class the class must override their own << operator*/
template <typename T>
class circbuff
{
private:
    T *data;
    uint Head;
    uint Tail;
    uint buffsize;
    bool full;

public:
    // constructor and destructor -----------------------------------------------------------------------------------------
    // default size is 32 elements can be config to be whatever is needed
    circbuff(uint size = 32)
    {
        Head = 0;
        Tail = 0;
        full = false;
        data = new T[size];
        buffsize = size;
    }
    circbuff(const circbuff& other) // Copy constructor
    {
        Head = other.Head;
        Tail = other.Tail;
        buffsize = other.buffsize;
        full = other.full;
        data = new T[buffsize];
        std::memcpy(data,other.data,buffsize);

    }
    ~circbuff(void)
    {
        // protection from double free
        delete [] data;
    }
    // add to the circ buffer -----------------------------------------------------------------------------------------------
    // returns true unless buffer is full
    // if called when full will just return false and do nothing with data
    bool append(T input)
    {
        if (!full)
        {
            data[Head++] = input;
            Head = Head % buffsize;
            full = Head == Tail;
        }
        return !full;
    }

    // remove or read from circ buffer --------------------------------------------------------------------------------------
    
    // return next item in circ buffer
    // if item does not exist (is empty) will return 0
    T read(void)
    {
        if ((Head == Tail) && !full)
        {
            return 0;
        }
        full = false;
        uint OldTail = Tail++;
        Tail = Tail % buffsize;
        return data[OldTail];
    }
    // "flushes" the buffer, the data in the buffer is discarded and the buffer becomes empty
    void clear(void)
    {
        Head = 0;
        Tail = 0;
        full = false;
    }

    // read the buffer ------------------------------------------------------------------------------------------------------
    
    // true if buffer is full false otherwise
    bool isfull(void){
        return full;
    }
    // true if buffer is empty false otherwise
    bool isempty(void){
        return (Head == Tail) && (!full);
    }
    // operators ------------------------------------------------------------------------------------------------------------
    
    circbuff& operator=(const circbuff& other){
        delete[] data;
        data = new T[other.buffsize];
        std::memcpy(data,other.data,other.buffsize);
        Head = other.Head;
        Tail = other.Tail;
        buffsize = other.buffsize;
        full = other.full;
        return *this;
    }
    // function will print '~' for data that is not part of the buffer
    // may change this or have this be a setting that can be toggled in future
    friend std::ostream& operator<<(std::ostream& os, const circbuff& cb){
        os << '[';
        for (uint i = 0; i < cb.buffsize ; i++)
        {
            if (i == cb.Tail)
            {
                os<<"{T}->";
            }
            if (i == cb.Head)
            {
                os<<"<-{H}";
            }
            // properly print with both edge cases
            if (cb.Head >= cb.Tail)
            {
                if ((i >= cb.Tail && i < cb.Head))
                {
                    os << cb.data[i];
                }
                else
                {
                    os << '~';
                }
            }
            else
            {
                if ((i >= cb.Tail || i < cb.Head))
                {
                    os << cb.data[i];
                }
                else
                {
                    os << '~';
                }
            }
            if (i<cb.buffsize-1)
            {
                os<<',';
            }
        }
        os << ']';
        return os;
    }
    /* will output a circbuff that 
    size = size1 + size2
    and has the data such that tail -> data1,data2,< - head
    */
    circbuff& operator+(const circbuff& o){
        // init the new buffer
        buffsize = this->buffsize + o.buffsize;
        circbuff<T>& out = new circbuff<T>(buffsize);
        // copy data from circbuff 1
        for (uint i = this->Tail; i != this->Head; ++i%this->buffsize)
        {
            out.append(this->data[i]);
        }
        // copy data from circbuff 2
        for (uint i = o.Tail; i != o.Head; ++i%o.buffsize)
        {
            out.append(o.data[i]);
        }
        return out;
    }
};

#endif