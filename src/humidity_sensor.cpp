#include "humidity_sensor.h"
DHT20 DHT; // humidity sensor
void setupHumiditySensor()
{
    // Setup humidity sensor
    DHT.begin(); //  ESP32 default pins 21 22

    Serial.begin(9600);
    Serial.println(__FILE__);
    Serial.print("DHT20 LIBRARY VERSION: ");
    Serial.println(DHT20_LIB_VERSION);
    Serial.println();

    delay(1000);
}
void humidityCheck()
{
    DHT.read();
    // Get humidity reading
    float cur_humidity = DHT.getHumidity();
    // Print to terminal
    Serial.print("Humidity (%): ");
    Serial.println(cur_humidity);
    // Compare with humidity thresholds
    if (cur_humidity > HUMIDITY_HIGH_THRESHOLD)
    {
        // Alert user of high humidity issue
        // Suggest replacing food
        // These should be changed to be on TTGO menu/ & display
        Serial.println("The humidity in the reservoir is high!");
        Serial.println("You may want to replace the food with a newer batch");
        blinkLight(YELLOW_PIN, 200); // yellow blinks every 200ms
    }
    else if (cur_humidity > HUMIDITY_MEDIUM_THRESHOLD)
    {
        // Alert user of medium humidity issue
        // Suggest opening cap for venting, etc
        // These should be changed to be on TTGO menu/ & display
        Serial.println("The humidity in the reservoir is moderate");
        Serial.println("Opening the reservoir cap might help with ventilation");
    }
    else
    {
        Serial.println("The humidity in the reservoir is low");
        Serial.println("This helps prolong food shelf life");
    }
}