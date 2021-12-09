#include <Wire.h>             //This library allows to communicate with I2C inter-integrated circuit
#include <Adafruit_GFX.h>     //it add graphics functions like lines, circles and text.
#include <Adafruit_SSD1306.h> //which handles the low-level communication with the hardware
#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels
                              
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);   // Declaration for an SSD1306 display connected to this pins (SDA, SCL pins) i.e a4 and a5


int sensorPin = A0; //this is the analog input pin which gets the moist level from the sensor
int sensorValue;  
int limit = 400; //here we are specifying a value to differentiate the moist level 
int in1 = 7;    //at this pin number the relay signal is connected

void setup() {
 
  pinMode(in1, OUTPUT);
  digitalWrite(in1, HIGH);
  
}

void disp(int sensorValue)    //its the function to display the status in oled and takes sensorValue as parameter
{
  Serial.begin(115200);  
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
      // Address 0x3D for 128x64    
      Serial.println(F("SSD1306 allocation failed"));    
      for(;;); 
   }
  display.clearDisplay();   
   display.setTextSize(1);  //here we r setting the size color and
   display.setTextColor(WHITE);  
   display.setCursor(0, 10);  // setting the cursor of oled to the beginning
   
  if (sensorValue<limit) //if the value is less than the limit then the blow func will print Moisture found Motor off in the display
  {
       display.println("Moisture found\nMotor off"); 
       display.display(); 
  }
  else        //if the value is greater than the limit then the below func will print Moisture not found Motor on in the display
  {
       display.println("Moisture not found\nMotor on"); 
       display.display(); 
  }
}
void loop() {     //the void loop
 sensorValue = analogRead(sensorPin);   //reading the analog pin A0 and assigning the value to sensorvalue
 if (sensorValue<limit)     
 {
 disp(sensorValue);       //it a function call which calls the above disp function sending the sensorValue
 digitalWrite(in1, HIGH);   //this will not give any signal to relay and here High means it will off the pump beecause the pump is connected to NO and Common terminal of the relay
 }
 else 
 {
 disp(sensorValue);       //it calls the above disp function
 digitalWrite(in1, LOW);    //this will give some signal to relay and here Low means it will on the pump beecause the pump is connected to NO and Common
 }
 delay(100); 
}
