#include "CytronMotorDriverEsp32.h"
#include <math.h>

CytronMD::CytronMD(CytronMD_MOTOR_MODE mode, uint8_t pin1, uint8_t pin2, uint8_t channel, uint32_t freq, uint8_t resolution)
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
            ledcSetup(channel, freq, resolution);
            ledcAttachPin(_pin1, channel);
            ledcWrite(channel, 0);
            digitalWrite(_pin2, LOW);
          break;

      case PWM_PWM:
        ledcSetup(channel, freq, resolution);
        ledcSetup(channel * 10, freq, resolution);

        ledcAttachPin(_pin1, channel);
        ledcAttachPin(_pin2, channel * 10);

        ledcWrite(channel, 0);
        ledcWrite(channel * 10, 0);
      
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
              ledcWrite(_channel, setSpeed);
              ledcWrite(_channel * 10, 0);
            }
            else
            {
              ledcWrite(_channel, 0);
              ledcWrite(_channel * 10, setSpeed);
            }
            break;
      }
}