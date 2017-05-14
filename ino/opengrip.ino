/**
 * OpenGrip v1.1
 * @author Ond�ej �ilha
 * @created 09.05.2017
 * @mail ondrej.silha@gmail.com
 */

// Knihovna pro pr�ci s pam�t�
#include <EEPROM.h>

int counter = 0;		// �ita� pro akce tla��tka
int pin = 7;			// Tla��tko
int vapepin =9;		// PWM v�stup na mosfet
bool lock = false;		// Z�mek �ita�e
bool hardlock = false;	// Z�mek opengripu
int tempMil = 0;		// Pracovn� prom�nn� (milisekundy)
int tempMil2 = 0;		// Pracovn� prom�nn� (milisekundy)

// Ulo�en� hodnota v�konu ve watech
#define EEPROM_POWER 0

// Ulo�en� hodnota odporu �hav�c�ho dr�tu
#define EEPROM_RESISTANCE 1


/**
 * �vodn� nastaven�
 * @return void
 */
void setup() {
	pinMode(pin, INPUT);
	pinMode(vapepin, OUTPUT);
}

/**
 * Hlavn� smy�ka 
 * @return void
 */
void loop() {
	
	int press = digitalRead(pin); //P�e�te co se d�je na pinu
	
	// Tla��tko zm��knuto, inkrementace �ita�e a z�mek �ita�e.
	if(press == HIGH && !lock)  {
		counter++;
		if(counter == 1)
			tempMil2 = millis();
		tempMil = millis();
		lock = true;
	}
	
	// Tla��tko je zm��kl� a dr�� se - spust� se odpa�ov�n�, pokud nen� za��zen� zam�en� hardlockem.
	// Pokud je zam�eno, zobraz� na displeji z�mek.
	if(press == HIGH && lock && (tempMil + 1000 < millis()))  {
		if(!hardlock) {
			vape();
			counter = 0;
		}
		else {
			//zobrazit z�mek na displeji
		}	
	}
	
	// Tla��tko je vypnut�. Nyn� se rozhodn� jakou akci vykonat.
	// 1 - Zapnout / vypnout displej
	// 2 - 
	// 3 - Zamknout/odemknout za��zen�
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
			if(counter == 3)  {	// 3 - Zamknout/odemknout za��zen�
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
 * Na�te nastaven� a zapne �haven�
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
//	result = 1125300L / result; // V�po�et Vcc (mV); 1125300 = 1.1*1023*1000
	return 0;
}