#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "control.h"


#define SWITCH_PIN GPIO_PIN_7
#define SWITCH_PORT GPIO_PORTA_BASE


static bool switchState;
static bool butflag = 0;


void initSwitch(void) {
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOInput (SWITCH_PORT, SWITCH_PIN);
    GPIOPadConfigSet (SWITCH_PORT, SWITCH_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
    GPIODirModeSet(SWITCH_PORT, SWITCH_PIN, GPIO_DIR_MODE_IN);
}


void updateSwitch(void) {
    switchState = GPIOPinRead(SWITCH_PORT, SWITCH_PIN);
}


bool checkSwitch(void) {
    if (switchState != 0 && butflag == 0) { // Switch is up
        butflag = 1;
        return true;
    } else if (switchState == 0 && butflag == 1) { // Switch is down
        butflag = 0;
        return false;
    } else {
        return false;
    }
}



