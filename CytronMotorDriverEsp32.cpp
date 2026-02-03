#include "CytronMotorDriverEsp32.h"
#include <math.h>

uint8_t CytronMD::nextChannel = 0;

CytronMD::CytronMD(CytronMD_Motor_Mode mode, uint8_t pin1, uint8_t pin2, uint32_t freq, uint8_t resolution)
{
  _mode = mode;
  _pin1 = pin1;
  _pin2 = pin2;
  _channel = nextChannel;  // set automatically
  _maxSpeed = (1 << resolution) - 1;

  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);

  switch (_mode)
  {
  case PWM_DIR:
    ledcAttachChannel(_pin1, freq, resolution, _channel);
    ledcWriteChannel(_channel, 0);
    digitalWrite(_pin2, LOW);
    nextChannel++; // increment to next channel 
    break;

  case PWM_PWM:

    ledcAttachChannel(_pin1, freq, resolution, _channel);
    ledcAttachChannel(_pin2, freq, resolution, _channel + 1);

    ledcWriteChannel(_channel, 0);
    ledcWriteChannel(_channel + 1, 0);
    nextChannel += 2;  // increment 2 channels
    break;
  }

  Serial.print("   CytronMD::init done");
}

void CytronMD::setSpeed(int32_t speed)
{
  // Make sure the speed is within the limit.
  speed = constrain(speed, -_maxSpeed, _maxSpeed);

  // Make sure the speed is within the limit.
  uint32_t setSpeed = abs(speed);
  setSpeed = constrain(setSpeed, 0, _maxSpeed);

  // Set the speed and direction.
  switch (_mode)
  {
  case PWM_DIR:
    ledcWriteChannel(_channel, setSpeed);

    if (speed >= 0)
    {
      digitalWrite(_pin2, LOW);
    }
    else
    {
      digitalWrite(_pin2, HIGH);
    }
    break;

  case PWM_PWM:
    if (speed >= 0)
    {
      ledcWriteChannel(_channel, setSpeed);
      ledcWriteChannel(_channel + 1, 0);
    }
    else
    {
      ledcWriteChannel(_channel, 0);
      ledcWriteChannel(_channel + 1, setSpeed);
    }
    break;
  }
}