/*
 * GccApplication3.cpp
 *
 * Created: 16/8/2021 17:03:59
 * Author : Wenceslao
 */ 

#include <avr/io.h>
#include <avr/iom2560.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <avr/interrupt.h>


//Prototipos
void initPorts();
void initTimers();


//Variables Globales
volatile uint16_t timeOut10ms;


//Interrupciones
ISR(TIMER1_COMPA_vect){
	
	timeOut10ms--;
	if (!timeOut10ms){
		timeOut10ms = 100;
		
		if(PORTB & (1 << PB7)) 
			PORTB &= ~(1 << PB7); 
		else
			PORTB |= (1 << PB7);
	}
	
}


void initPorts(){
	//Config PIN de LEd como salida (PB7)

	DDRB = (1 << DDB7);
	//DDRB |= (1 << DDB5);

	PORTB |= (1 << PB7);
}

void initTimers(){

	OCR1A = 0x7D0;
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	TCNT1 = 0x00;
	TIFR1 = TIFR1;
	TIMSK1 = (1 << OCIE1A); //0b00000001
	TCCR1B = (1 << WGM12) | (1 << CS11);//activo modo CTC y pongo preescalador 8
}

int main(void)
{

	timeOut10ms = 100;

	initPorts();
	initTimers();
	
	sei(); //pongo en 1 el bit 7 del status para habilitar las int

	/* Replace with your application code */
	while (1){

	}

	
}

