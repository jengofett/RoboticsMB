#include <microM.h>


void setup()
{ 
  microM.Setup();
  Serial.begin(19200); // set the serial port speed.
  microM.ircommand=10; // stopped.
}

void loop()
{
  const int forwardButton=58;
  const int backwardsButton=59;
  const int adjustment=-50;
  const int stopbutton=62;
  const int leftbutton=60;
  const int rightbutton=61;
  if (microM.ircommand==forwardButton)
  {
    microM.Motors(500,500+adjustment,0,0);
  } else if (microM.ircommand == backwardsButton)
  {
    microM.Motors(-500,-500,0,0);

  }  else if (microM.ircommand == leftbutton)
  {
    microM.Motors(500,0,0,0);
  } else if (microM.ircommand == stopbutton)
  {
    microM.Motors(0,0,1,1);
  } else if (microM.ircommand == rightbutton) 
{
  microM.Motors(0,500,0,0);
}
}
