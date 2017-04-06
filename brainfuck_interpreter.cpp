#include <iostream>
#include <string>
#include <vector>
#include <stack>

constexpr int MAX_INSTRUCTIONS = 100'000'000;
constexpr int MAX_MEMORY_CELLS = 100'000;

void error(const std::string& message){
    std::cerr << "error: " << message << std::endl;
    exit(1);
}

std::string interpretCode(const std::string& commands){
    std::vector<unsigned char> data(std::min(32, MAX_MEMORY_CELLS), 0);
    std::vector<unsigned char>::iterator dataPtr = data.begin();

    std::string::const_iterator instructionPtr = commands.begin();
    std::stack<std::string::const_iterator, std::vector<std::string::const_iterator>> instructionsStack;

    std::string result;
    int nr_iterations = 0;
    
    while (instructionPtr != commands.end()){
        if (++nr_iterations > MAX_INSTRUCTIONS)
            error("Too many instructions");
            
        switch(*instructionPtr){
            case '<':
                if (dataPtr != data.begin())
                    dataPtr--;
                break;
            case '>':
                if (++dataPtr == data.end()){
                    if (data.size() < MAX_MEMORY_CELLS)
                        data.emplace_back(0);
                    dataPtr = data.end() - 1;
                }
                break;
            case '+':
                ++(*dataPtr);
                break;
            case '-':
                --(*dataPtr);
                break;
            case '.':
                result.push_back(*dataPtr);
                break;
            case '[':
                instructionsStack.push(instructionPtr);
                
                if (*dataPtr == 0){
                    auto startInstructionPtr = instructionPtr;
                    
                    while (++startInstructionPtr != commands.end()){
                        if (++nr_iterations > MAX_INSTRUCTIONS)
                            error("Too many instructions");
                            
                        if (*instructionPtr == '[')
                            instructionsStack.push(instructionPtr);
                        else if (*instructionPtr == ']'){
                            if (instructionsStack.empty())
                                error("Found a ']' that did not have a matching '['");
                            
                            auto tempInstructionPtr = instructionsStack.top();
                            instructionsStack.pop();
                            
                            if (startInstructionPtr == tempInstructionPtr)
                                break;
                        }
                    }
                }
                
                break;
            case ']':
                if (instructionsStack.empty())
                    error("Found a ']' that did not have a matching '['");
                    
                if (*dataPtr != 0)
                    instructionPtr = instructionsStack.top();
                else
                    instructionsStack.pop();
                    
                break;
            default:
                error("Invalid command");
                break;
        }
        
        if (instructionPtr == commands.end())
            error("Invalid program");
            
        instructionPtr++;
    }
    
    if (!instructionsStack.empty())
        error("Found a '[' that did not have a matching ']'!");
    
    return result;
}

int main()
{   
    return 0;
}