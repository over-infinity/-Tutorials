/*************************************************************************************
 Copyright (C) 2021 Over-Infinity.
 Everyone is permitted to copy and distribute verbatim copies of this license document
 This Sampel shows how to use callback function in c++11 and later version
**************************************************************************************/

#include <iostream>
#include<functional>

class BarClass;
typedef std::function<void()> CallBack_arg0_t;
typedef std::function<void(int)> CallBack_arg1_t;

class FooClass{
  public:
    FooClass(CallBack_arg0_t _fun0, CallBack_arg1_t _fun1){
      
      callback_0 =_fun0;
      callback_1 = _fun1;
      num = 100;
      
    }
    void Foo_do_Somthing(){
        /* User Code Here  */
        callback_0();
        callback_1(num);
    }
    
  private: 
    CallBack_arg0_t callback_0;
    CallBack_arg1_t callback_1;
    int num;
};

class BarClass{
    public:
        BarClass(){
            foo=new FooClass(std::bind(&BarClass::Bar_callback_0,this), std::bind(&BarClass::Bar_callback_1,this,std::placeholders::_1));
        }
        void Bar_doSomthing(){
            foo->Foo_do_Somthing();
        }
protected:        
    void Bar_callback_0(){
        std::cout << "this is a callback method with zero arg \n";
    } 
    
    void Bar_callback_1(int num){
        
        std::cout << "this is a callback method with one arg : " << num << "\n";
    }  
    private:
        FooClass *foo;
    
};


int main()
{
    std::cout<<"CallBack Sample\n";
    BarClass bar;
    bar.Bar_doSomthing();
    return 0;
}
