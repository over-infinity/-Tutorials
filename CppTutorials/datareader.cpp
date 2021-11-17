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
    void read_async(std::size_t count, std::vector<char>& out, 
                  std::function<void(std::error_code)> callback){
                      
                  }
};

class DataReader
{
   /* rest of interface */
public:
  // DataReader(){}
   void read_remaining()
   { 
      stream.read_async(expected - content.size(), content,
                        std::bind(&DataReader::part_done, this));
   }

   void part_done() 
   {
     if (content.size() < expected)
       read_remaining();
   }

   InputStream stream;
   std::size_t const expected;          
   std::vector<char> content;
};

int main()
{
    std::cout<<"Hello World";

    return 0;
}
