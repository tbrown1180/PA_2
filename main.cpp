#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

#include "ArrayStack.h"

using namespace std;

// Token

struct Token {
    string value;   // number, operator, or parenthesis
};

// Tokenizer

vector<Token> tokenize(const string& line) {
    vector<Token> tokens;
    int i = 0;

    while (i < line.length()) {                                      //loops while i < the length of the line
        if (isspace(line[i])) {                                      //if there is a space in the line increase i
            i++;
        }
        else if (isdigit(line[i])) {                                 //checks if element at value i is a number
            string number = "";
            while (i < line.length() && isdigit(line[i])) {         //loops while i is < length of the line and is a number at that location
                number += line[i];
                i++;                                                //increment i so the loop doesn't loop forever
            }
            tokens.push_back({number});               //pushes number
        }
        else {                                                      // the else acknowledges () and special characters like +-*/ and makes a token
            string s(1, line[i]);
            tokens.push_back({s});
            i++;
        }
    }
    // TODO
    return tokens;
}

// Helpers

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    // TODO
    if (op == "+" || op == "-") {       //checks if operation is + or -
        return 1;
    }
    if (op == "*" || op == "/") {       //checks if operation is * or /
        return 2;
    }
    return 0;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    // TODO
    int stackSize = 0;

    for (const auto& t : tokens) {
        if (isdigit(t.value[0])) {                  //a number gets pushed to the stack
            stackSize++;                            //increase stack size when valid operand is added
        }
        else if (isOperator(t.value)) {
            if (stackSize < 2) {                    //checks if 2 operands are already on the stack
                return false;
                stackSize--;                        //reduce stack size if false isn't returned
            }
        }
        else {
            return false;                           //if it's not a number or an operator (invalid token) it returns false
        }
    }
    return stackSize == 1;                          //stack must be 1 because a valid expression produces one final result; n - k = 1
                                                    //EX) nums = 3 operators = 2;  123/* so this becomes 3-2=1
}

bool isValidInfix(const vector<Token>& tokens) {
    // TODO
    int balance = 0;                                //balance is used to keep track of the ( )
    bool expectOperand = true;                      //keeps track of what should come after a ( , whether it's another ) or a number

    for (const auto& t : tokens) {
        if (isdigit(t.value[0])) {                  //a number is valid if expecting an operand
            if (!expectOperand) {
                return false;
            }
            expectOperand = false;
        }
        else if (t.value == "(") {                  //if ( is expected and is true increase balance
            if (!expectOperand) {
                return false;
            }
            balance++;
        }
        else if (t.value == ")") {                  // ) can only come after an operand and if true decrease balance
            if (expectOperand) {
                return false;
            }
            balance--;
            if (balance < 0) {                      //if balance is < 0 then there are too many )
                return false;
            }
            expectOperand = false;
        }
        else if (isOperator(t.value)) {             //operator must come after a number or ) and after operator expect operand
            if (expectOperand) {
                return false;
            }
            expectOperand = true;
        }
        else {
            return false;
        }
    }

    return balance == 0 && !expectOperand;          //there is a right amount of () and ended on a number or )
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    // TODO
    ArrayStack<string> opStack;

    for (const auto& t : tokens) {
        if (isdigit(t.value[0])) {                     //pushes if there's a digit
            output.push_back(t);
        }
        else if (isOperator(t.value)) {                //checks the stack of operators and sees if there are others with equal or higher precedence and moves them to output first
            while (!opStack.empty() && isOperator(opStack.top()) && precedence(opStack.top()) >= precedence(t.value)) {
                output.push_back({opStack.top()});
                opStack.pop();
            }
            opStack.push(t.value);                    //pushes the current operator with less precedence
        }
        else if (t.value == "(") {                    //if there's a ( push
            opStack.push(t.value);
        }
        else if (t.value == ")") {                   //if there is a ) check if the stack is not empty and that the top isn't ( then pop  until the top is (
            while (!opStack.empty() && opStack.top() != "(") {
                output.push_back({opStack.top()});
                opStack.pop();
            }
            if (!opStack.empty()) {
                opStack.pop();                      //remove the ( because it is only needed for grouping
            }
        }
    }

    while (!opStack.empty()) {                     //removes remaining operators from the stack to output
        output.push_back({opStack.top()});
        opStack.pop();
    }

    return output;
}


// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;
    // TODO
    return 0.0;
}

// Main

int main() {
    string line;
    getline(cin, line);

    vector<Token> tokens = tokenize(line);

    if (isValidPostfix(tokens)) {
        cout << "FORMAT: POSTFIX\n";
        cout << "RESULT: " << evalPostfix(tokens) << "\n";
    }
    else if (isValidInfix(tokens)) {
        vector<Token> postfix = infixToPostfix(tokens);
        cout << "FORMAT: INFIX\n";
        cout << "POSTFIX: ";
        for (const auto& t : postfix) {
            cout << t.value << " ";
        }
        cout << "\n";
        cout << "RESULT: " << evalPostfix(postfix) << "\n";
    }
    else {
        cout << "FORMAT: NEITHER\n";
        cout << "ERROR: invalid expression\n";
    }

    return 0;
}
