
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

//#include <SD.h>

#include <SPI.h>

#include <EEPROM.h>
#include <common.h>
#include <Keypad.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

//defining the symbols on the buttons of the keypads.
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //{11, 10, 9, 8};//pins connected to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //{7, 6, 5, 4};  //pins connected to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);


//MODE_CHANGE  e_mode_change = INTIAL;
MODE_TYPE current_mode = NOTHING;
MODE_TYPE prev_mode = NOTHING;
TANK_STAUTS tank_mode = TANK_STAUTS_OK;
unsigned int integerValue = 0;
float  float_dispaly_qty = 0.0;
float float_tank_qty = 210.00;
//struct MACHINE_DESC machine_desc;
float f_mode_1 = 0;
float f_mode_2 = 0;
void setup() {

  Serial.begin(9600);
  pinMode(led, OUTPUT);

  f_mode_1 = 900; // read form sd card
  f_mode_2 = 100; // read form sd card

  // if(1){
  if (readTankStatus(20.0)) { ///   DANGerous code start

    //displayMessage("you can press  A / B / C / D    to continue");
  }
  else {
    current_mode = FILLING_REQ;
    tank_mode = EMPTY_TANK;
  }  ///   DANGerous code end

  //  Serial.println(" <<<<<<<<<<<<<<<<<<<<   you can press  A / B / C / D    to continue >>>>>>>>>>>>  ");
  // Add an event listener for this keypad
  // keypad.setHoldTime(2*1000);
  keypad.addEventListener(keypadEvent);
}

void loop() {
  //scan the pins of the keypad
  char key = keypad.getKey();

  //blink the LED
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);

  //displayMessage(" TANK level sensor  ");
  //delay(2*1000);

  if (tank_mode == TANK_STAUTS_OK) {  ///   DANGerous code start

    if (current_mode != NOTHING) {
      // displayMessage("LOOP 2 PASSED");
      getKeyPadInput();
    }


  }
  else if (tank_mode == EMPTY_TANK) {
    displayMessage("FILLING_REQ IS REQUIRED ");
  }  ///   DANGerous code end


  //if (mode_change == true) showModeValue();

  //
  //  1. read tank statuS  , 2. read abort status to stop filling 3.
  //
}

// Taking care of some special events.
void keypadEvent(KeypadEvent key) {

  //  Serial.println("keypadEvent()---> called  ");
  if (tank_mode == TANK_STAUTS_OK) {

    switch (keypad.getState()) {

      case PRESSED:
        // mode_key = key;
        if (key == 'A') {
          //when 'A' is pressed allow the user to input a key.
          current_mode = REGULAR_MODE;
        }
        else if (key == 'B') {
          current_mode = FAST_MODE_1;
        }

        else if (key == 'C') {
          current_mode = FAST_MODE_2;
        }

        else if (key == '#') {
          current_mode = CONTINUE;
        }
        else if (key == '*') {
          current_mode = CANCEL;
        }
          break;

    } // switch end

  }


}


void getKeyPadInput() {

  integerValue = 0;
  char incomingByte;

  if (current_mode == REGULAR_MODE) {
    integerValue = 0;
    integerValue = getKeypadInput();

    float_dispaly_qty = (float)integerValue / 1000.000;
    //    displayMessage("The Entered value is ");
    //   displayFloatMessage(float_dispaly_qty);
    //  Serial.println(" -- MLS PRESS  # to continue  [or] prees * to cancel ");
    //fillBottle(); // 06/10/2016
    current_mode = NOTHING;
    prev_mode = current_mode;


  } // REGULAR_MODE END
  else if (current_mode == FAST_MODE_1) {
    //   Serial.println(" <<<<<<<<<<<<<<<<<<<<  FAST_MODE_1   >>>>>>>>>>>>  ");

    current_mode = NOTHING;
    prev_mode = current_mode;
    float_dispaly_qty = f_mode_1 / 1000;
    //   Serial.println(" <<<<<<<<<<<<<<<<<<<<    PRESS  # to continue  [or] prees * to cancel >>>>>>>>>>>>  ");
  }
  else if (current_mode == FAST_MODE_2) {
    //   Serial.println(" <<<<<<<<<<<<<<<<<<<<  FAST_MODE_2  >>>>>>>>>>>>  ");
    current_mode = NOTHING;
    prev_mode = current_mode;
    float_dispaly_qty = f_mode_2 / 1000;
    //  Serial.println(" <<<<<<<<<<<<<<<<<<<<   \n PRESS  # to continue  [or] prees * to cancel >>>>>>>>>>>>  ");
  }
  else if (current_mode == FAST_MODE_3) {
    //  Serial.println("\n FAST_MODE_3 \n");
    current_mode = NOTHING;
    prev_mode = current_mode;
  }
  else if (current_mode == CONTINUE) {

    if (float_dispaly_qty != 0.00) {
      if (readTankStatus(float_dispaly_qty))
        fillBottle(float_dispaly_qty);
    }
    else {
      // Serial.println(" <<<<<<<<<<<<<<<<<<<<  Please enter more than zero value >>>>>>>>>>>>  ");
    }

    if (tank_mode != EMPTY_TANK)
      //    Serial.println("\n PREES # FOR CONTINUE \n [or] * FOR CANCEL ");
      //incomingByte = keypad.waitForKey();
      current_mode = NOTHING;
  }
  else if (current_mode == CANCEL) {
    // Serial.println("\n CANCEL \n");
    current_mode = NOTHING;
    //    digitalWrite(led, HIGH);
    //  Serial.println(" <<<<<<<<<<<<<<<<<<<<   you can press  A / B / C / D    to continue >>>>>>>>>>>>  ");
    //  incomingByte = keypad.waitForKey();
  }

}

void fillBottle(float f_qty)
{
  if (f_qty != 0.00) {

    for (int i = 0; i < 10 ; i++) {

      Serial.print("****   ");
      // Serial.print(f_qty);
      //  Serial.print("****   ");
      //   Serial.print(float_tank_qty);
      float_tank_qty = float_tank_qty - 10.00;
      //   Serial.print("\n");
      delay(500);
    }

    // displayMessage("Up dateed SD Card");
  }

}
bool readTankStatus(double float_dispaly_qty)
{
  bool bool_tank_status = false;
  int int_dispaly = int(float_dispaly_qty);
  int int_tank_qty = int(float_tank_qty); // WE GET INFO FROM SENSOR
  if (int_tank_qty > (int_dispaly + 10) ) {
    bool_tank_status =  true;
  }
  else {
    // displayMessage(" TANK IS EMPTY PLEASE FILL THE TANK BEFORE THIS OPERATION ");
    // current_mode = FILLING_REQ;
    tank_mode = EMPTY_TANK;
    bool_tank_status = false;
  }
  return bool_tank_status;
}
void displayMessage(char *strMessage) {
  // Serial.print("<<<<<     ");
  //  Serial.print(strMessage);
  //  Serial.println("     >>>>>");
}
void displayFloatMessage(float f_val) {
  //erial.print("<<<<<     ");
  //  Serial.print(f_val);
  //Serial.println("     >>>>>");
}

int getKeypadInput()
{
  char incomingByte;
  int integerValue = 0;
  // TERG : REGULAR_MODE START
  // displayMessage("   please enter the value below 10000 ML or 10 ltrs  end with 'D'   ");
  while (1) {           // force into a loop until 'n' is received
    incomingByte = keypad.waitForKey();
    //
    // look for enter and zero checking
    //
    if (incomingByte == 'D') { // TERG : look for enter and zero checking
      if (integerValue != 0)
        break;
      else {
        displayMessage("**************** Error ::  Please enter more tham 0 value   ************ ");
      }
    }   // TERG : look for enter and zero checking
    //
    //    CHECK FOR NUMERICS ONLY ,
    //
    else if (incomingByte != 'A' && incomingByte != 'B' && incomingByte != 'C' && incomingByte != '*' && incomingByte != '#') {
      //     Serial.print(incomingByte);
      if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1
      integerValue *= 10;  // shift left 1 decimal place
      // convert ASCII to integer, add, and shift left 1 decimal place
      integerValue = ((incomingByte - 48) + integerValue);
      if (integerValue > 10000) {
        displayMessage("   Value Exceeded .... please enter the value below 10000 ML or 10 ltrs    ");
        integerValue = 0;
      }
    }
  } // WHILE (1) END

  return  integerValue;

}

