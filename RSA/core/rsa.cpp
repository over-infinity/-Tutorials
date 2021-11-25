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

/* rsa.cpp */
/***********************************************************************************
Key Generation Algorithm:
This is the original algorithm.
1- Generate two large random primes, p and q, of approximately equal size such that
   their product n=pq is of the required bit length, e.g. 1024 bits.
2- Compute n=pq and ϕ=(p−1)(q−1).
3- Choose an integer e, 1<e<ϕ, such that gcd(e,ϕ)=1.
4- Compute the secret exponent d, 1<d<ϕ, such that ed≡1 mod ϕ.
5- The public key is (n,e)and the private key (d,p,q). Keep all the values d, p, q and ϕ secret. 
   [Sometimes the private key is written as (n,d) because you need the value of n when using d. 
    Other times we might write the key pair as ((N,e),d)].
    
* n is known as the modulus.
* e is known as the public exponent or encryption exponent or just the exponent.
* d is known as the secret exponent or decryption exponent.

RSA Algorithm Example:

    Choose p = 3 and q = 11
    Compute n = p * q = 3 * 11 = 33
    Compute φ(n) = (p - 1) * (q - 1) = 2 * 10 = 20
    Choose e such that 1 < e < φ(n) and e and φ (n) are coprime. Let e = 7
    Compute a value for d such that (d * e) % φ(n) = 1. One solution is d = 3 [(3 * 7) % 20 = 1]
    Public key is (e, n) => (7, 33)
    Private key is (d, n) => (3, 33)
    The encryption of m = 2 is c = 27 % 33 = 29
    The decryption of c = 29 is m = 293 % 33 = 2
    
    refrences 
    - https://www.di-mgt.com.au/rsa_alg.html
    - https://www.cs.utexas.edu/~mitra/honors/soln.html
************************************************************************************/
#include "rsa.h"
#include <stdint>
#include <cstdlib> 
#include <time.h>

#define SWAP(type, value1, value2) {type temp=value2; value2=value1; value1=temp;}

#ifndef UINT32_MAX
  #define UINT32_MAX 0xFFFFFFFF
#endif

/*  RSA Constructor   */
   RSA::RSA() {
	
	   Init();
	   
	} 

   /*  RSA destructor   */
   RSA::~RSA(){}

   
/*  
 * @name GCD1
 * @brief GCD (Greatest Common Divisor) or HCF (Highest Common Factor) of 
 *         two numbers is the largest number that divides both of them. 
 * @param num1, first number.
 * @param num2, second number.
 * @return gcd(num1,num2).
 */
 STATIC uint32_t RSA::GCD1(uint32_t num1, uint32_t num2)
{
   /* we suppose num1 is greater or equal to num2 if not so swap them */	 
   if(num1 > num2)
     SWAP(uint32_t,num1,num2);
	 
    do{
	/* everything divides 0 */
	if(num1 == 0)
	   return num2;
	 if(num2 == 0)
            return num1;
	/*  equal values example : gcd(5,5) = 5 */
	if(num1 == num2)
          return num1;
		
	num1=num1-num2;
	    
	/* be sure that num1 is greator that num2  */	 
	if(num2 > num1)
	   SWAP(uint32_t,num2,num1); 
		 
	 }while(num1 >= num2);
}   
	
 /* 
  * @name GCD2 
  * @brief  Another more efficient solution for getting GCD is to use modulo operator base on Euclidean algorithm.
  *           GCD2 is a recursive algorithm.
  * @param  num1, first number.
  * @param  num2, second number.
  * @return gcd(num1,num2).
  */
STATIC uint32_t RSA::GCD2(uint32_t num1, uint32_t num2)
{
    if (num2 == 0)
        return num1;
	
    return GCD2(num2, num1 % num2);     
}
	
 /* 
  * @name IsPrime 
  * @brief  Any whole number which is greater than 1 and has only two factors that is 1 and the number itself, is 
  *          called a prime number.        
  * @param  num1, number to check if is prime or not
  * @return true/false
  */	
STATIC bool RSA::IsPrime(uint32_t value)
{
	/* simply we only need to cheak half of the number to realize that it is prime or not. */
	for (int i = 2; i <= (value / 2); i++)
	{
		if (value % i == 0)
			return false;
	}
	return true;
}

 /* 
  * @name GenRandPrime 
  * @brief  srand() is used to initialise random number generators. This function gives a starting point  
  *           for producing the pseudo-random integer series. The argument is passed as a seed for generating
  *           a pseudo-random number. prototype : int srand(unsigned int seed);
  * @param  none
  * @return random prime number between 0 < rp < UINT32_MAX
  */

uint32_t RSA::GenRandPrime(uint32_t maxvalue)
{	
	#define MinRatio 5000
	
	uint32_t rp; // random prime number
	uint32_t minvalue = (maxvalue / MinRatio ) + 1;
	do
	{
		srand(time(NULL));
		rp = (rand() % maxvalue) ;
		
	}while (!RSA::IsPrime(rp) || rp  < minvalue);
	
	return rp;
}

void RSA::Init(){	
	
	 p = RSA::GenRandPrime(UINT32_MAX); // 1 < p < UINT32_MAX
	 do{	     
	      q = RSA::GenRandPrime(UINT32_MAX); // 1 < q < UINT32_MAX					
	  } while(p==q)// generate prime numbers p and q.		
		
	phi = n - p - q + 1;  // phi = (p-1)(q-1) = pq-p-q+1 = n-p-q+1  
	
	do{
	    e = RSA::GenRandPrime(phi);  // 1 < e < phi
		
	}while (RSA::GCD2(e,phi) != 1); // e and phi sould be prime to each other(gcd(e,phi)==1)
	
}

