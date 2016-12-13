#include <avr/io.h>
#include <avr/interrupt.h>

/* This is the number of 10ms delays to give us the desired LED periods of time. */
#define LED_BLINK_TIME 100

/* These constants are the different states of the blinking LED state machine.
enum
{
  fadeIn,
  on,
  fadeOut,
  off,
  final /* reset state */
};

/* This variable holds the state of the LED. */
uint8_t ledState,
/* This variable counts the number of 10ms delays */
        ledDelay = LED_BLINK_TIME;

/* A flag that is set every time Timer 0 times out (10ms).  Make it volatile
   so the compiler won't optimize it out and it will be visible in the main()
   function. */
volatile uint8_t t010msFlag;

/* This is the Timer 0 Compare A interrupt service routine.  Runs every 10ms
   when the timer times out.  All it does is sets a flag.
   - Important to keep it simple! */
ISR(TIMER0_COMPA_vect)
{
  t010msFlag = 1;
}

/* This is where it all happens. */
int main(void)
{
  /* Initialize pin 6 as output */
  DDRD |= _BV(PORTD6); 
  PORTD &= ~_BV(PORTD6);

  /* Set up Timer 0:
     - clocked by F_CPU / 1024
     - generate interrupt when OCR0A matches TCNT0
     - load OCR0A with the delay count to get 10ms delay
   */
  TCCR0A = 0b00000010; /* TC0 mode 2, CTC - clear timer on match A */
  TCCR0B = 0b00000101; /* clock by F_CPU / 1024 */
  OCR0A = 155; /* = F_CPU / 1024 / 100 - 1 */
  TIMSK0 = 0b00000010; /* enable OCIE0, match A interrupt */

  /* enable the interrupt system */
  sei();

  /* run around this loop for ever */
  while (1)
  {
    if(t010msFlag == 1) /* test the 10ms flag, is it set? */
    {
      t010msFlag = 0; /* reset the flag */
      
      if(ledDelay-- == 0) /* count another 10ms, time up yet? */
      {
        ledDelay = LED_BLINK_TIME; /* reset the delay counter */
        
        if(++ledState == maxLedState) /* advance to the next state */
        {
          ledState = ledState0; /* reset the state to the first state */
        }
        
        /* test ledState and do what we need to do */
        switch(ledState)
        {
          case fadeIn:
            DDRD |= _BV(PORTD3);
            PORTD &= ~_BV(PORTD3);
            
            break;

          case on:
            PORTD |= _BV(PORTD3);
            break;

          case fadeOut:
            PORTD |= _BV(PORTD3);
            break;        

          case off:
            PORTD &= ~_BV(PORTD3);
            break;

          default:
            break;

        }/* end switch(ledState) */
        
      }/* end if(ledDelay-- == 0) */
      
    }/* end if(t010msFlag == 1) */
    
  }/* end while(1) */
  
}/* end main() */
