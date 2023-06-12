#include <SoftwareSerial.h>

#define USB_BAUDRATE (115200)
#define RS232_BAUDRATE (9600)

int RXPin = 6;
int TXPin = 7;

SoftwareSerial rs232(RXPin, TXPin);

String processData;
int stage = 0;
bool printed = false;
bool executed = false;

String sAzimuth;
String sElevation;
String sMsgCount;

void setup()
{
    Serial.begin(USB_BAUDRATE);
    rs232.begin(RS232_BAUDRATE);

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
