#include <Arduino.h>
#include <SoftwareSerial.h>
#include "BasicStepperDriver.h"

#define USB_BAUDRATE (115200)
#define RS232_BAUDRATE (9600)

#define MOTOR_STEPS 200
#define RPM 20
#define MICROSTEPS 2

int RXPin = 6;
int TXPin = 7;

int DIRPin = 2;
int STEPPin = 3;
int MSAPin = 4;

SoftwareSerial rs232(RXPin, TXPin);

BasicStepperDriver stepper(MOTOR_STEPS, DIRPin, STEPPin, MSAPin);

String processData;
int stage = 0;
bool printed = false;
bool executed = false;

String sAzimuth;
String sElevation;
String sMsgCount;

bool azIsFirstTime = true;
int currentAz;
int prevAz;

void setup()
{
    Serial.begin(USB_BAUDRATE);
    rs232.begin(RS232_BAUDRATE);

    stepper.begin(RPM, MICROSTEPS);
    stepper.setMicrostep(2);

    Serial.println("Monitoring RS-232 Serial Connection...");
}

void loop()
{
    if (rs232.available())
    {
        if (stage == 5 & printed == false)
        {
            Serial.print("Azimuth: ");
            Serial.println(sAzimuth);
            Serial.print("Elevation: ");
            Serial.println(sElevation);
            Serial.print("Message Count: ");
            Serial.println(sMsgCount);
            printed = true;
        }

        char received = rs232.read();
        processData += received;

        if (received == '\n')
        {
            executed = false;
            processData = processData.substring(0, processData.length() - 2);

            if (processData == "STARTMSG" && executed == false)
            {
                Serial.println("START RECEIVED");
                stage = 2;
                executed = true;
                printed = false;
            }

            if (processData == "ENDMSG" && executed == false)
            {
                Serial.println("END RECEIVED");
                Serial.println();
                stage = 1;
                executed = true;
            }

            if (stage == 2 && executed == false)
            {
                sAzimuth = processData;

                currentAz = sAzimuth.toInt();
                Serial.print("Current az (int): ");
                Serial.println(currentAz);

                if (azIsFirstTime == true)
                {
                    stepper.rotate(currentAz);
                    azIsFirstTime = false;
                } else
                {
                    if (currentAz > prevAz)
                    {
                        int diff = currentAz - prevAz;
                        stepper.rotate(diff);
                        Serial.println("ROTATED RIGHT");
                    } else if (prevAz > currentAz)
                    {
                        int diff = prevAz - currentAz;
                        diff *= -1;
                        stepper.rotate(diff);
                        Serial.println("ROTATED LEFT");
                        Serial.print("DIFF: ");
                        Serial.println(diff);
                    }
                }

                prevAz = currentAz;

                stage = 3;
                executed = true;
            }

            if (stage == 3 && executed == false)
            {
                sElevation = processData;
                stage = 4;
                executed = true;
            }

            if (stage == 4 && executed == false)
            {
                sMsgCount = processData;
                stage = 5;
                executed = true;
            }

            processData = "";
        }
    }
}
