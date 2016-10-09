

E_FILLING_STATUS fillBottle(int i_qty){
	
	if (i_qty != ZERO_VALS) {

		if(getTankStatus() == TANK_STAUTS_OK){
			
			valve.start(i_qty);
			E_FILLING_STATUS e_filling_status = FILLING_STATUS_NO;
			int scale_qty = 0;
			while(e_filling_status != FILLING_STATUS_NO ){
				
				 scale_qty = scale.read();
				 // LCD.write(scale_qty);
				 if(scale_qty >= i_qty  ){
					 e_filling_status = FILLING_STATUS_OK;
				 }
				
			}
			
			//valve.stop();
			//updateDB();
		}
		
    }

    // displayMessage("Up dateed SD Card");
	   return e_filling_status;
 }


bool updateDB(int i_qty){
	
	SD.write(i_qty);
	
}
E_TANK_STAUTS getTankStatus(){
	
	
  E_TANK_STAUTS e_tank_status = EMPTY_TANK;
  //int int_dispaly = int(float_dispaly_qty);
  //int_tank_qty = sensor.read();
  int int_tank_qty = 0; // WE GET INFO FROM SENSOR
  if (int_tank_qty > TANK_MIN_QTY ) {
    e_tank_status =  TANK_STAUTS_OK;
  }
  else {
    // displayMessage(" TANK IS EMPTY PLEASE FILL THE TANK BEFORE THIS OPERATION ");
    // current_mode = FILLING_REQ;
    tank_mode = EMPTY_TANK;
    e_tank_status = EMPTY_TANK;
  }
  return e_tank_status;
  
}
int incrementVal(int i_display_qty , int i_inc_qty){
	
	return i_display_qty+i_inc_qty;
}
void decrementVal(int i_display_qty , int i_dec_qty){
	
	return i_display_qty-i_dec_qtyss;
} 



/ Taking care of some special events.
void keypadEvent(KeypadEvent key) {

  //  Serial.println("keypadEvent()---> called  ");
  if (tank_mode == TANK_STAUTS_OK) {

    switch (keypad.getState()) {

      case PRESSED:
        // mode_key = key;
        if (key == 'I') {
          //when 'A' is pressed allow the user to input a key.
          INC_DEC_BTN = INC_BTN;
        }
        else if (key == 'D') {
          INC_DEC_BTN = DEC_BTN;
        }

        else if (key == '1') {
          STD_BTN = STD_BTN_1;
        }

        else if (key == '2') {
          STD_BTN = STD_BTN_2;
        }
        else if (key == '3') {
          STD_BTN = STD_BTN_3;
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
