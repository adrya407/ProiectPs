// avr-libc library includes
#include <avr/io.h> //  can be omitted
#include <avr/interrupt.h> // can be omitted
                         
void setup()
{
//pinMode(LEDPIN, OUTPUT);
DDRB = DDRB | B00100000; 

// initialize Timer1
cli();         // disable global interrupts
TCCR1A = 0;    // set entire TCCR1A register to 0
TCCR1B = 0;    // set entire TCCR1A register to 0

// enable Timer1 overflow interrupt:
TIMSK1 |= (1 << TOIE1);
TCNT1=0x0BDC;
TCCR1B |= (1 << CS12); 
// enable global interrupts:
sei();
}

ISR(TIMER1_OVF_vect)
{
//PORTB ^= ~_BV(PORTB5); //am incercat sa setam prin registrii si nu functioneaza
TCNT1=0x0BDC; // reload the timer preload
}

void loop() {}
