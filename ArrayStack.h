#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <iostream>
#include <ostream>
#include <vector>
#include <stdexcept>

template <typename T>
class ArrayStack {
private:
    std::vector<T> data;

public:
    void push(const T& value) {
        // TODO
        data.push_back(value);  // adds to the back of the stack which is the top of the stack
    }

    void pop() {
        // TODO
        //safety check to see if stack is empty so error doesn't happen
        if (data.empty()) {
            throw std::out_of_range("ArrayStack is empty");  //throw stops the program
        }
        data.pop_back();  //removes from the back of the stack which is the top of the stack
    }

    T top() const {
        // TODO
        //safety check to see if stack is empty so error doesn't happen
        if (data.empty()) {
            throw std::out_of_range("ArrayStack is empty");  //throw stops the program
        }
        return data.back();  //returns data
    }

    bool empty() const {
        // TODO
        return data.empty();  //returns true or false
    }

    int size() const {
        // TODO
       return data.size();  //returns size
    }
};

#endif
