#include "SparkFunLSM6DSO.h"
#include "gyro_sensor.h"
#include "buzzer.h"
#include "display.h"
#include "lights.h"
float OFFSET_X, OFFSET_Y, OFFSET_Z;
LSM6DSO mySensor;
int buzzing = 0;
void setupGyro()
{
    Wire.begin();
    delay(10);
    if (mySensor.begin())
        Serial.println("Ready.");
    else
    {
        Serial.println("Could not connect to IMU.");
        Serial.println("Freezing");
    }

    if (mySensor.initialize(BASIC_SETTINGS))
        Serial.println("Loaded Settings.");

    Serial.print("\nAccelerometer offsets:\n");
    OFFSET_X = mySensor.readFloatAccelX() - 0.981; // in this setup, x points up (light on LSM6DSO is down)
    OFFSET_Y = mySensor.readFloatAccelY();
    OFFSET_Z = mySensor.readFloatAccelZ();
}

int fallCheck()
{
    // read each value from accelerometer
    float x = mySensor.readFloatAccelX() - OFFSET_X;
    float y = mySensor.readFloatAccelY() - OFFSET_Y;
    float z = mySensor.readFloatAccelZ() - OFFSET_Z;
    // Serial.print("X:");
    // Serial.println(x);
    // Serial.print("Y:");
    // Serial.println(y);
    // Serial.print("Z:");
    // Serial.println(z);
    // fell over if z or y have acceleration of ~0.981, while other axes have accelration near 0
    if ((abs(x) < 0.2 && abs(y) < 0.2 && abs(z) > 0.8) || (abs(x) < 0.2 && abs(z) < 0.2 && abs(y) > 0.8))
    {
        displayText(0xF800, "TIPPED OVER!");
        Serial.println("ALERT"); // print to terminal
        // activate buzzer
        activateBuzzer();
        blinkLight(RED_PIN, 500);
        buzzing = 1;
    }
    else if (buzzing == 1)
    {
        disableBuzzer(); // turn off buzzer
        displayText(0x07E0, "STATUS: LEVELED");
        buzzing = 0;
    }
    return buzzing;
}

const char *getFellOverString(int fell)
{
    if (fell == 1)
    { // fell
        return "WARNING: fell over";
    }
    else
    {
        return "Pet feeder upright";
    }
}