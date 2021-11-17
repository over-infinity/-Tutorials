/*************************************************************************************
 Copyright (C) 2021 Over-Infinity.
 Everyone is permitted to copy and distribute verbatim copies of this license document
 This Sampel shows how to use callback function in c++11 and later version
**************************************************************************************/

#include <iostream>
#include<functional>

class BarClass;
/*First of all we define callback type here we have two callback
 * one without input argument and the other with one int argument */
typedef std::function<void()> CallBack_arg0_t;
typedef std::function<void(int)> CallBack_arg1_t;

/* FooClass is a class that get two callback method in its constructor and later
 * can call them here we call them in Foo_do_Somthing member function */
class FooClass{
  public:
    FooClass(CallBack_arg0_t _fun0, CallBack_arg1_t _fun1):callback_0(_fun0),
    callback_1(_fun1),num(100){
        // class constructor 
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
/* BarClass this class is main class and creat an object class from FooClass then pass tow of its
 * member functions to FooClass as a callback functions. for this purpose we use std::bind(...) to 
 * bind BarClass's memberfunctions as a callback functions. 
 * Note:: When std::placeholders::_1 used as an argument in a std::bind expression, the placeholder
 * objects are stored in the generated function object, and when that function object is invoked 
 * with unbound arguments, each placeholder _N is replaced by the corresponding Nth unbound argument.
 * cppreference: https://en.cppreference.com/w/cpp/utility/functional/placeholders */
class BarClass{
    public:
        BarClass(){
             // class constructor 
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
