#include <iostream>
#include <string>

std::string stringToBrainfuck(const std::string str){
    unsigned char data = 0;
    std::string result;
    
    for (unsigned char c: str){
        while (data < c){
            result.push_back('+');
            ++data;
        }
        
        while (data > c){
            result.push_back('-');
            --data;
        }
        
        result.push_back('.');
    }
    
    return result;
}

int main()
{   
    return 0;
}
