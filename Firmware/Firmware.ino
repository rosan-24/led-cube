/*
  4x4x4 LED Cube "DIY Active" - direct wiring on an ESP32 DEVKITV1 (30-pin)
  Wiring: see 4x4x4led_direct_wiring.png  (no resistors, no driver chips)

  Layers   L0..L3 : GPIO 13, 14, 26, 27   HIGH = layer on (pin supplies current)
  Columns  C0..C15: GPIO 4,16,17,18,19,21,22,23,25,32,33,0,2,5,12,15
                    LOW = column on (pin sinks current)

  Column index c = 4*x + y (x, y = 0..3), same numbering as the original sketch.

  There is no resistor in the LED circuit, so the GPIO drive strength limits
  the current. Each pin is set to about 20 mA, so the code keeps the cube safe:
    - only one layer is on at a time (the layers are scanned in turn)
    - at most MAX_PER_LAYER LEDs are lit in any layer at the same time
  Before running the full cube, check the current of one layer with a
  multimeter and change DRIVE if needed.

  Note: GPIO 2 also drives the onboard LED, which glows faintly while C12 is off.
*/

#include "driver/gpio.h"

// ---------- wiring ----------
const int LAYER_PIN[4] = {27, 26, 14, 13};
const int COL_PIN[16]  = {4, 16, 17, 18, 19, 21, 22, 23, 25, 32, 33, 0, 2, 5, 12, 15};

// ---------- limits and timing ----------
const int MAX_PER_LAYER = 4;                        // LEDs allowed on per layer at once
const unsigned int ON_US = 1500;                    // time each layer stays on per scan (us)
const gpio_drive_cap_t DRIVE = GPIO_DRIVE_CAP_2;    // about 20 mA per pin
const unsigned long SPEED = 250;                    // base timing (was "time")

// ---------- LED state ----------
// frame[l] bit c = 1 means the LED in layer l, column c is on
uint16_t frame[4] = {0, 0, 0, 0};

#define LED_BIT(c)   ((uint16_t)1 << (c))
#define CENTER_MASK  (LED_BIT(5) | LED_BIT(6) | LED_BIT(9) | LED_BIT(10))   // 2x2 in the middle
#define CORNER_MASK  (LED_BIT(0) | LED_BIT(3) | LED_BIT(12) | LED_BIT(15))  // the 4 corners

void clearCube()
{
  for (int l = 0; l < 4; l++) frame[l] = 0;
}

// column index for position (x, y)
int colIndex(int x, int y)
{
  return 4 * x + y;
}

// 2x2 square of columns starting at (x0, y0)
uint16_t square2x2(int x0, int y0)
{
  return LED_BIT(colIndex(x0, y0)) | LED_BIT(colIndex(x0, y0 + 1))
       | LED_BIT(colIndex(x0 + 1, y0)) | LED_BIT(colIndex(x0 + 1, y0 + 1));
}

// mask with n different random columns set
uint16_t randomMask(int n)
{
  uint16_t m = 0;
  int count = 0;
  while (count < n) {
    int c = random(16);
    if (!(m & LED_BIT(c))) {
      m |= LED_BIT(c);
      count++;
    }
  }
  return m;
}

// Safety limit: keep at most MAX_PER_LAYER LEDs on in each layer
void limitFrame()
{
  for (int l = 0; l < 4; l++) {
    uint16_t keep = 0;
    int n = 0;
    for (int c = 0; c < 16 && n < MAX_PER_LAYER; c++) {
      if (frame[l] & LED_BIT(c)) {
        keep |= LED_BIT(c);
        n++;
      }
    }
    frame[l] = keep;
  }
}

// One refresh of the whole cube: each layer on for ON_US, in turn
void scanOnce()
{
  for (int l = 0; l < 4; l++) {
    // set the columns while this layer is still off (avoids ghosting)
    for (int c = 0; c < 16; c++) {
      digitalWrite(COL_PIN[c], (frame[l] & LED_BIT(c)) ? LOW : HIGH);
    }
    digitalWrite(LAYER_PIN[l], HIGH);
    delayMicroseconds(ON_US);
    digitalWrite(LAYER_PIN[l], LOW);
  }
}

// Wait for ms milliseconds while keeping the cube lit (replaces delay())
void hold(unsigned long ms)
{
  limitFrame();
  unsigned long end = millis() + ms;
  while (millis() < end) {
    scanOnce();
  }
}

void setup()
{
  for (int l = 0; l < 4; l++) {
    pinMode(LAYER_PIN[l], OUTPUT);
    digitalWrite(LAYER_PIN[l], LOW);
    gpio_set_drive_capability((gpio_num_t)LAYER_PIN[l], DRIVE);
  }
  for (int c = 0; c < 16; c++) {
    pinMode(COL_PIN[c], OUTPUT);
    digitalWrite(COL_PIN[c], HIGH);          // HIGH = column off
    gpio_set_drive_capability((gpio_num_t)COL_PIN[c], DRIVE);
  }
  randomSeed(analogRead(34));                // GPIO 34 is left unconnected
}

// ---------- animations (same order as the original loop) ----------

// random LEDs, more of them each round (replaces flickerOn)
void flickerOn()
{
  for (int n = 1; n <= MAX_PER_LAYER; n++) {
    for (int k = 0; k < 4; k++) {
      for (int l = 0; l < 4; l++) frame[l] = randomMask(n);
      hold(SPEED / 2);
      clearCube();
      hold(SPEED / 2);
    }
  }
}

// the 4 corners pulse in every layer (replaces turnEverythingOn)
void cornersPulse()
{
  for (int k = 0; k < 4; k++) {
    for (int l = 0; l < 4; l++) frame[l] = CORNER_MASK;
    hold(SPEED / 2);
    clearCube();
    hold(SPEED / 2);
  }
}

// a 2x2 block rises and falls through the layers (replaces layer up and down)
void layerUpDown()
{
  for (int rep = 0; rep < 3; rep++) {
    for (int l = 0; l < 4; l++) {
      clearCube();
      frame[l] = square2x2(0, 0);
      hold(SPEED / 2);
    }
    for (int l = 2; l >= 0; l--) {
      clearCube();
      frame[l] = square2x2(0, 0);
      hold(SPEED / 2);
    }
  }
  clearCube();
}

// centre pillar stomps on all layers together (replaces layerstomp)
void layerStomp()
{
  for (int k = 0; k < 5; k++) {
    for (int l = 0; l < 4; l++) frame[l] = CENTER_MASK;
    hold(SPEED / 5);
    clearCube();
    hold(SPEED / 5);
  }
}

// one column line (through all layers) sweeps across the cube (replaces column sideways)
void columnSideways()
{
  for (int rep = 0; rep < 3; rep++) {
    for (int c = 0; c < 16; c++) {
      for (int l = 0; l < 4; l++) frame[l] = LED_BIT(c);
      hold(SPEED / 4);
    }
  }
  clearCube();
}

// the corners drop down through the layers (replaces around edge down)
void cornersDown()
{
  for (int rep = 0; rep < 3; rep++) {
    for (int l = 3; l >= 0; l--) {
      clearCube();
      frame[l] = CORNER_MASK;
      hold(SPEED / 2);
    }
  }
  clearCube();
}

// random LEDs, changing every 10 ms (replaces randomflicker)
void randomFlicker()
{
  for (int i = 0; i < 750; i++) {
    for (int l = 0; l < 4; l++) frame[l] = randomMask(random(0, MAX_PER_LAYER + 1));
    hold(10);
  }
  clearCube();
}

// drops fall from the top layer to the bottom (replaces random rain)
void randomRain()
{
  for (int i = 0; i < 25; i++) {
    int c = random(16);
    for (int l = 3; l >= 0; l--) {
      clearCube();
      frame[l] = LED_BIT(c);
      hold(SPEED / 4);
    }
  }
  clearCube();
}

// 2x2 squares walk around the floor, on the upper pair of layers, then the lower pair
void diagonalSquares()
{
  const int corner[4][2] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
  for (int rep = 0; rep < 3; rep++) {
    for (int p = 0; p < 4; p++) {
      uint16_t m = square2x2(corner[p][0], corner[p][1]);
      clearCube();
      frame[2] = m;
      frame[3] = m;
      hold(SPEED + 100);
      clearCube();
      frame[0] = m;
      frame[1] = m;
      hold(SPEED + 100);
    }
  }
  clearCube();
}

// every LED once, one at a time, layer by layer (replaces go through all LEDs)
void walkAllLeds()
{
  for (int rep = 0; rep < 2; rep++) {
    for (int n = 0; n < 64; n++) {
      clearCube();
      frame[n / 16] = LED_BIT(n % 16);
      hold(15);
    }
  }
  clearCube();
}

// four-LED spokes turn, one layer at a time (same spokes as the original)
void propeller()
{
  const uint16_t spokes[6] = {
    LED_BIT(0) | LED_BIT(5)  | LED_BIT(10) | LED_BIT(15),
    LED_BIT(4) | LED_BIT(5)  | LED_BIT(10) | LED_BIT(11),
    LED_BIT(6) | LED_BIT(7)  | LED_BIT(8)  | LED_BIT(9),
    LED_BIT(3) | LED_BIT(6)  | LED_BIT(9)  | LED_BIT(12),
    LED_BIT(2) | LED_BIT(6)  | LED_BIT(9)  | LED_BIT(13),
    LED_BIT(1) | LED_BIT(5)  | LED_BIT(10) | LED_BIT(14)
  };
  for (int l = 3; l >= 0; l--) {
    for (int rep = 0; rep < 2; rep++) {
      for (int i = 0; i < 6; i++) {
        clearCube();
        frame[l] = spokes[i];
        hold(SPEED / 5);
      }
    }
  }
  clearCube();
}

// a column walks the spiral through all four layers, in then out
void spiral()
{
  const int spiralIn[16]  = {0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 5, 6, 10, 9};
  const int spiralOut[16] = {9, 10, 6, 5, 4, 8, 12, 13, 14, 15, 11, 7, 3, 2, 1, 0};
  for (int rep = 0; rep < 2; rep++) {
    for (int i = 0; i < 16; i++) {
      for (int l = 0; l < 4; l++) frame[l] = LED_BIT(spiralIn[i]);
      hold(SPEED / 4);
    }
    for (int i = 0; i < 16; i++) {
      for (int l = 0; l < 4; l++) frame[l] = LED_BIT(spiralOut[i]);
      hold(SPEED / 4);
    }
  }
  clearCube();
}

// random LEDs, fewer each round (replaces flickerOff)
void flickerOff()
{
  for (int n = MAX_PER_LAYER; n >= 1; n--) {
    for (int k = 0; k < 4; k++) {
      for (int l = 0; l < 4; l++) frame[l] = randomMask(n);
      hold(SPEED / 2);
      clearCube();
      hold(SPEED / 2);
    }
  }
  clearCube();
}

void loop()
{
  clearCube();
  flickerOn();
  cornersPulse();
  hold(SPEED);
  layerUpDown();
  layerStomp();
  columnSideways();
  hold(SPEED);
  cornersDown();
  randomFlicker();
  randomRain();
  diagonalSquares();
  walkAllLeds();
  propeller();
  spiral();
  flickerOff();
  clearCube();
  hold(2000);
}