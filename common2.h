#include "Arduino.h"

enum E_MODE_TYPE {
	NOTHING = 0,
	MENU_MODE = 1,
	REGULAR_MODE = 'A',
	FAST_MODE_1= 'B',
	FAST_MODE_2= 'C',
	FAST_MODE_3= 'D',
	CONTINUE = '#',
	CANCEL = '*',
	FILLING_REQ = 2 ,
};
enum E_TANK_STAUTS {
	EMPTY_TANK = 0,
	FULL_TANK = 1,
	THREE_4_TANK = 2,
	HALF_TANK =3,
	QUARTER_TANK =4,
	TEN_PER_OF_TANK = 5,
	TANK_STAUTS_OK = 6,
};
enum E_STANDARD_BUTTON {
	STD_BTN_NO= 0,
	STD_BTN_1 = 1,
	STD_BTN_2 = 2,
	STD_BTN_3 = 3,
	STD_BTN_4 = 4,
	
};
enum E_FLEXIBLE_BUTTON {
	FLX_BTN_NO= 0,
	FLX_BTN_1 = 1,
	FLX_BTN_2 = 2,
	FLX_BTN_3 = 3,
	FLX_BTN_4 = 4,
	
};
enum E_INC_DEC_BUTTON {
	INC_DEC_BTN_NO= 0,
	DEC_BTN = 1,
	INC_BTN = 2,
};
enum E_LOC_ULC_BUTTON {
	LOC_ULC_BTN_NO= 0,
	LOC_BTN = 1,
	ULC_BTN = 2,
};

enum E_VALVE_STATUS {
	VALVE_STATUS_OFF = 0,
	VALVE_STATUS_ON = 1,
};
enum E_FILLING_STATUS {
	FILLING_STATUS_NO = 0,
	FILLING_STATUS_OK = 1,
};

#define DEC_INC_VAL_10		10
#define DEC_INC_VAL_100		100
#define TANK_MIN_QTY		20000
#define DRAW_MAX_QTY		5000

#define STD_BTN_1_VAL		50
#define STD_BTN_2_VAL		100
#define STD_BTN_3_VAL		500
#define STD_BTN_4_VAL		1000
#define ZERO_VAL 0

const int led =  13;
const int FLX_BTN_1_VAL =  0;
const int FLX_BTN_2_VAL =  0;
const int FLX_BTN_3_VAL =  0;
const int FLX_BTN_4_VAL =  0;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns


E_STANDARD_BUTTON STD_BTN 		= STD_BTN_NO;
E_FLEXIBLE_BUTTON FLX_BTN 		= FLX_BTN_NO;
E_INC_DEC_BUTTON INC_DEC_BTN    = INC_DEC_BTN_NO;
E_LOC_ULC_BUTTON				= LOC_ULC_BTN_NO;

int i_display_req_qty = 0;
int i_tank_qty = 0;

E_FILLING_STATUS fillBottle(int i_qty);
bool updateDB(int i_qty);
bool getTankStatus();
void incrementVal(int i_display_qty , int i_inc_qty); 
void decrementVal(int i_display_qty , int i_dec_qty); 





