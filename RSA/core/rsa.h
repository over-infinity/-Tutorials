/*
 * this file is a part of RSA implimentation project, https://github.com/over-infinity/-Tutorials/RSA
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2021, Over-Infinity
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* rsa.h */

#ifndef _RSA_H
#define _RSA_H

////////////////////  Includes ///////////////////
#include <inttypes.h>                           //                       
//////////////////////////////////////////////////

#define STATIC static  

class RSA{
   
/* Public class methods  */     
public:  
   
   RSA();   
   ~RSA();

 /* Private attributes  */
 private:   
   uint32_t n; /* n is known as the modulus. */ 
   uint32_t e; /* e is known as the public exponent or encryption exponent or just the exponent. */
   uint32_t d; /* d is known as the secret exponent or decryption exponent. */
   uint32_t p;
   uint32_t q;
   uint32_t phi; 
   
 /* Private class methods  */   
private:
  void Init();
  STATIC uint32_t Gcd1(uint32_t num1, uint32_t num2);
  STATIC uint32_t Gcd2(uint32_t num1, uint32_t num2);
  STATIC bool IsPrime(uint32_t value);   
  STATIC uint32_t GenRandPrime(uint32_t maxvalue);
  
  
};


#endif  // _RSA_H
