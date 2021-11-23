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
    
    https://www.cs.utexas.edu/~mitra/honors/soln.html
************************************************************************************/
