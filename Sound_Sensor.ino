// Pin Defination
// Analog Pin
int micPin = A0;                  // For Mic Analog Input
// Define Digital Output Pin
int Relay11 = 13;                    // For Relay Digital Output

// Macros Defination
#define AVG_COUNT           5
#define THERSHOLD           350

// Variables Defination
boolean LightOFFFlag = true;
int MicActualValue;
int AvgValue;
unsigned char AvgCounter = 0;
int BluetoothStatus;

void setup() 
{
    pinMode(Relay11, OUTPUT);        // Set Realy as Digital Output
    pinMode(micPin, INPUT);       // Set Mic Input As Input 
    digitalWrite(Relay11, LightOFFFlag);
    Serial.begin(38400);            // Default communication Rate for Bluethooth module
}

void loop() 
{
//___________________________________ Bluetooth Acess _______________________________
  if(Serial.available()>0)                  //check data is avaiable on Bluetooth
    BluetoothStatus = Serial.read();        // Read the Data from Bluetooth

    if(BluetoothStatus == '0')              // Received command for TURN OFF Light
    {
          digitalWrite(Relay11, LightOFFFlag);   // Turn OFF Light
          LightOFFFlag = true;
          Serial.println("LED: OFF");           // Send back status to the phone as Light is TURN OFF.
    }
    if(BluetoothStatus == '1')              // Received command for TURN ON Light
    {
        digitalWrite(Relay11, LightOFFFlag);  // Turn ON Light
        LightOFFFlag = false;
        Serial.println("LED: ON");           // Send back status to the phone as Light is TURN ON.
    }
  
//___________________________________ Mic Process Code _______________________________
  AvgValue = 0;     // Clear Variable
  for(AvgCounter = 0; AvgCounter < AVG_COUNT;AvgCounter++)
    AvgValue += analogRead(micPin);

    AvgValue /= AVG_COUNT;      // Average Value
  
    MicActualValue = AvgValue;    // Shift in Actual Value Variable
    
    if(MicActualValue > THERSHOLD)     // if Clap is done
    {
//        Serial.println(MicActualValue);
         if(LightOFFFlag == false)                // Light is ON
         {
          digitalWrite(Relay11, LightOFFFlag);   // Turn OFF Light
          LightOFFFlag = true;
        }
        else                                     // Light is OFF
        {
          digitalWrite(Relay11, LightOFFFlag);  // Turn ON Light
          LightOFFFlag = false;
        }
        delay(1000);
    }
}
