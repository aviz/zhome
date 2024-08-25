#include <Arduino.h>
#include <ArduinoLog.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AppManager.h"
#include "Event.h"

// Mock class for Event
class MockEvent : public Event {
public:
    MOCK_METHOD3(_subscribe, void(std::string caller, int eventId, EventCb cb));
    MOCK_METHOD2(_publish, void(int eventId, void* data));
};

// Test fixture for AppManager
class AppManagerTest : public testing::Test {
protected:
    AppManager appManager;
    MockEvent mockEvent;

    void SetUp() override {
        // Set up the mock Event object
        Event::setInstance(&mockEvent);
    }

    void TearDown() override {
        // Clean up the mock Event object
        Event::setInstance(nullptr);
    }
};

// Test case for onSetup() method
TEST_F(AppManagerTest, OnSetup) {
    // Arrange
    EXPECT_CALL(mockEvent, _publish(ON_INIT, nullptr));
    EXPECT_CALL(mockEvent, _publish(ON_SETUP, nullptr));

    // Act
    appManager.onSetup();

}

// Test case for onLoop() method
TEST_F(AppManagerTest, OnLoop) {
    // Arrange
    EXPECT_CALL(mockEvent, _publish(ON_LOOP, nullptr));

    // Act
    appManager.onLoop();
    

    // No assertion needed
}

// Test case for the constructor
TEST_F(AppManagerTest, Constructor) {
    // No setup or assertion needed
}



