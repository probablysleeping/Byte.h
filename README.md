# Byte.h
### Overview

This is a single header Byte-Manipulation library. Useful for compact bool storage or information packing. Each "bit" can be accessed and used as a bool.

Byte's main storage variable is a uint8_t, and the Byte class remains no bigger than 1 byte.

Only uses the standard c++ library. Single header include.

### Usage

Due to template restraints, the bit access variable must be known at compile-time, so you need to use the supplied *std::integrial_constant template auto* **'bit'**
These bit variables are what are used to access a given Bit.

#### Bit Access Examples
```
Byte newByte{ 0 };              //Create a new Byte object.
newByte = (uint8_t)64; 

bit<0>                          //Bit access variable, only usable in Byte operator[], 0 is minimum.
bit<7>                          //7 is maximum.

newByte[bit<1>] = true;         //Set a specific bit within the byte.

bool value = newByte[bit<1>];   //Use it as a bool.
if (newByte[bit<2>])            //etc.
```
#### Byte Functionality
```
if (newByte += 64);             //Addition should be used via += to avoid overflow, operator+= returns true if the sum overflows.
   //do something

newByte == otherByte            //Comparator ==

newByte.Print();                //Prints the Byte in '00000000' format
newByte.to_string()             //Returns the Byte as a '0d00000000' string for other use.

```

