#include <LiquidCrystal.h>
#include <Servo.h>

// initialize the functon to move the 
// sensor up and down
void UpDown();

// initialize the functon to move the 
// sensor up and down
void LeftRight();

Servo servo1;
Servo servo2;

// Initialize the library with the numbers 
// of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// set up loop
void setup() {
  
  // Initialize the LCD with 16 characters
  // long on each line and 2 lines.
  lcd.begin(16, 2); 
 
  // conect servo 1 to interface pin 9
  servo1.attach(9);
  // conect servo 2 to interface pin 10
  servo2.attach(10); 

  // sets the angle of servo 1 to 90 degrees
  servo1.write(90); 
  // sets the angle of servo 2 to 90 degrees
  servo2.write(90); 
}


void loop() {

  int Tolerence = 0;// set tolerence to 0

  // set the top LDR input to analog pin 0
  int sensorTop = analogRead(A0);
  // set the bottom LDR input to analog pin 1
  int sensorBottom = analogRead(A1);
  // set the left LDR input to analog pin 3
  int sensorLeft = analogRead(A3);
  // set the right LDR input to analog pin 4
  int sensorRight = analogRead(A4);

  // Compares the difference in top and bottom
  int sensorTest1 = sensorTop - sensorBottom;
  // Compares the difference in top and bottom
  int sensorTest2 = sensorBottom - sensorTop;
  // Compares the difference in left and right
  int sensorTest3 = sensorLeft - sensorRight;
  // Compares the difference in left and right
  int sensorTest4 = sensorRight - sensorLeft;

  // Reads the variable resistor value to get tolerence
  int TolerenceValue = analogRead(A2);
  // sets tolerence value and changes value between 1 and 10
  Tolerence = (TolerenceValue * (5.0 / 1023.0)) * 2; 

  int avgIntensity = (sensorTop + sensorBottom + sensorLeft + sensorRight) / 4 - 54;
  lcd.clear();

  // checks to see if sensor test 1 is greater then or equal to the
  // tolerance and that sensor test 1 is a positive number
  if ((sensorTest1 >= 0) && (sensorTest1 >= Tolerence)) {
    // calls function to move the solar panel up or down towards the sun. 
    // Also pass the values of top and bottom sensors
    UpDown(sensorTop, sensorBottom);
  }

  // checks to see if sensor test 2 is greater then or equal to the 
  // tolerance and that sensor test 2 is a positive number
  if ((sensorTest2 >= 0) && (sensorTest2 >= Tolerence)) {
    // calls function to move the solar panel up or down towards the sun. 
    // Also pass the values of top and bottom sensors
    UpDown(sensorTop, sensorBottom);
  }

  // checks to see if sensor test 3 is greater then or equal to the 
  // tolerance and that sensor test 3 is a positive number
  if ((sensorTest3 >= 0) && (sensorTest3 >= Tolerence)) {
    // calls function to move the solar panel left or right towards the sun. 
    //Also pass the values of left and right sensors
    LeftRight(sensorLeft, sensorRight);
  }

  // checks to see if sensor test 4 is greater then or equal to the 
  // tolerance and that sensor test 4 is a positive number
  if ((sensorTest4 >= 0) && (sensorTest4 >= Tolerence)) {
    // calls function to move the solar panel Left or right towards the sun. 
    // Also pass the values of left and right sensors
    LeftRight(sensorLeft, sensorRight);
  }

  int pos1 = servo1.read();
  int pos2 = servo2.read();
  lcd.setCursor(0, 0);
  lcd.print("V: ");
  lcd.print(pos1);

  lcd.setCursor(7, 0);
  lcd.print("H: ");
  lcd.print(pos2);

  lcd.setCursor(0, 1);
  lcd.print("I: ");
  lcd.print(avgIntensity);

  delay(100); 
}

// function to check what direction to move up or down and turn towards the sun.
// Also take the value of top and bottom from the main loop and return nothing.
void UpDown(int sensorTop, int sensorBottom) {

  // reads the current angle of servo 1
  int pos1 = servo1.read(); 

  // checks to see if the bottom sensor is grater than the top tehn enter the loop.
  if (sensorTop < sensorBottom) {
    pos1 = --pos1; // change the angle by -1
  }
  // if the bottom is not greater than the top then enter this loop
  else{
    pos1 = ++pos1;// change the angle by +1
  }
  
  servo1.write(pos1); // write the new angle to servo 1
}

// function to check what direction to move left or right and turn towards the sun.
// Also take the value of left and right from the main loop and return nothing.
void LeftRight(int sensorLeft, int sensorRight) {

  int pos2 = servo2.read(); // reads the current angle of servo 1

  // checks to see if the left sensor is grater than the right tehn enter the loop.
  if (sensorLeft < sensorRight) {
    pos2 = --pos2;// change the angle by -1
  }
  // if the left is not greater than the right then enter this loop
  else{
    pos2 = pos2 + 1;// change the angle by +1
  }
  servo2.write(pos2); // write the new angle to servo 1
}
