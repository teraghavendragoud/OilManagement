#include "Arduino.h"

enum MODE_TYPE {
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
enum TANK_STAUTS {
	EMPTY_TANK = 0,
	FULL_TANK = 1,
	THREE_4_TANK = 2,
	HALF_TANK =3,
	QUARTER_TANK =4,
	TEN_PER_OF_TANK = 5,
	TANK_STAUTS_OK = 6,
};

const int led =  13;


