#include <Arduino.h>
#include "dummybounce.h"


void dummybounce::begin(unsigned long interval_millis )
{
	interval(interval_millis);
	previous_millis = millis();
	state = 0x0;
}


void dummybounce::write(int new_state)
       {
       	this->state = new_state;
       }


void dummybounce::interval(unsigned long interval_millis)
{
  this->interval_millis = interval_millis;
  this->rebounce_millis = 0;
}

void dummybounce::rebounce(unsigned long interval)
{
	 this->rebounce_millis = interval;
}



int dummybounce::update()
{
	if ( debounce() ) {
        rebounce(0);
        return stateChanged = 1;
    }

     // We need to rebounce, so simulate a state change
     
	if ( rebounce_millis && (millis() - previous_millis >= rebounce_millis) ) {
        previous_millis = millis();
		 rebounce(0);
		 return stateChanged = 1;
	}

	return stateChanged = 0;
}


unsigned long dummybounce::duration()
{
  return millis() - previous_millis;
}


int dummybounce::read()
{
	return (int)state;
}


// Protected: debounces the pin
int dummybounce::debounce() {
	uint8_t newState = this->dummystate;

	if (state != newState ) {
  		if (millis() - previous_millis >= interval_millis) {
  			previous_millis = millis();
  			state = newState;
  			return 1;
	}
  }
  
  return 0;
	
}

// The risingEdge method is true for one scan after the de-bounced input goes from off-to-on.
bool  dummybounce::risingEdge() { return stateChanged && state; }
// The fallingEdge  method it true for one scan after the de-bounced input goes from on-to-off. 
bool  dummybounce::fallingEdge() { return stateChanged && !state; }

