# Microcontroller Basics

## ESP32 
### Overview  

The ESP32 is a **microcontroller**. A microcontroller a small programmable 
computer chip which interacts with the outside world through a set of input 
and output pins. All a microcontroller does is take some inputs, performs 
some processing, and controls some outputs.  

The seemingly simple capabilities of a microcontroller in fact enable it to 
perform a wide range of functions. You can find microcontrollers in 
everything around you, from headphones, to satellites, to cars to 
3d-printers. The very same ESP32 chip we're going to be using is very popular 
in smart devices, so if you have wifi-controlled lights, or a thermostat 
you can adjust from your phone, you may already have an ESP32 in your home. 

![](Photos/esp32_devkit_v1_pinout.png)

In all of these devices, the fundamental working principle is the same. 
Get data from input pins. Perform some processing. Control the output pins. 

For our project, the input is going to be a microphone, and the output is 
going to be an RGB LED grid. But there are many other options to choose 
from.   
  
#### Inputs and outputs
![Inputs and outputs](Photos/inputs_and_outputs.jpg)

  
## Setup

1. Download the Arduino IDE [here](https://www.arduino.cc/en/software/)
2. Follow these [instructions](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) 
to set up your ESP32 board. 
  
## Programming your microcontroller 
### Blinky 
When getting started with a new devboard, microcontroller, or project, you're 
almost always going to want to write a blinky program. This is a simple way 
to make sure that your board works, that you know how to upload code to your
board, and that you can use its basic features. 

For us, this will also be a great opportunity to learn about some fundamental 
programming concepts.  

```
// Blinky example 

int LED = 2; 

// Runs once when ESP32 is powered on 
void setup() {
  // Set pin mode
  pinMode(LED,OUTPUT);
}

// Runs in a continuous loop after setup()
void loop() {
  delay(500); // Delays for 500 milliseconds (1/2 second)
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
}

```
### Hello world  
Another common test program is the hello world. In fact, when learning a 
new programming language, you're going to write a hello world program
before anything else. 

```
void setup() {
  // Create a serial connection
  // This will enable us to send data 
  // From our microcontroller to our 
  // computer one bit at a time. 
  // 115200 is the speed at which we can
  // send data. This is called the baud 
  // rate and it is measured in bits per
  // second. 
  Serial.begin(115200); 
}

void loop() {
  // Send a string of characters to 
  // our computer. 
  Serial.println("Hello World"); 
  delay(3000); 
}

```
After you upload your code to your microcontroller, click the Serial Monitor 
button in the upper right corner of the Arduino IDE. Make sure the port matches
the port your ESP32 is connected to. Make sure the baud rate matches the rate the ESP32 is set to. You should see the words *Hello World* being printed out 
repeatedly.  

> :memo: **Challenge**  
> Modify the above code to send a message of your choice!    

### Programing basics: What is code?  
  
The snippet shown above is an example of C++ code. But what you see above 
is not actually what is uploaded to our ESP32. 

### Building blocks of a program
 
#### Building Block: Variables
Variables are the way we store information in a program. There are few 
different variable types in C++, which are defined by specific keywords.  

Here are some of the more common types we will encounter in this class. 
  
- <span style="color:teal">int</span>: 
stores whole numbers, typically between -2,147,483,648 to 2,147,483,647
- <span style="color:teal">float</span>: 
stores decimal values, between -3.4^38 to -3.4^38. 
- <span style="color:teal">bool</span>: 
represents either true or false, (1 or 0). bool stands for boolean
  
Now, here we can get to the fun part and can play around with our newfound 
understanding of variables. 

*Example*  

We can perform basic mathematic operations on our variables as well. 
```
void loop() {
  int a = 100; 
  Serial.print("Original: "); 
  Serial.println(a); 

  a = a + 2; 
  Serial.print("Plus 2: "); 
  Serial.println(a); 

  a = a - 1; 
  Serial.print("Minus 1: "); 
  Serial.println(a); 

  a = a * 4; 
  Serial.print("Times 4: "); 
  Serial.println(a); 

  a = a / 2; 
  Serial.print("Divide 2: "); 
  Serial.println(a); 

  Serial.println(); 
  
  delay(5000);
}
```

#### Building Block: Functions 

So it turns out that we've already used functions. ````setup()````, 
````loop()````, ````Serial.println()```` and ````Serial.print()```` are all 
functions. 
  
What is a function, and why do we use it? A function is a reusable block of code 
which performs a specific task. This is super useful in programming. Oftentimes
we want to perform the same task in many different contexts. We can write 
functions which take certain inputs, and then perform some operations on those 
inputs to get a result. 

*Example*
```
int add(int a, int b) {
  return a + b; 
}

void loop() {
  int sum = add(a, b); 
  Serial.print("Function result:");
  Serial.println(sum); 
  delay(10000); 
}
```
> :memo: **Challenge**  
> Write a function that takes an integer as an argument and returns the square of 
> that integer.   
> **Bonus**  
> In the function, print the result in this format: ```` var squared equals result````  

Something else to note about a function is that variables declared within a 
function cannot be accessed outside of that function. 

#### Building Blocks: if else  
We don't always want out program to do the same thing every time. We want our 
little computer to be able to make some decisions. We want to be able to turn 
on a light if a button is pressed. We want to be able to stop a motor if a 
robotic arm has reached the correct position. 
  
How are we going to do this? This is where if else statements come in. These 
simple statements when coupled with other code can enable some very complex, 
intelligent behavior.  
```
void print_greater_than_equal(int test, int threshold) {
  if(test >= threshold) {
    print("Success!!!"); 
  }
  else {
    print("Failure ");
  }
}

void print_comparison(int a, int b) {
  if(a > b) {
    Serial.println("Greater than"); 
  }
  else if(a < b) {
    Serial.println("Less than"); 
  }
  else {
    Serial.println("Equal"); 
  }
}

void loop() {
  int threshold = 10; 

  print_comparison(1, threshold); 
  print_comparison(12, threshold); 
  print_comparison(threshold, threshold); 
  print_comparison(threshold - 1, threshold); 

  Serial.println();
  Serial.println("Greater than equal function"); 
  print_greater_than_equal(threshold, threshold);  
  print_greater_than_equal(threshold - 1, threshold); 

}
```

