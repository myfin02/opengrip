/**
 * OpenGrip v1.1
 * @author Ondøej Šilha
 * @created 09.05.2017
 * @mail ondrej.silha@gmail.com
 */

// Knihovna pro práci s pamìtí
#include <EEPROM.h>

int counter = 0;		// Èitaè pro akce tlaèítka
int pin = 7;			// Tlaèítko
int vapepin =9;		// PWM výstup na mosfet
bool lock = false;		// Zámek èitaèe
bool hardlock = false;	// Zámek opengripu
int tempMil = 0;		// Pracovní promìnná (milisekundy)
int tempMil2 = 0;		// Pracovní promìnná (milisekundy)

// Uložená hodnota výkonu ve watech
#define EEPROM_POWER 0

// Uložená hodnota odporu žhavícího drátu
#define EEPROM_RESISTANCE 1


/**
 * Úvodní nastavení
 * @return void
 */
void setup() {
	pinMode(pin, INPUT);
	pinMode(vapepin, OUTPUT);
}

/**
 * Hlavní smyèka 
 * @return void
 */
void loop() {
	
	int press = digitalRead(pin); //Pøeète co se dìje na pinu
	
	// Tlaèítko zmáèknuto, inkrementace èitaèe a zámek èitaèe.
	if(press == HIGH && !lock)  {
		counter++;
		if(counter == 1)
			tempMil2 = millis();
		tempMil = millis();
		lock = true;
	}
	
	// Tlaèítko je zmáèklé a drží se - spustí se odpaøování, pokud není zaøízení zamèené hardlockem.
	// Pokud je zamèeno, zobrazí na displeji zámek.
	if(press == HIGH && lock && (tempMil + 1000 < millis()))  {
		if(!hardlock) {
			vape();
			counter = 0;
		}
		else {
			//zobrazit zámek na displeji
		}	
	}
	
	// Tlaèítko je vypnuté. Nyní se rozhodnì jakou akci vykonat.
	// 1 - Zapnout / vypnout displej
	// 2 - 
	// 3 - Zamknout/odemknout zaøízení
	// 4 - 
	// 5 - Zobrazit info o autorovi :-)
	if(press == LOW)  {
		lock = false;
		digitalWrite(vapepin , LOW);	
		
		if(tempMil2 + 3000 < millis())  {
			if(counter == 1)  {	// 1 - Zapnout / vypnout displej
			}
			if(counter == 2)  {
			}
			if(counter == 3)  {	// 3 - Zamknout/odemknout zaøízení
				if(hardlock)
					hardlock = false;
				else
					hardlock = true;		
			}
			if(counter == 4)  {
			}
			if(counter == 5)  {	// 5 - Zobrazit info o autorovi 
			}
			counter = 0;
		}
	}
}

/**
 * Naète nastavení a zapne žhavení
 * @return void
 */
void vape() {
	int savedPower = EEPROM.read(EEPROM_POWER);
	int resistance = EEPROM.read(EEPROM_RESISTANCE); 
	
}

long readVcc() {
//	#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
//	ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
//	#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
//	ADMUX = _BV(MUX5) | _BV(MUX0);
//	#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
//	ADMUX = _BV(MUX3) | _BV(MUX2);
//	#else
//	ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
//	#endif
//	delay(2);
//	ADCSRA |= _BV(ADSC);
//	while (bit_is_set(ADCSRA,ADSC));
//	uint8_t low = ADCL;
//	uint8_t high = ADCH;
//	long result = (high<<8) | low;
//	result = 1125300L / result; // Výpoèet Vcc (mV); 1125300 = 1.1*1023*1000
	return 0;
}