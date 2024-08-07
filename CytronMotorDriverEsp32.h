#ifndef CYTRON_MOTOR_DRIVER_H
#define CYTRON_MOTOR_DRIVER_H

#include <Arduino.h>
#include <stdint.h>

#if defined(ARDUINO_ARCH_ESP32)

enum CytronMD_MOTOR_MODE {
  PWM_DIR,
  PWM_PWM,
};

class CytronMD
{
  public:
    CytronMD(CytronMD_MOTOR_MODE mode, uint8_t pin1, uint8_t pin2, uint8_t channel = 0, uint32_t freq = 0, uint8_t resolution = 0);
    void setSpeed(int32_t speed);
    
  protected:
    CytronMD_MOTOR_MODE _mode;
    
  	uint8_t _pin1;
    uint8_t _pin2;
    uint8_t _channel;
    int32_t _maxSpeed;
};

#else

//only compatible with ESP32

#endif

#endif
