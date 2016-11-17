// Persjon.h

#ifndef _PERSJON_h
#define _PERSJON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PersjonClass
{
 protected:


 public:
	void init();
};

extern PersjonClass Persjon;

#endif

