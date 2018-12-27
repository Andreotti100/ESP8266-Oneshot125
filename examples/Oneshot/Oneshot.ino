#include <Oneshot125.h>

Oneshot osFL; // front-left
Oneshot osFR; // front-right
Oneshot osBL; // back-left
Oneshot osBR; // back-right

const int PotPin = 0; // A0
int ppm = 0;
int ppmAvg = 0;
float ema_a = 0.25;

int lowPassFilter_int(float alpha, int latest, int stored)
{
  return round(alpha * latest) + round((1 - alpha) * stored);
}

void setup()
{
//  Serial.begin(115200);

  osFL.attach(3);  // D0
  osFR.attach(14); // D5
  osBL.attach(12); // D6
  osBR.attach(13); // D7

  osFL.write(0);
  osFR.write(0);
  osBL.write(0);
  osBR.write(0);
}

void loop()
{
  ppm = analogRead(PotPin) + 980;

//  Serial.print("PPM: ");
//  Serial.print(ppm);

  ppmAvg = lowPassFilter_int(ema_a, ppm, ppmAvg);

/*
  Serial.print(" - PPM avg: ");
  Serial.print(ppmAvg);
  Serial.println();
*/ 
  osFL.write(ppmAvg);
  osFR.write(ppmAvg);
  osBL.write(ppmAvg);
  osBR.write(ppmAvg);
  delay(25);
}

int lowPassFilter(float alpha, float latest, float stored)
{
  // EMA style low pass filter
  return (alpha * latest) + ((1 - alpha) * stored);
}
