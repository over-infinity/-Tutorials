/*************************************************************************************
 Copyright (C) 2021 Over-Infinity.
 Everyone is permitted to copy and distribute verbatim copies of this license document
 This Sampel shows how to use callback function in c++11 and later version
**************************************************************************************/
#include <iostream>
#include <functional>
class InputStream
{
public:
    InputStream(){}
    void read_async(std::vector<char>& out,std::function<void()> callback){
        out.push_back('O');
        out.push_back('v');
        out.push_back('e');
        out.push_back('r');
        out.push_back('-');
        out.push_back('I');
        out.push_back('n');
        out.push_back('f');
        out.push_back('i');
        out.push_back('n');
        out.push_back('i');
        out.push_back('t');
        out.push_back('y');
        
        callback();
                      
        }
};

class DataReader
{
   /* rest of interface */
public:
   DataReader(){}
   
   void read_stream()
   { 
     /* Here insted of passing function member to stream.read_async we pass lambda function to it.
      * Remind notition: 
      * -> Lambda Syntax : [ captures ] ( params ) lambda-specifiers requires(optional) { body } 	
      *       & (implicitly capture the used automatic variables by reference) and
      *       = (implicitly capture the used automatic variables by copy). 
      *  for more information refer to https://en.cppreference.com/w/cpp/language/lambda   */
     
      stream.read_async(content,
                        std::bind([=](){for (char n : content) std::cout << n;}));
   }

   InputStream stream;
   std::vector<char> content;
};

int main()
{
    DataReader reader;
    reader.read_stream();
    
    return 0;
}
