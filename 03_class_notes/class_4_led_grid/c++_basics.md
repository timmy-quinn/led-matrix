# Programming LED Matrix

## Basic C++
### Basic data types
**integers:**
```c++
int myInt = 16;
```
Integers store whole numbers between -2,147,483,648 to 2,147,483,647

**floating-point numbers:**
```c++
float myFloat = 10.11;
float myFloat = 10.0;
```
Floating-point numbers store decimal values  1.17549435×10^−38 to 3.4028235×10^38

**boolean:**
```c++ 
bool myBool = true;
bool myOtherBool = false;
```
Booleans store either true or false. 

**arrays:**
```c++
bool boolArray[10];
int intArray[3];
float floatArray[4] = {1, 2, 3, 4};
```
Arrays are data structures which store a fixed-size collection of elements of
the same data type. You can access elements of the same data type as shown below.
```c++
// intArray = {0, 0, 0};
intArray[0] = 1;
intArray[1] = 10,000;
intArray[2] = 12;
// now intArray = {1, 10,000, 12};
```
Note, arrays are zero-indexed.

### Basic operators
```c++
int a;
a = 10 + 1;
a = 10 - 1;
a = 10 * 1;
a = 21 / 5; // Since a is an int, remainder is ignored, so a = 4 
```
**modulus operator:**
When dividing integers, the remainder is ignored. Modulus operator is used to
return remainder.
```c++
int a;
a = 21 % 2; // remainder is 1
a = 20 % 2; // remainder is 0
```
This will be useful for our project.


### Control flow
**if:**
```c++
int x = 10;
if(x == 10) {
    Serial.println("Equal");
}
```

**else if, else**: 
We can add on to if statements with else if and else statements.
```c++
int x = 10;
if (x > 10) {
    Serial.println("Greater");
}
else if (x == 10) {
    Serial.println("Equal");
}
else {
    Serial.println("Less");
}
```


