/*
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to this part of the project by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc program (described in the spec) to check the legality of
     your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the spec and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *
 *      YOU WILL RECEIVE NO CREDIT IF YOUR CODE DOES NOT PASS THIS CHECK.
 *
 *   2. Use the btest checker to verify that your solutions produce the
 *      correct answers.
 */

#endif

/*
 * isZero - returns 1 if x == 0, and 0 otherwise
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
    return !x; //if x is 0 return 1, else return 0
}

/*
 * bitNor - ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
    return (~x) & (~y); //takes the inverse of x and y and compares them too each other with and
}

/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
int distinctNegation(int x) {
    x = x ^ (~x + 1); //x gets inverted, find two's complement of x, XOR the entire thing
    return !!x; //turns x into a bool value, returns 1 if x is non Zero, 0 otherwise
}

/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int dividePower2(int x, int n) {
    int sign = (x >> 31) & 1; //Get the sign of x (0-positive, 1-Negative)
    int bias = (sign << n) + (~sign + 1); //Caluculates the bias for rounding

    return (x + bias) >> n; // return Divide x by 2^n and round
}

/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    int shift = n << 3; //Calculates how many bits to shift
    int mask = 0xFF; //Creates a with all bits set to 1
    //Shifts x to the right by n bytes and masks to return the desired byte
    return (x >> shift) & mask; 
}

/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int isPositive(int x) {
    //first check if sign is set, double negate x so it acts as a 'boolean' x becomes 1 if non-zero, and 0 if zero
    int result = (!(x >> 31)) & !!x;
    return result; //return 1 if positive, 0 otherwise
}

/*
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
    unsigned signMask = 0x80000000; //Mask to extract the sign bit
    unsigned NaNMask = 0x7F800000; //Mask for exponenet bits
    unsigned fracMask = 0x007FFFFF; //Mask for fraction bits

    if((uf & NaNMask) == NaNMask && (uf & fracMask)){
        //It's a NaN
        return uf;
    }
    else{
        //Flip sign bit to negate value
        return (uf ^ signMask);
    }
}

/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int signX = (x >> 31) & 1; //Gets sign bit of x (0-Positive, 1-Negative)
    int signY = (y >> 31) & 1; //Gets sign bit of y (0-positive, 1-Negatvie)

    //checks if x and y are the same, checks if x -y is negative, combine the conditions
    int result = (!(signY^signX)) & (((x+~y) >> 31) & 1);
    
    //if y is negative and x is postive or zero, return 1, else return 0
    return result|((!signY)& signX);
}

/*
 * bitMask - Generate a mask consisting of all 1's between
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
    int ones = ~0x00; //ones is an int with all bits set to one
    int x = ones << lowbit; //creates a mask of 1s at and left of lowbit
    int y = (ones  << highbit) << 1; //creates a mask of 1s at and left of highbit
    return (x & ~y); //this returns a bit number with all ones except inbetween lowbit and highbit
}

/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
    int sum = x + y; //get sum of x and y

    //checks for overflow by looking at bit 31 of x and y compared to sum. (1, no overflow: 0, overflow)
    int result = !(((sum ^ x) & (sum ^ y)) >> 31);

    return result;
}

/*
 * floatScale64 - Return bit-level equivalent of expression 64*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 35
 *   Rating: 4
 */
unsigned floatScale64(unsigned uf) {
    unsigned signMask = 0x80000000; //Mask to extract the sign bit
    unsigned NaNMask = 0x7F800000; //Mask for exponenet bits
    unsigned fracMask = 0x007FFFFF; //Mask for fraction bits
    unsigned sign = uf & signMask; //get sign using signMask
    unsigned exp = uf & NaNMask; //get exponent using NaNMask
    unsigned frac = uf & fracMask; //get fraction using fracMask

    if((uf & NaNMask) == NaNMask && (uf & fracMask)){
        //checks if uf is NaN
        return uf;
    }

    exp = exp + (64 << 23); //multiply exponent by 64

    //check for overflow, return +inf if it does
    if(exp >= NaNMask){
        return NaNMask | sign;
    }

    return sign | exp | frac; //otherwise return result
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    unsigned result;

    //check for overflow
    if(x > 127){
        //x too large, return +INF
        result = 0xFF << 23;
        return result;
    }
    //denormalized
    if(x <= -126 && x >= -149){
        //set result to a denormalized number
        result = 1 << (23 - ((-x) - 126));
        return result;
    }
    //normalized
    if(x >= -126 && x <= 127){
        //set result to a normalized number
        result = (x + 127)<<23;
        return result;
    }
    //x is too small to be represented
    if(x < -149){
        return 0;
    }
    
    return 0;
}
