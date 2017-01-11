// initialize the Orbit Booster pack
void deviceInit() {
  SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_4);
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOC );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF );
  
  GPIOPadConfigSet(SWTPort, SWT1 | SWT2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(BTN1Port, BTN1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(BTN2Port, BTN2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(LED1Port, LED1, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED2Port, LED2, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED3Port, LED3, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED4Port, LED4, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);

  GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);
  GPIOPinTypeGPIOInput(BTN1Port, BTN1);
  GPIOPinTypeGPIOInput(BTN2Port, BTN2);
  GPIOPinTypeGPIOOutput(LED1Port, LED1);
  GPIOPinTypeGPIOOutput(LED2Port, LED2);
  GPIOPinTypeGPIOOutput(LED3Port, LED3);
  GPIOPinTypeGPIOOutput(LED4Port, LED4);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
  GPIOPinTypeADC(AINPort, AIN);

  ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
  ADCSequenceEnable(ADC0_BASE, 0);

  OrbitOledInit();
}

//========================================
// Wire used to connect accelerometer

static TwoWire wire(0);

void wireInit() {
    wire.begin();
}

void wireWriteByte(int address, uint8_t value) {
    wire.beginTransmission(address);
    wire.write(value);
    wire.endTransmission();
}

void wireWriteRegister(int address, uint8_t reg, uint8_t value) {
    wire.beginTransmission(address);
    wire.write(reg);
    wire.write(value);
    wire.endTransmission();
}
 
void wireRequestArray(uint8_t address, uint32_t* buffer, uint8_t amount) {
    wire.requestFrom(address, amount);
    do {
        while(!wire.available());
            *(buffer++) = wire.read();
    } while(--amount > 0);
}
//=====================================
//Accelerometer

static uint8_t const sensorAccelerometer = 0x1D;
static uint32_t const motionThreshold = 8;
static float motionAccumulator = 0;

void acceleroInit() {
    wireWriteRegister(sensorAccelerometer, 0x31, 1);
    wireWriteRegister(sensorAccelerometer, 0x2D, 1 << 3);
}

void checkForMotion() {
    size_t const dataLength = 6;
    uint32_t data[dataLength] = { 0 };
    wireWriteByte(sensorAccelerometer, 0x32);
    wireRequestArray(sensorAccelerometer, data, dataLength);
    // get motion changes in y axis
    uint16_t yChange = (data[3] << 8) | data[2];
    motionAccumulator = *(int16_t*)(&yChange);
}

int getMotionDir() {
    if(abs(motionAccumulator) < motionThreshold) {
        return 0;
    }
    if(motionAccumulator > 0) {
        return 1;
    }
    return -1;
}
//======================================
// Led lights
void flashLED(int pin, int n) {
    bool ledOn = false;
    for(int i = 0; i < n; i++) {
        if(ledOn) {
            digitalWrite(pin, LOW);
        }
        else {
            digitalWrite(pin, HIGH);
        }
        ledOn = !ledOn;
        delay(LED_TOGGLE_RATE);
    }
    digitalWrite(pin, LOW); // ensure the LED is off
}
//=====================================
// EEPROM storage device
void storageInit() {
    EEPROMInit();
}
void updateValue(uint32_t value, uint32_t address) {
    EEPROMProgram(&value, address, 4);
}

uint32_t getValue(uint32_t address){
    uint32_t data;
    EEPROMRead(&data, address, 4);
    return data;
}
