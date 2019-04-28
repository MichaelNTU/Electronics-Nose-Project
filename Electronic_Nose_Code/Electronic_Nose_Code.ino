// include the library code:
#include <LiquidCrystal.h>
#include <SPI.h> 
#include <Wire.h> 

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
int Analog_MQ2_Sensor = A0;
int Analog_MQ135_Sensor = A1;
int LPG = 13; // this defined and declare the pin 
int Propane = 10;
int Hydrogen = 9;
int Alcohol = 8;
int CO2 = 7;
int Ammonia = 6;
float m_LPG =-0.476; //Slope, this is used to calculate sensitivity of gas resistance
float b_LPG =3.083;//Y-Intercept
float m_Propane = -0.461; //Slope
float b_Propane = 2.69;//Y-Intercept
float m_Hydrogen = -0.465; //Slope
float b_Hydrogen = 3.251;//Y-Intercept
float m_Alcohol = -0.245; //Slope
float b_Alcohol = 0.771;//Y-Intercept
float m_CO2 = -0.380; //Slope
float b_CO2 = 1.752;//Y-Intercept
float m_Ammonia = -0.418; //Slope
float b_Ammonia = 2.021;//Y-Intercept
float R0_MQ135 = 13.465;
float R0_MQ2 = 6.865;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(LPG, OUTPUT); // this either turn on or off the led 
  pinMode(Propane, OUTPUT);
  pinMode(Hydrogen, OUTPUT);
  pinMode(Alcohol,OUTPUT);
  pinMode(CO2,OUTPUT);
  pinMode(Ammonia,OUTPUT);
  pinMode(Analog_MQ2_Sensor, INPUT);// this get input from the sensor 
  pinMode(Analog_MQ135_Sensor, INPUT); // this get input from the sensor
  digitalWrite(LPG,LOW); // this turn off the leds 
  digitalWrite(Propane,LOW);
  digitalWrite(Hydrogen,LOW);
  digitalWrite(Alcohol,LOW);
  digitalWrite(CO2,LOW);
  digitalWrite(Ammonia,LOW);
}

void loop() {
  ////////////////////////////////DECLEAR MORE VARIABLE FOR MQ2///////////////////////
  float sensor_volt_MQ2; // this is used to calculate sensor votage 
  float RS_gas_MQ2; // this is used to calculate resistence of gas sensitivitt 
  float ratio_MQ2; // this is used to cacuilate the gas ratios 
  float Analog_MQ2_Sensors = analogRead(Analog_MQ2_Sensor); // this is esed to get the sensor input
  sensor_volt_MQ2 = Analog_MQ2_Sensors*(5.0/1023.0);// Convert analog value to voltage
  RS_gas_MQ2 = ((5.0*10.0)/sensor_volt_MQ2)-10.0;// Get the value of RS in gas
  ratio_MQ2 = RS_gas_MQ2/R0_MQ2;
  ////////////////////////////////DECLEAR MORE VARIABLE FOR MQ135///////////////////////
  float sensor_volt_MQ135;
  float RS_gas_MQ135;
  float ratio_MQ135;
  float Analog_MQ135_Sensors = analogRead(Analog_MQ135_Sensor);
  sensor_volt_MQ135 = Analog_MQ135_Sensors*(5.0/1023.0);// Convert analog value to voltage
  RS_gas_MQ135 = ((5.0*10.0)/sensor_volt_MQ135)-10.0;// Get the value of RS in gas
  ratio_MQ135 = RS_gas_MQ135/R0_MQ135;
  //////////////////DISPLAY ON SCREEN SENSITIVITY RESISTANCE OF THE GASES//////////////////
  Serial.print("RS_gas_MQ2:");// this display message RS MQ2 on the screen 
  Serial.print( RS_gas_MQ2); // this put the actual value of RS MQ2 on rthe screen  
  Serial.print(" RS_gas_MQ135:");
  Serial.print( RS_gas_MQ135);
  lcd.setCursor(0,1);
  lcd.print("RS_gas_MQ2:");
  lcd.print(RS_gas_MQ2);
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("RS_MQ135:");
  lcd.print(RS_gas_MQ135);
  delay(2000);
  
  /////////////////////////////////////MQ2 LPG GAS///////////////////////////////////////////
  double ppm_log_LPG = (log10(ratio_MQ2)-b_LPG)/m_LPG;   
  double ppm_MQ2_LPG = pow(10, ppm_log_LPG); //Convert ppm value to log scale 
  double percentage_LPG = ppm_MQ2_LPG/10000;//percentage value

  if(ppm_MQ2_LPG>=800 && ppm_MQ2_LPG<=5000){ //Check if ppm value is greater than 2000 
    Serial.print("  MQ2 LPG in Air: ");
    Serial.print(ppm_MQ2_LPG);
    Serial.print(" percentage_LPG:");
    Serial.print(percentage_LPG); //Percentage value 
    Serial.print("%  "); //Display on screen  "%"
    lcd.begin(16, 2);
    lcd.print("MQ2 LPG in AIR:");
    lcd.setCursor(0,1);
    lcd.print("MQ2 LPG:");
    lcd.print(ppm_MQ2_LPG);
    digitalWrite(LPG, HIGH); //Turn LED on 
    delay(1000);
    
  }else if(ppm_MQ2_LPG<5000 ){
      digitalWrite(LPG, LOW);
      delay(1000);
      }
  delay(1000);
  ///////////////////////////////////MQ2 PROPANE GAS///////////////////////////////////////////
  double ppm_log_Propane = (log10(ratio_MQ2)-b_Propane)/m_Propane;   
  double ppm_MQ2_Propane = pow(10, ppm_log_Propane); //Convert ppm value to log scale 
  double percentage_Propane = ppm_MQ2_Propane/10000;//percentage value

  if(ppm_MQ2_Propane>=900 && ppm_MQ2_Propane<=5000){ //Check if ppm value is greater than 2000 
    Serial.print(" MQ2 PROPANE in AIR: ");
    Serial.print(ppm_MQ2_Propane);
    Serial.print(" percentage_Propane:");
    Serial.print(percentage_Propane); //Percentage value 
    Serial.print("%  "); //Display on screen  "%"
    lcd.begin(16, 2);
    lcd.print("MQ2 PROPANE in AIR:");
    lcd.setCursor(0,1);
    lcd.print("MQ2 PROPANE:");
    lcd.print(ppm_MQ2_Propane);
    digitalWrite(Propane, HIGH); //Turn LED on 
    delay(1000);
    
  }else if(ppm_MQ2_Propane<5000 ){
      digitalWrite(Propane, LOW);
      delay(1000);
      }
  delay(1000);
  ///////////////////////////////////MQ2 HYDROGEN GAS///////////////////////////////////////////
  double ppm_log_Hydrogen = (log10(ratio_MQ2)-b_Hydrogen)/m_Hydrogen;   
  double ppm_MQ2_Hydrogen = pow(10, ppm_log_Hydrogen); //Convert ppm value to log scale 
  double percentage_Hydrogen = ppm_MQ2_Hydrogen/10000;//percentage value

  if(ppm_MQ2_Hydrogen>=1000 && ppm_MQ2_Hydrogen<=10000 ){ //Check if ppm value is greater than 2000 
    Serial.print(" MQ2 HYDROGEN in AIR: ");
    Serial.print(ppm_MQ2_Hydrogen);
    Serial.print(" percentage_Hydrogen:");
    Serial.print(percentage_Hydrogen); //Percentage value 
    Serial.print("%  "); //Display on screen  "%"
    lcd.begin(16, 2);
    lcd.print("MQ2 H2 in AIR:");
    lcd.setCursor(0,1);
    lcd.print("MQ2_H2:");
    lcd.print(ppm_MQ2_Hydrogen);
    digitalWrite(Hydrogen, HIGH); //Turn LED on 
    delay(1000);
    
  }else if(ppm_MQ2_Hydrogen<10000 ){
      digitalWrite(Hydrogen, LOW);
      delay(1000);
      }
  delay(1000);
  ///////////////////////////////////MQ135 ALCOHOL/////////////////////////////////////////
  double ppm_log_Alcohol = (log10(ratio_MQ135)-b_Alcohol)/m_Alcohol;   
  double ppm_MQ135_Alcohol = pow(10, ppm_log_Alcohol); //Convert ppm value to log scale 
  double percentage_Alcohol = ppm_MQ135_Alcohol/10000;//percentage value

  if(ppm_MQ135_Alcohol>100 && ppm_MQ135_Alcohol<=2000 ){ //Check if ppm value is greater than 2000 
    Serial.print("  MQ135 ALCOHOL in Air: ");
    Serial.print(ppm_MQ135_Alcohol);
    Serial.print(" percentage_Alcohol:");
    Serial.print(percentage_Alcohol); //Percentage value 
    Serial.print("%  "); //Display on screen  "%"
    lcd.begin(16, 2);
    lcd.print("MQ135 ALCOHOL:");
    lcd.setCursor(0,1);
    lcd.print("PPM_MQ135:");
    lcd.print(ppm_MQ135_Alcohol);
    digitalWrite(Alcohol, HIGH); //Turn LED on 
    delay(1000);
    
  }else if(ppm_MQ135_Alcohol<2000 ){
      digitalWrite(Alcohol, LOW);
      delay(1000);
      }
  delay(1000);
  //////////////////////////////////MQ135 CO2 GAS//////////////////////////////////////////
  double ppm_log_CO2 = (log10(ratio_MQ135)-b_CO2)/m_CO2;   
  double ppm_MQ135_CO2 = pow(10, ppm_log_CO2); //Convert ppm value to log scale 
  double percentage_CO2 = ppm_MQ135_CO2/10000;//percentage value

  if(ppm_MQ135_CO2>=1000 && ppm_MQ135_CO2<=10000 ){ //Check if ppm value is greater than 2000 
    Serial.print(" MQ135 CO2 in AIR: ");
    Serial.print(ppm_MQ135_CO2);
    Serial.print(" percentage_CO2:");
    Serial.print(percentage_CO2); //Percentage value 
    Serial.print("%  "); //Display on screen  "%"
    lcd.begin(16, 2);
    lcd.print("MQ135 CO2 in AIR:");
    lcd.setCursor(0,1);
    lcd.print("MQ135 CO2:");
    lcd.print(ppm_MQ135_CO2);
    digitalWrite(CO2, HIGH); //Turn LED on 
    delay(1000);
    
  }else if(ppm_MQ135_CO2<2000 ){
      digitalWrite(CO2, LOW);
      delay(1000);
      }
  delay(1000);
  ///////////////////////////////////MQ135 AMMONIA GAS/////////////////////////////////////
  double ppm_log_Ammonia = (log10(ratio_MQ135)-b_Ammonia)/m_Ammonia;   
  double ppm_MQ135_Ammonia = pow(10, ppm_log_Ammonia); //Convert ppm value to log scale 
  double percentage_Ammonia = ppm_MQ135_Ammonia/10000;//percentage value
  
  if(ppm_MQ135_Ammonia>= 300 && ppm_MQ135_Ammonia<=2000 ){ //Check if ppm value is greater than 2000 
    Serial.print(" MQ135 AMMONIA in AIR: ");
    Serial.print(ppm_MQ135_Ammonia);
    Serial.print(" percentage_Ammonia:");
    Serial.print(percentage_Ammonia); //Percentage value 
    Serial.print("%  "); //Display on screen  "%"
    lcd.begin(16, 2);
    lcd.print("MQ135 AMMONIA in AIR:");
    lcd.setCursor(0,1);
    lcd.print("MQ135 AMMONIA in AIR:");
    lcd.print(ppm_MQ135_Ammonia);
    digitalWrite(Ammonia, HIGH); //Turn LED on 
    delay(1000);
    
  }else if(ppm_MQ135_Ammonia<2000 ){
      digitalWrite(Ammonia, LOW);
      delay(1000);
      }
  
  delay(1000);
  /////////////////////////////////////////////////////////////////////////////////////////
    Serial.println();
    delay(10);
}
