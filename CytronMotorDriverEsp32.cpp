#include "CytronMotorDriverEsp32.h"
#include <math.h>

CytronMD::CytronMD(CytronMD_Motor_Mode mode, uint8_t pin1, uint8_t pin2, uint8_t channel, uint32_t freq, uint8_t resolution)
{
      _mode = mode;
      _pin1 = pin1;
      _pin2 = pin2;
      _channel = channel;
      _maxSpeed = (pow(2, resolution) - 1);

      pinMode(_pin1, OUTPUT);
      pinMode(_pin2, OUTPUT);

      switch (_mode)
      {
        case PWM_DIR:
            ledcAttachChannel(_pin1, freq, resolution, channel);
            ledcWriteChannel(channel, 0);
            digitalWrite(_pin2, LOW);
          break;

      case PWM_PWM:

        ledcAttachChannel(_pin1, freq, resolution, channel);
        ledcAttachChannel(_pin2, freq, resolution, channel * 10);

        ledcWriteChannel(channel, 0);
        ledcWriteChannel(channel * 10, 0);
      
        break;
      }
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
            ledcWrite(_channel, setSpeed);

            if (speed >= 0) {
              digitalWrite(_pin2, LOW);
            }else {
              digitalWrite(_pin2, HIGH);
            }
          break;

          case PWM_PWM:
            if (speed >= 0)
            {
              ledcWriteChannel(_channel, setSpeed);
              ledcWriteChannel(_channel * 10, 0);
            }
            else
            {
              ledcWriteChannel(_channel, 0);
              ledcWriteChannel(_channel * 10, setSpeed);
            }
            break;
      }
}