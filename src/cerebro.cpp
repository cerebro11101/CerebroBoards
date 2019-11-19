/**
 * @file cerebro.cpp
 * @author Aarón Miranda (epsilon11101@gmail.com)
 * @brief 
 * @version 0.0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "cerebro.h"

/**
 * @brief Construct a new Cerebro:: Cerebro object
 * 
 */


Cerebro::Cerebro(){}
/**
 * @brief Destroy the Cerebro:: Cerebro object
 * 
 */
Cerebro::~Cerebro(){}

/**
 * @brief Inicializa todos los componentes de arduino
 * 
 */
void Cerebro::CerebroInit(){
    DDRD = B00110000;        
    DDRB = B00011111;        
    DDRC = B00011100;        
    DDRD = DDRD | B00110000; 
    Serial.begin(9600);
    m_servo.attach(servo);
    Serial.println("inicializado");
}
/**
 * @brief Funcion para reproducir n cantidad de sonidos en n determinado tiempo
 * 
 * @param melody arreglo de sonidos
 * @param soundTime arreglo de tiempos de reproducción del sonido
 * @param size tamaño de arreglo n
 */
void Cerebro::Melody(piano_sound *melody, int *soundTime , int size)
{
    int size_melody = size;
    int size_soundTime = size;
    if (size_melody == size_soundTime)
    {
        for (int thisNote = 0; thisNote < size_melody; thisNote++)
        {
            
            int noteDuration = 1000 / *(soundTime + thisNote);
            tone(buzzer, *(melody + thisNote), noteDuration);
            int pauseBetweenNotes = noteDuration * 1.30;
            delay(pauseBetweenNotes);
            noTone(buzzer);
        }
    }
    else
    {
        Serial.println(F("WARNING: THE SIZE OF THE MELODY ARRAY AND SOUND TIME ARRAY MUST BE THE SAME"));
    }
}
/**
 * @brief Reproduce un solo sonido
 * 
 * @param melody sonido 
 * @param soundTime tiempo de reproducción del sonido
 */
void Cerebro::Melody(piano_sound melody, uint16_t soundTime)
{
    int noteDuration = 1000 / soundTime;
    tone(buzzer, melody, noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzer);
}

/**
 * @brief Detiene el sonido (silenciar)
 * 
 */
void Cerebro::StopMelody(){
    noTone(buzzer);
    DDRB = DDRB & B11101111;
}
/**
 * @brief Mueve el servomotor en un determinado angulo y tiempo
 * 
 * @param angulo Angulo al cual el servomotor debe de moverse
 * @param time Tiempo en el cual el servomotor permanecera en la posición indicada
 */
void Cerebro::AnguloServo(int16_t angulo, uint32_t time)
{
    if (angulo <= 180 && angulo >= 0)
    {
        m_servo.write(angulo);
        delay(time);
    }
    else
    {
        Serial.println(F("WARNING: ANGLES MUST BE IN THE INTERVAL OF  0-180 DEGREES"));
    }
}
/**
 * @brief Mueve el servomotor en angulo de 0 a 180 y de 180 a 0 en un determinado tiempo
 * 
 * @param time tiempo que tardara en mover cada angulo
 */
void Cerebro::ServoRadar(uint32_t time)
{
    for (int16_t i = 0; i <= 180; i++)
    {
        m_servo.write(i);
        delay(time);
        Serial.println(i);
    }
    for (int16_t i = 180; i >= 0; i--)
    {
        m_servo.write(i);
        delay(time);
         Serial.println(i);
    }
    
}
/**
 * @brief Lee el estado actual del boton 
 * 
 * @param Whichbutton seleccion de boton : 'l' para sensor izquierdo 'r' para el sensor derecho
 * @return byte regresa 1 si el boton esta presionado, 0 si el botón no esta presionado
 */
byte Cerebro::ButtonState(char Whichbutton)
{
    byte readState =  (Whichbutton == 'l') ? ((PIND & B00000100)>>2) : ((PIND & B00001000)>>3);
    if (readState == 1 ) {Serial.println(F("BUTTON PRESSED"));}
    else{ Serial.println(F("BUTTON RELEASED"));}
    return readState ;
}

/**
 * @brief Realiza la lectura de los dos botones 
 * 
 * @return byte Retorna el estado de los 2 botones 
 */
byte Cerebro::ButtonState()
{
    byte leftState = PIND & B00000100;
    byte rightState = PIND & B00001000;
    if (leftState && rightState)
    {
        Serial.println(F("LEFT AND RIGHT BUTTON'S PRESSED"));
        return 0;
    }
    else if (leftState && !rightState)
    {
        Serial.println(F("LEFT  BUTTON PRESSED && RIGHT BUTTON RELEASED"));
        return 1;
    }
    else if (!leftState && rightState)
    {
        Serial.println(F("RIGHT  BUTTON PRESSED && LEFT BUTTON RELEASED"));
        return 2;
    }
    else
    {
        Serial.println(F("LEFT AND RIGHT BUTTON'S RELEASED"));
        return 3;
    }
}
/**
 * @brief Realiza la lectura de un sensor de seguidor de linea
 * 
 * @param WhichSensor Selección del sensor 'l' para izquierdo y 'r' para derecho
 * @return byte Regresa 0 si esta en línea blanca y 1 si se encuentra en línea negra
 */
byte Cerebro::lineSensor(char WhichSensor)
{
    byte readState = (WhichSensor == 'l') ? (PIND & B01000000)>>6 : (PIND & B10000000)>>7;
    if (readState == 0 ){ Serial.println(F("WHITE LINE")) ;}
    else {Serial.println(F("BLACK LINE"));}
    return readState;
}
/**
 * @brief Realiza la lectura de los dos sensores de seguidor de linea
 * 
 * @return byte Retorna en el estado en el que se encuentrán los sensores
 */
byte Cerebro::lineSensor()
{
    byte leftState = PIND & B01000000;
    byte rightState = PIND & B10000000;
    if (leftState && rightState)
    {
        Serial.println(F("LEFT AND RIGH SENSORS IN WHITE LINE"));
        return 0;
    }
    else if (leftState && !rightState)
    {
        Serial.println(F("RIGHT SENSOR IN BLACK LINE"));
        return 1;
    }
    else if (!leftState && rightState)
    {
        Serial.println(F("LEFT SENSOR IN BLACK  LINE"));
        return 2;
    }
    else
    {
        Serial.println(F("BOTH SENSORS IN BLACK LINE"));
        return 3;
    }
}

/**
 * @brief Crea un color especifico 
 * 
 * @param r valor de color rojo entre 0-255
 * @param g valor de color verde entre 0-255
 * @param b valor de color azul entre 0-255
 * @param time tiempo de encendido, 0 para no afectar tus algoritmos
 */
void Cerebro::RGBcolor(byte r, byte g, byte b, uint16_t time)
{
    if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
    {
        
        analogWrite(B00001011, r);
        analogWrite(B00001010, g);
        analogWrite(B00001001, b);
        delay(time);
    }
    else
    {
        Serial.println(F("WARNING: THE RGB VALUE MUST BE BETWEEN 0-255"));
    }
}

/**
 * @brief Utiliza colores que definimos para ti Blue,Red, etc... 
 * 
 * @param hex_RGB Nombre de los colores definidos para ti
 * @param time tiempo de encendido, 0 para no afectar tus algoritmos
 */
void Cerebro::RGBcolor(rgb_color hex_RGB, uint16_t time)
{
    analogWrite(B00001011, (hex_RGB & 0xFF0000) >> 16);
    analogWrite(B00001010, (hex_RGB & 0x00FF00) >> 8);
    analogWrite(B00001001, hex_RGB & 0x0000FF);
    delay(time);
    
}
/**
 * @brief Retorna el valor del sensor LDR
 * 
 * @param WhichSensor Selecciona de que sensor quieres tomar la lectura 'l' para izquierdo 'r' para derecho
 * @return float regresa el valor promedio de el LDR seleccionado
 */
float Cerebro::lightSensor(char WhichSensor)
{
    float averange = 0;
    if (WhichSensor == 'l')
    {
        this->Averange(A0, &averange);
    }
    else
    {
        this->Averange(A1, &averange);
    }
    Serial.print(F("LDR VALUE ["));
    Serial.print(WhichSensor);
    Serial.print(F("]:  "));
    Serial.println(averange);
    return averange;
}

/**
 * @brief Mueve un solo motor a la dirección especificada
 * 
 * @param Motor M1 para motor izquierdo M2 para motor derecho
 * @param Direction Dirección a la que quieras que tu motor se mueva Forward, Backward, Stop
 * @param time  tiempo de encendido, 0 para no afectar tus algoritmos
 */
void Cerebro::moveMotor(_motor Motor, motor_direction Direction, uint32_t time)
{
    
    if (Motor == 1)
    {
        if (Direction == 1)
        { //FORWARD
            PORTB = B00010000;
            PORTC = B00000000;
        }
        else if (Direction == 2)
        { //BACKWARD
            PORTB = B00000000;
            PORTC = B00100000;
        }
        else
        { //STOP
            PORTB = B00000000;
            PORTC = B00000000;
        }
    }
    else if (Motor == 2)
    {
        if (Direction == 1)
        { //FORWARD
            PORTB = B00000000;
            PORTC = B00001000;
        }
        else if (Direction == 2)
        { //BACKWARD
            PORTB = B00000000;
            PORTC = B00010000;
        }
        else
        { //STOP
            PORTB = B00000000;
            PORTC = B00000000;
        }
    }
    else
    {
        PORTB = B00000001;
        PORTC = B00000000;
        Serial.println(F("MOTOR DOESNT EXISTS :C "));
    }
    delay(time);
}
/**
 * @brief Mueve los dos motores de Cerebro a la dirección especificada
 * 
 * @param Direction Dirección a la que quieras que tu motor se mueva Forward, Backward, Left, Right , Stop
 * @param time tiempo de encendido, 0 para no afectar tus algoritmos
 */
void Cerebro::moveTank(motor_direction Direction,uint32_t time)
{
    switch (Direction)
    {
        case 1: // forward
            PORTB = B00010000;
            PORTC = B00001000;
            break;
        case 2: //backward
            PORTB = B00000000;
            PORTC = B00110000;
            break;
        case 3: //stop
            PORTB = 0x01;
            PORTC = 0X00;
            break;
        case 4: //left
            PORTB = B00010000;
            PORTC = B00010000;
            break;
        case 5://right
            PORTB = B00000000;
            PORTC = B00101000;
            break;
            
        default:
            Serial.println(F("DIRECTION DOESNT EXISTS :C "));
            PORTB = 0x01;
            PORTC = 0X00;
            break;
    }
    delay(time);
}



/**
 * @brief Realiza un muestreo de 10 al sensor especificado
 * 
 * @param AX Sensor al cual se realizaran las muestras
 * @param avergange promedio del sensor
 */
void Cerebro::Averange(byte AX, float *avergange)
{
    uint32_t ADCValue=0;
    *avergange = 0;
    for (byte i = 0; i < 10; i++)
    { 
        *avergange += analogRead(AX);
    }
    *avergange = *avergange / 10;
}
/**
 * @brief Calcula la distancia del sensor ultrasonico
 * 
 * @return uint16_t Retorna el valor de la distancia calculada en cm rango de 3-200 cm
 */
uint16_t Cerebro::getDistance(){

  
     PORTB = PORTB & B1111110;
     delayMicroseconds(2);
     PORTB = PORTB | B0000001;
     delayMicroseconds(10);
     PORTB = PORTB & B1111110;
     int tiempo = pulseIn(echo,1);
     int distancia = tiempo / 2.0 * 0.0343;
     delayMicroseconds(50);
     if (distancia <= 0 || distancia >= 400) {
        return 0 ;
    } else {

     Serial.print("DISTANCIA: ");
     Serial.println(distancia);
        return distancia;
    }

}



