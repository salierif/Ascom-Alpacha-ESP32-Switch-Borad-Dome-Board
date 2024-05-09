#ifndef COVER_VARIABLE
#define COVER_VARIABLE

/* BASE */

struct coverCStruct{
    unsigned int actualValue;
    int cmdValue = -1;
};

coverCStruct coverC;

/* ALPACA */

struct coverCAlpacaParameters{
  unsigned int brightness;
};

/* CONFIG*/

struct coverCSaveConfigStruct{
  bool execute = false;
  bool failed = false;
  bool restartNeeded = false;
};

struct coverCLoadConfigStruct{
  bool isValid = false;
};


#endif