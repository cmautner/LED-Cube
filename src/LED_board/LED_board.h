const uint8_t LED_SIZE = NUM_COLORS;
const uint8_t NUM_LEDS = 8;
const uint8_t ROW_SIZE = NUM_LEDS * LED_SIZE;
const uint8_t ROW_BYTES = NUM_LEDS * LED_SIZE / 2; // 4 bits/color
const uint8_t NUM_ROWS = 8;
const uint8_t PANEL_SIZE = NUM_ROWS * ROW_SIZE;
const uint8_t NUM_PANELS = 1;
const uint8_t NUM_REFRESHES = 16;
const uint8_t DDRC_INIT = 0x37; // PC0-2, 4-5 as outputs. All others as inputs
const uint8_t DDRB_INIT = 0x23; // PB0-1,5 as outputs. All others as inputs

const int BLANK_ = 8;  // Enable for LEDs, active low
const int LATCH = 9;

