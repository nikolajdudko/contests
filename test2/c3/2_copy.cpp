#include <iostream>
#include <iomanip>


namespace numbers
{

struct item
{
    complex value;
    item *next;
    item *prev;
};

class complex_stack
{
    item *bot;
    item *top;
    size_t sz;

    void
    push(const complex& s)
    {
        if (top == NULL) {
            bot = top = new item;
            top->prev = NULL;
        } else {
            top->next = new item;
            top->next->prev = top;
            top = top->next;
        }
        top->next = NULL;
        top->value = s;
        sz++;
    }

public:

    void
    show() {
        item *tmp = bot;
        std::cout << std::endl;
        while (tmp->next != NULL) {
            std::cout << tmp->value.to_string() << std::endl;
            tmp = tmp->next;
        }
        std::cout << tmp->value.to_string() << std::endl;
        std::cout << std::endl;
    }

    complex_stack()
    {
        sz = 0;
        bot = NULL;
        top = NULL;
    }

    complex_stack(const complex& s): complex_stack()
    {
        (*this).push(s);
    }

    complex_stack(const complex_stack& smp): complex_stack()
    {
        for (int i = 0; i < (int)smp.sz; i++) {
            (*this).push(smp[i]);
        }
    }

    ~complex_stack() {
        while (bot != NULL && bot->next != NULL) {
            bot = bot->next;
            delete bot->prev;
        }
        if (bot != NULL) {
            delete bot; 
        }
    }
    
    const size_t size() const 
    {
        return sz;
    }

    const complex operator[](const int& i) const
    {
        item *tmp = bot;
        for (int j = i; j > 0; j--) {
            tmp = tmp->next;
        }
        return tmp->value;
    }
    
    const complex_stack operator<<(complex s) const
    {
        complex_stack a(*this);
        a.push(s);
        return a;
    }

    const complex operator+() const
    {
        return top->value;
    }

    const complex_stack operator~() const
    {
        complex_stack a(*this);
        item *tmp = a.top;
        a.top = a.top->prev;
        a.top->next = NULL;
        a.sz--;
        delete tmp;
        return a;
    }

//copy-and-swap
    const complex_stack operator=(complex_stack smp)
    {
        (*this).swap(smp);
        return *this;
    } 

private:
    void
    swap(complex_stack& smp) {

        item *tmp = bot;
        bot = smp.bot;
        smp.bot = tmp;

        tmp = top;
        top = smp.top;
        smp.top = tmp;

        size_t t = sz;
        sz = smp.sz;
        smp.sz = t;
    }
};
}
