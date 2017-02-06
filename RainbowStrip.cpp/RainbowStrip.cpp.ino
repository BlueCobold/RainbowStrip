
#include <EEPROM.h>
#include <LPD6803.h>

const int SIN_AMPLITUDE = 127;
const int SIN_TO_COLOR = 127 / 31;
const int SIN_PERIODE = 511;

// table-gen
/*
  #include <iostream>
  #include <cmath>

  int main() {
  for (int i = 0; i < 512; i++) {
    std::cout << (int)(round(127*sinf(i/256.0*3.14159))) << ", ";
    if ((i % 15) == 14)
      std::cout << std::endl;
  }
  // your code goes here
  return 0;
  }
*/
const unsigned int rgbTable[] = {31, 30, 1053, 2076, 3099, 4122, 5145, 6168, 7191, 8214, 9237, 10260, 11283, 12306, 13329, 14352, 15375, 16398, 17421, 18444, 19467, 20490, 21513, 22536, 23559, 24582, 25605, 26628, 27651, 28674, 29697, 30720, 31744, 30720, 29728, 28736, 27744, 26752, 25760, 24768, 23776, 22784, 21792, 20800, 19808, 18816, 17824, 16832, 15840, 14848, 13856, 12864, 11872, 10880, 9888, 8896, 7904, 6912, 5920, 4928, 3936, 2944, 1952, 960, 992, 960, 929, 898, 867, 836, 805, 774, 743, 712, 681, 650, 619, 588, 557, 526, 495, 464, 433, 402, 371, 340, 309, 278, 247, 216, 185, 154, 123, 92, 61, 30};
const char sinTable[] = { 0, 2, 3, 5, 6, 8, 9, 11, 12, 14, 16, 17, 19, 20, 22,
                          23, 25, 26, 28, 29, 31, 32, 34, 35, 37, 38, 40, 41, 43, 44,
                          46, 47, 49, 50, 51, 53, 54, 56, 57, 58, 60, 61, 63, 64, 65,
                          67, 68, 69, 71, 72, 73, 74, 76, 77, 78, 79, 81, 82, 83, 84,
                          85, 86, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100,
                          101, 102, 103, 104, 105, 106, 106, 107, 108, 109, 110, 111, 111, 112, 113,
                          113, 114, 115, 115, 116, 117, 117, 118, 118, 119, 120, 120, 121, 121, 122,
                          122, 122, 123, 123, 124, 124, 124, 125, 125, 125, 125, 126, 126, 126, 126,
                          126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
                          127, 126, 126, 126, 126, 126, 125, 125, 125, 125, 124, 124, 124, 123, 123,
                          122, 122, 122, 121, 121, 120, 120, 119, 118, 118, 117, 117, 116, 115, 115,
                          114, 113, 113, 112, 111, 111, 110, 109, 108, 107, 106, 106, 105, 104, 103,
                          102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88,
                          86, 85, 84, 83, 82, 81, 79, 78, 77, 76, 74, 73, 72, 71, 69,
                          68, 67, 65, 64, 63, 61, 60, 58, 57, 56, 54, 53, 51, 50, 49,
                          47, 46, 44, 43, 41, 40, 38, 37, 35, 34, 32, 31, 29, 28, 26,
                          25, 23, 22, 20, 19, 17, 16, 14, 12, 11, 9, 8, 6, 5, 3,
                          2, 0, -2, -3, -5, -6, -8, -9, -11, -12, -14, -16, -17, -19, -20,
                          -22, -23, -25, -26, -28, -29, -31, -32, -34, -35, -37, -38, -40, -41, -43,
                          -44, -46, -47, -49, -50, -51, -53, -54, -56, -57, -58, -60, -61, -63, -64,
                          -65, -67, -68, -69, -71, -72, -73, -74, -76, -77, -78, -79, -81, -82, -83,
                          -84, -85, -86, -88, -89, -90, -91, -92, -93, -94, -95, -96, -97, -98, -99,
                          -100, -101, -102, -103, -104, -105, -106, -106, -107, -108, -109, -110, -111, -111, -112,
                          -113, -113, -114, -115, -115, -116, -117, -117, -118, -118, -119, -120, -120, -121, -121,
                          -122, -122, -122, -123, -123, -124, -124, -124, -125, -125, -125, -125, -126, -126, -126,
                          -126, -126, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127,
                          -127, -127, -126, -126, -126, -126, -126, -125, -125, -125, -125, -124, -124, -124, -123,
                          -123, -122, -122, -122, -121, -121, -120, -120, -119, -118, -118, -117, -117, -116, -115,
                          -115, -114, -113, -113, -112, -111, -111, -110, -109, -108, -107, -106, -106, -105, -104,
                          -103, -102, -101, -100, -99, -98, -97, -96, -95, -94, -93, -92, -91, -90, -89,
                          -88, -86, -85, -84, -83, -82, -81, -79, -78, -77, -76, -74, -73, -72, -71,
                          -69, -68, -67, -65, -64, -63, -61, -60, -58, -57, -56, -54, -53, -51, -50,
                          -49, -47, -46, -44, -43, -41, -40, -38, -37, -35, -34, -32, -31, -29, -28,
                          -26, -25, -23, -22, -20, -19, -17, -16, -14, -12, -11, -9, -8, -6, -5, -3, -2
                        };

unsigned long lastUpdate;
unsigned long lastFUpdate;
unsigned long stepTime;
unsigned long steps;
float fsteps;
byte mode;
int wait;
int potiValue;
unsigned long lastTap;
unsigned long loops;

const int dataPin = 2;
const int clockPin = 3;
LPD6803 strip = LPD6803(50, dataPin, clockPin);

void setup() {
  lastUpdate = millis();
  lastFUpdate = lastUpdate;
  lastTap = 0;
  stepTime = 1000 / 5;
  steps = 0;
  mode = EEPROM.read(0);
  wait = 50;
  loops = 0;
  potiValue = 0;

  pinMode(A3, INPUT_PULLUP);
  strip.setCPUmax(50);
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

int sinT(unsigned long x) {
  return sinTable[x % 512];//& SIN_PERIODE];
}

unsigned int rgb(int r, int g, int b) {
  return ((((unsigned int)g >> 3) & 0x1F) << 10)
         | ((((unsigned int)r >> 3) & 0x1F) << 5)
         | (((unsigned int)b >> 3) & 0x1F);
}

unsigned int color(int r, int g, int b) {
  return (((unsigned int)g & 0x1F) << 10) | (((unsigned int)b & 0x1F) << 5) | ((unsigned int)r & 0x1F);
}

unsigned int rainbow(unsigned long x) {
  const int PERIODE = 6 * 32;
  int i = x % PERIODE;
  if (i >= 5 * 32) {
    return color(31, 0, 6 * 32 - i - 1); // purple -> red
  } else if (i >= 4 * 32) {
    return color(i - 4 * 32, 0, 31); // blue -> purple
  } else if (i >= 3 * 32) {
    return color(0, 4 * 32 - i - 1, 31); // turquise -> blue
  } else if (i >= 2 * 32) {
    return color(0, 31, i - 2 * 32); // green -> turqoise
  } else if (i >= 32) {
    return color(2 * 32 - i - 1, 31, 0); // yellow -> green
  } else {
    return color(31, i, 0); // red -> yellow
  }
}

unsigned int mix(unsigned int c1, unsigned int c2, long x) {
  int y = 32 - x;
  return (((c1 & 0x1F) * y + (c2 & 0x1F) * x) >> 5)
         | ((((c1 >> 5) & 0x1F) * y + ((c2 >> 5) & 0x1F) * x) & 0x3E0)
         | (((((c1 >> 10) & 0x1F) * y + ((c2 >> 10) & 0x1F) * x) & 0x3E0) << 5);
}

unsigned int mix(unsigned int c1, unsigned int c2, unsigned int c3, long x) {
  const int PERIODE = 3 * 32;
  int i = x % PERIODE;
  if (i >= 2 * 32) {
    return mix(c3, c1, i - 2 * 32);
  } else if (i >= 32) {
    return mix(c2, c3, i - 32);
  } else {
    return mix(c1, c2, i);
  }
}

void checkMode(unsigned long now) {
  int tapValue = analogRead(A3);
  if (tapValue > 50) {
    lastTap = now;
  }
  if (now - lastTap > 200) {
    mode++;
    EEPROM.write(0, mode);
    lastTap = now;
  }
  Serial.println(tapValue);
  //mode = 10;
}

void updateSteps(unsigned long now) {
  unsigned long delta = now - lastUpdate;
  potiValue = (loops & 7) == 0 ? analogRead(A2) : potiValue;
  stepTime = 5 + 5 * (potiValue / 50);
  if (stepTime >= 100) {
    lastUpdate = now;
    lastFUpdate = now;
    return;
  }
  fsteps += (now - lastFUpdate)/(5.0 * stepTime);
  lastFUpdate = now;
  if (delta > stepTime) {
    lastUpdate = now;
    while (delta > stepTime) {
      steps++;
      delta -= stepTime;
    }
  }
}

void loop() {
  loops++;
  unsigned long now = millis();

  updateSteps(now);
  checkMode(now);

  switch (mode) {
    case 0: {
      unsigned int s1 = (unsigned int)(2 * fsteps);
      for (int i = 0; i < strip.numPixels(); i++)
        strip.setPixelColor(i, rainbow(s1));
      break;
    }
    case 1: {
      unsigned int s1 = (unsigned int)(4 * fsteps);
      for (int i = 0; i < strip.numPixels(); i++)
        strip.setPixelColor(i, rainbow(i * 3 + s1));
      break;
    }
    case 2: {
      unsigned int s1 = (unsigned int)(6 * fsteps);
      for (int i = 0; i < strip.numPixels(); i++)
        strip.setPixelColor(i, rainbow(i * 8 + s1));
      break;
    }
    case 3: {
      unsigned int s1 = (unsigned int)(8 * fsteps);
      for (int i = 0; i < strip.numPixels(); i++)
        strip.setPixelColor(i, rainbow(i * 20 + s1));
      break;
    }
    case 4: {
      unsigned int s1 = (unsigned int)(fsteps * 12);
      unsigned int s2 = (unsigned int)(fsteps * 16);
      unsigned int s3 = (unsigned int)(fsteps * 26);
      for (int i = 0; i < strip.numPixels(); i++)
        strip.setPixelColor(i, rgb(127 + sinT(i * 10 + s1),
                                   127 + sinT(i * 30 + s2),
                                   127 + sinT(i * 50 - s3)));
      break;
    }
    case 5: {
      unsigned int s1 = (unsigned int)(fsteps * 16);
      unsigned int s2 = (unsigned int)(fsteps * 21);
      unsigned int s3 = (unsigned int)(fsteps * 26);
      for (int i = 0; i < strip.numPixels(); i++)
        strip.setPixelColor(i, rgb((256 + sinT(i * 15 + s1) * 2 + 127
                                      + sinT((unsigned int)((i * 15 + fsteps * 16) * 3 / 5))) / 3,
                                   (256 + sinT(i * 23 - s2) * 2
                                   + 127 + sinT((unsigned int)((i * 23 - fsteps * 21) * 2 / 3))) / 3,
                                   (256 + sinT(i * 37 + s3) * 2
                                   + 127 + sinT((unsigned int)((i * 37 - fsteps * 26) * 3 / 2))) / 3));
      break;
    }
    case 6: {
      unsigned int s1 = (unsigned int)(fsteps * 15);
      unsigned int s2 = (unsigned int)(fsteps * 22);
      for (int i = 0; i < strip.numPixels(); i++) {
        int x = (256 + sinT(i * 18 + s1) * 2
               + 127 + sinT(i * 27 - s2)) / 5;
        strip.setPixelColor(i, rainbow(x));
      }
      break;
    }
    case 7: {
      unsigned int s1 = (unsigned int)(fsteps * 15);
      unsigned int s2 = (unsigned int)(fsteps * 22);
      for (int i = 0; i < strip.numPixels(); i++) {
        int x = (256 + sinT(i * 18 + s1) * 2
               + 127 + sinT(i * 27 - s2)) / 5;
        strip.setPixelColor(i, rainbow(x + (unsigned int)(fsteps / 6)));
      }
      break;
    }
    case 8: {
      unsigned int s1 = (unsigned int)(fsteps * 5);
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, rainbow(31 + (sinT(50 * i) >> 2) + s1));
      }
      break;
    }
    case 9:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, rgbTable[(3 * i + steps) % (3 * 32)]);
      }
      break;
    case 10:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, mix(rgb(255, 60, 0), rgb(0, 255, 60), rgb(60, 0, 255), 3 * i + steps));
      }
      break;
    case 11:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, mix(rgbTable[(i + steps) % (3 * 32)], rgbTable[(6 * 32 - 2 * i) % (3 * 32)], 16));
      }
      break;
    case 12: {
      unsigned int s1 = (unsigned int)(4 * fsteps);
      unsigned int s2 = (unsigned int)(3 * fsteps);
      for (int i = 0; i < strip.numPixels(); i++) {
        int v = ((127 + sinT(i * 10 + s1)) >> 1)
                + ((127 + sinT(i * 7 - s2)) >> 2)
                + ((127 + sinT(i * 11 - s1)) >> 2);
        strip.setPixelColor(i, rainbow(v + (steps >> 1)));
      }
      break;
    }
    default:
      mode = 0;
      break;
  }
  strip.show();
  delay(wait);
}
