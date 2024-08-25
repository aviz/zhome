#include <Arduino.h>
#include <ArduinoLog.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

void setup()
{
    // should be the same value as for the `test_speed` option in "platformio.ini"
    // default value is test_speed=115200
    Serial.begin(115200);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);

    Log.notice("Initialazing\n");

    ::testing::InitGoogleMock();
}

void loop()
{
  // Run tests
  if (RUN_ALL_TESTS());

  // sleep for 1 sec
  delay(1000);
}
