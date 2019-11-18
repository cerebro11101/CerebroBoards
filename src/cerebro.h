#ifndef Cerebro_h
#define Cerebro_h

#include <Arduino.h>
#include <Servo.h>

enum piano_sound{
  _B0  =31,
  _C1  =33,
  _CS1 =35,
  _D1  =37,
  _DS1 =39,
  _E1  =41,
  _F1  =44,
  _FS1 =46,
  _G1  =49,
  _GS1 =52,
  _A1  =55,
  _AS1 =58,
  _B1  =62,
  _C2  =65,
  _CS2 =69,
  _D2  =73,
  _DS2 =78,
  _E2  =82,
  _F2  =87,
  _FS2 =93,
  _G2  =98,
  _GS2 =104,
  _A2  =110,
  _AS2 =117,
  _B2  =123,
  _C3  =131,
  _CS3 =139,
  _D3  =147,
  _DS3 =156,
  _E3  =165,
  _F3  =175,
  _FS3 =185,
  _G3  =196,
  _GS3 =208,
  _A3  =220,
  _AS3 =233,
  _B3  =247,
  _C4  =262,
  _CS4 =277,
  _D4  =294,
  _DS4 =311,
  _E4  =330,
  _F4  =349,
  _FS4 =370,
  _G4  =392,
  _GS4 =415,
  _A4  =440,
  _AS4 =466,
  _B4  =494,
  _C5  =523,
  _CS5 =554,
  _D5  =587,
  _DS5 =622,
  _E5  =659,
  _F5  =698,
  _FS5 =740,
  _G5  =784,
  _GS5 =831,
  _A5  =880,
  _AS5 =932,
  _B5  =988,
  _C6  =1047,
  _CS6 =1109,
  _D6  =1175,
  _DS6 =1245,
  _E6  =1319,
  _F6  =1397,
  _FS6 =1480,
  _G6  =1568,
  _GS6 =1661,
  _A6  =1760,
  _AS6 =1865,
  _B6  =1976,
  _C7  =2093,
  _CS7 =2217,
  _D7  =2349,
  _DS7 =2489,
  _E7  =2637,
  _F7  =2794,
  _FS7 =2960,
  _G7  =3136,
  _GS7 =3322,
  _A7  =3520,
  _AS7 =3729,
  _B7  =3951,
  _C8  =4186,
  _CS8 =4435,
  _D8  =4699,
  _DS8 =4978
};

enum rgb_color{
    Red = 0xFF0000,
    Blue = 0x0000FF,
    Green = 0x00FF00,
    Orange = 0xFF7D00,
    Yellow = 0xFFFF00,
    SpringGreen = 0x7DFF00,
    Turquoise = 0x00FF7D,
    Cyan = 0x00FFFF,
    Ocean = 0x007DFF,
    Violet = 0X7F00FF,
    Magenta = 0xFF00FF,
    Raspberry = 0xFF007D
};
enum motor_direction{
    Forward = 1,
    Backward = 2,
    Stop = 3,
    Left = 4,
    Right = 5
    
};
enum _motor{
    M1 = 1,
    M2 = 2
};

class Cerebro {
public:
 
    Cerebro();
    ~Cerebro();

    void CerebroInit();
    void Melody(piano_sound *melody, int *soundTime , int size);
    void Melody(piano_sound melody, uint16_t soundTime);
    void StopMelody();
    void AnguloServo(int angulo, uint32_t time);
    void ServoRadar(uint32_t time);
    byte ButtonState(char Whichbutton);
    byte ButtonState();
    byte lineSensor(char WhichSensor);
    byte lineSensor();
    void RGBcolor(byte r, byte g, byte b, uint16_t time);
    void RGBcolor(rgb_color hex_RGB, uint16_t time);
    float lightSensor(char WhichSensor);
    void moveMotor(_motor Motor, motor_direction Direction,uint32_t time);
    void moveTank(motor_direction Direction,uint32_t time);
    uint16_t getDistance();
    
 
private:
    #define buzzer 4
    #define servo 5
    #define trig 8
    #define echo 13
    Servo m_servo;
    void Averange(byte AX, float *avergange);
    
};

#endif //_Cerebro_H_


