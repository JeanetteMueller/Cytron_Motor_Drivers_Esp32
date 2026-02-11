#ifndef CYTRON_MOTOR_DRIVER_H
#define CYTRON_MOTOR_DRIVER_H

#include <Arduino.h>
#include <stdint.h>

#if defined(ARDUINO_ARCH_ESP32)

enum CytronMD_Motor_Mode
{
  PWM_DIR,
  PWM_PWM,
};

class CytronMD
{
public:
  CytronMD(CytronMD_Motor_Mode mode, uint8_t pin1, uint8_t pin2, uint32_t freq = 5000, uint8_t resolution = 8);
  void setSpeed(int32_t speed);

private:
  static uint8_t nextChannel; // Statischer Zähler
  void setChannelWithDuty(uint8_t channel, uint32_t duty);

protected:
  CytronMD_Motor_Mode _mode;

  uint8_t _pin1;
  uint8_t _pin2;
  uint8_t _channel;
  int32_t _maxSpeed;
};

#else

// only compatible with ESP32

#endif

#endif
