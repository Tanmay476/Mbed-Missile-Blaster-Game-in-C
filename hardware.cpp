// This header has all the (extern) declarations of the globals.
// "extern" means "this is instantiated somewhere, but here's what the name
// means.
#include "globals.h"

#include "hardware.h"

// We need to actually instantiate all of the globals (i.e. declare them once
// without the extern keyword). That's what this file does!

// Hardware initialization: Instantiate all the things!
uLCD_4DGL uLCD(p9, p10, p11); // LCD Screen (tx, rx, reset)
// SDFileSystem sd(p5, p6, p7, p8, "sd");      // SD Card(mosi, miso, sck, cs)
Serial pc(USBTX, USBRX);       // USB Console (tx, rx)
MMA8452 acc(p28, p27, 100000); // Accelerometer (sda, sdc, rate)

/** 
 * NOTE: For circuits using the NAV_SWITCH part.
 */
Nav_Switch navs(p12, p15, p14, p16, p13);   // Nav Switch p26, p27, p28, p29, p30);
/** 
 * NOTE: For circuits using the JOYSTICK part.
 */
AnalogIn jx(p15);
AnalogIn jy(p16);
DigitalIn jz(p14);

DigitalIn button1(p21); // Pushbuttons (pin)
DigitalIn button2(p22);
DigitalIn button3(p23);
AnalogOut DACout(p18);      // Speaker (pin)
PwmOut speaker(p25);        // PWM Out (pin)
wave_player waver(&DACout); // Wave player (pin)

BusOut mbedleds(LED1, LED2, LED3, LED4);

DigitalOut MBEDLED1(LED1);
DigitalOut MBEDLED2(LED2);
DigitalOut MBEDLED3(LED3);
DigitalOut MBEDLED4(LED4);

// Some hardware also needs to have functions called before it will set up
// properly. Do that here.
int hardware_init() {
  // Crank up the speed
  uLCD.baudrate(3000000);
  pc.baud(115200);

  // Initialize pushbuttons
  button1.mode(PullUp);
  button2.mode(PullUp);
  button3.mode(PullUp);

  // Initialize the joystick
  jz.mode(PullUp);


  return ERROR_NONE;
}

/**
 * TODO:
 * This handles reading inputs from all possible devices - pushbuttons,
 * nav_switch
 * NOTE: If you are using NAV_SWITCH, only implement reading inputs from 'navs', 
 *  and if you are using JOYSTICK, only implement reading inputs from 'jx', 'jy', 'jz'.
 * @return Game inputs
 */
GameInputs read_inputs() {
  GameInputs in;
   

  // 1. Read action buttons for in
  //   Hint: Low voltage means "pressed"     bool ns_up, ns_down, ns_left, ns_right, ns_center;  // NavSwitch readings
   in.b1 = !button1.read();
   in.b2 = !button2.read();
   in.b3 = !button3.read();

  // 2a. Read navigation switch buttons for in. 
    in.ns_left = navs.left();
    in.ns_right = !navs.right();
    in.ns_up = navs.up();
    in.ns_down = !navs.down();

  // 2b. (Alternative) Read joystick values from in.
  //   Hint: Low voltage means "pressed"


  // 3. (Optional) Read Accelerometer values


#ifdef F_DEBUG
  pc.printf("Inputs: B: %d %d %d | A: %f %f %f | N: %d %d %d %d %d | J: %f, %f, %f \r\n", in.b1,
            in.b2, in.b3, in.ax, in.ay, in.az, in.ns_up, in.ns_down, in.ns_left,
            in.ns_right, in.ns_center);
#endif

  wait(0.02); // For simple debouncing
  return in;
}
