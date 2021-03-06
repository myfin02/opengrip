/**
 * -------------
 * OpenGrip v1.1
 * -------------
 * @author Ondrej Silha
 * @date 2017/04/05
 * <properties>
 *   - Firmware for open-source electronic ciggarete.
 *   - Powered by arduino nano.
 * </properties>
 */

#include <EEPROM.h>
#include <pgmspace.h>
#define nextion Serial

// Basic variables
int hulPin = 9;
int runPin = 7;
int upPin = 6;
int downPin = 5;
int workVar;
int power;
bool locked = false;
int lockCounter = 0;
int MEMORY_POWER = 0;
int initVar = 0;

/**
 * Setup arduino after start.
 */
void setup() {
	pinMode(runPin, INPUT);
	pinMode(upPin, INPUT);
	pinMode(downPin, INPUT);
	pinMode(hulPin, OUTPUT);
	checkMemoryValues();
	power = getPower();
	nextion_init(9600);

}

/**
 * Main loop.
 */
void loop() {

	if(!initVar) {
		initialize();
		initVar = false;
	}
	check_display();

	if(!locked) {
		checkRun();
	}
	else {

	}
}

/**
 * Check is runpin is pressed. If pressed then open mosfet with
 * set power, else close mosfet.
 */
void checkRun() {
	workVar = digitalRead(runPin);

	if(workVar == HIGH) {
		run(power);
	}
	else {
		digitalWrite(hulPin, LOW);
	}
}

void initialize() {
	power = getPower();
}

/**
 * Open or close MOSFET with power value.
 * @var power integer Power of PWM (0 - 255)
 */
void run(int power) {
	analogWrite(hulPin, power);
}

/**
 * Returm power from EEPROM
 */
int getPower() {
	return EEPROM.read(MEMORY_POWER);
}

/**
 * Check if EEPROM is set. If eeprom is no set this funkction
 * put it the default values
 */
void checkMemoryValues() {
	//Power
	if(EEPROM.read(MEMORY_POWER) <= 0)
		EEPROM.write(MEMORY_POWER, 10);
}



void nextion_init(int speed_init) {	// nastaveni pri spusteni displeje
	nextion.begin(speed_init);
}

void touch_Return(String page_ID, String component_ID, String touch_event) {
	if (page_ID == "0") {
		if (component_ID == "1") {

		}
	}
}
//------------------------------------------------------------------
void page_Return(String page_ID) {	}
//------------------------------------------------------------------


String Nextion_receive(boolean read_data)  {

	boolean answer = false; // znacka
	char bite; // promenna pro ulozeni znaku
	String cmd; // promenna pro ulozeni textu
	byte countEnd = 0; // pocitadlo
	unsigned long previous; // cas spusteni
	int timeout = 1000; // doba po kterou se ceka na prichozi data
	previous = millis();


	if (nextion.available() > 0)  {
		bite = nextion.read();
		cmd += bite;
		if ((byte)bite == 0xff) countEnd++;
			if (countEnd == 3) answer = true;
	}

	while (!answer && !((unsigned long)(millis() - previous) >= timeout));

	if (read_data) {	// read general data
		if (cmd[0] == 0x65) {	// Touch event return data
			// 0X65 + Page ID + Component ID + TouchEvent + End
			touch_Return(String(cmd[1], DEC), String(cmd[2], DEC), String(cmd[3], DEC));
		}
		else if (cmd[0] == 0x66) {	// Current page ID number returns
			// 0X66 + Page ID + End
			page_Return(String(cmd[1], DEC));
		}
		else if (cmd[0] == 0x67) {	// Touch coordinate data returns

		}
		else if (cmd[0] == 0x68) {	// Touch Event in sleep mode

		}
	}
	else {	//read get data
		if (cmd[0] == 0x70) {	// String variable data returns
			// X70+Variable Content in ASCII code+End
			return cmd;
		}
		else if (cmd[0] == 0x71) {	// Numeric variable data returns
			// 0X71+variable binary data(4 bytes little endian mode, low in front)+End
			return cmd;
		}
	}
}


	void check_display() {	// kontrola prijatych dat
		if (nextion.available() > 0) // kontroluje obsah pameti, pokud nen nic odeslano, dalsi cast programu se neprovede
		{

			Nextion_receive(true); // precist hodnoty z serial portu
		}
	}

	void visible(String componentID, boolean visible) {

	}
	//------------------------------------------------------------------
	void send_Command(const char* cmd) {	// odeslani dat do displeje
		nextion.print(cmd);
		nextion.write(0xFF);
		nextion.write(0xFF);
		nextion.write(0xFF);
		nextion.flush();
	}
 