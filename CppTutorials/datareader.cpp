/*************************************************************************************
 Copyright (C) 2021 Over-Infinity.
 Everyone is permitted to copy and distribute verbatim copies of this license document
 This Sampel shows how to use callback function in c++11 and later version
**************************************************************************************/
#include <iostream>
#include <functional>

/* InputStream: this class is responsible of getting input stream from source 
 * and after recive it callback a function of caller to inform  it about done job*/
class InputStream{
 
public:
    InputStream(){}
    /* read stream from source asyn and then call callback function.*/
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

class DataReader{  
 
public:
   DataReader(){}   
   void read_stream(){ 
     stream.read_async(content,
                        std::bind(&DataReader::read_done, this));
   }

   void read_done() {
    for (char n : content) {
        std::cout << n;
    }
   }
   InputStream stream;
   std::vector<char> content;
};

int main(){
 
    DataReader reader;
    reader.read_stream();    
    return 0;
}
