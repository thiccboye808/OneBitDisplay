// ssd1306 oled test
// by thiccboye808/kerochan
// uses onebitbisplays soft i2c.
// bounces text on the screen

#include <OneBitDisplay.h>

// global defs
#define GND_PIN 40
#define VCC_PIN 38
#define SCL_PIN 36
#define SDA_PIN 34
#define RESET_PIN -1
#define OLED_ADDR -1
#define FLIP180 0
#define INVERT 0
#define USE_HW_I2C 0
#define OLED_TYPE OLED_128x64
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define BIT_SPEED 1000000L
#define BAUD_RATE 9600
#define TEXT_NUM 5

// onebitdisplay vars
static uint8_t backbuff[ 1024 ];
OBDISP obd;

// text struct definition
typedef struct Text
{
  char* text;
  uint8_t x;
  uint8_t vx;
  uint8_t y;
  uint8_t vy;
} Text;

// returns a text object
Text initText( char* text = ":3",
  uint8_t x = 0,
  uint8_t y = 0,
  uint8_t vx = 8,
  uint8_t vy = 1 )
{
  Text txt;
  txt.text = (char*)text;
  txt.x = x;
  txt.y = y;
  txt.vx = vx;
  txt.vy = vy;
  return txt; 
}

// text variables
Text def;
Text pp;
Text fuck;
Text shit;
Text hi;

// logic and display code for each frame
void textFrame( Text* txt )
{
  txt->x += txt->vx;
  if( txt->x <= 0 || txt->x >= OLED_WIDTH - ( strlen( txt->text ) * 8 ) )
  {
    txt->vx = -1 * txt->vx;
  }
  txt->y += txt->vy;
  if( txt->y <= 0 || txt->y >= ( OLED_HEIGHT / 8 ) - 1 )
  {
    txt->vy = -1 * txt->vy;
  }
  obdWriteString( &obd, 0, txt->x, txt->y, txt->text, FONT_8x8, 0, 1 );
  return;
}

void setup() 
{
  // serial init
  Serial.begin( BAUD_RATE );

  // power pin init
  pinMode( GND_PIN, OUTPUT );
  pinMode( VCC_PIN, OUTPUT );
  digitalWrite( GND_PIN, LOW );
  digitalWrite( VCC_PIN, HIGH );

  // bouncing text init
  def = initText(),
  pp = initText( (char*)"pp", 8 * 6, 0 );
  fuck = initText( (char*)"fuck", 8 * 6, 6 );
  shit = initText( (char*)"shit", 0, 6 );
  hi = initText( (char*)"hi cj", 8 * 4, 4 );
  // oled init
  int rc;
  rc = obdI2CInit( &obd, OLED_TYPE, OLED_ADDR, FLIP180, INVERT, USE_HW_I2C, SDA_PIN, SCL_PIN, RESET_PIN, BIT_SPEED );
  if( rc == OLED_NOT_FOUND )
  {
    Serial.println( "oled not found ;-;" );
    for( ;; ) {}
  }
  obdSetBackBuffer( &obd, backbuff );
  delay( 2000 );
}

void loop() 
{
  obdFill( &obd, 0, 1 );
  textFrame( &def );
  textFrame( &pp );
  textFrame( &fuck );
  textFrame( &shit );
  textFrame( &hi );
  obdDumpBuffer( &obd, backbuff );
}
