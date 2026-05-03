#include <M5Unified.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "wifi_config.h"

static void setupOTA() {
    ArduinoOTA.setHostname(OTA_HOSTNAME);
#ifdef OTA_PASSWORD
    ArduinoOTA.setPassword(OTA_PASSWORD);
#endif

    ArduinoOTA.onStart([]() {
        M5.Display.clear();
        M5.Display.drawString("OTA Start...", M5.Display.width() / 2, M5.Display.height() / 2);
    });

    ArduinoOTA.onEnd([]() {
        M5.Display.clear();
        M5.Display.drawString("OTA Done!", M5.Display.width() / 2, M5.Display.height() / 2);
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        M5.Display.clear();
        String msg = "OTA " + String(progress * 100 / total) + "%";
        M5.Display.drawString(msg, M5.Display.width() / 2, M5.Display.height() / 2);
    });

    ArduinoOTA.onError([](ota_error_t error) {
        M5.Display.clear();
        String msg = "OTA Err:" + String(error);
        M5.Display.drawString(msg, M5.Display.width() / 2, M5.Display.height() / 2);
    });

    ArduinoOTA.begin();
}

void setup() {
    M5.begin();

    M5.Display.setTextColor(WHITE);
    M5.Display.setTextDatum(middle_center);
    M5.Display.setFont(&fonts::FreeSans9pt7b);
    M5.Display.setTextSize(1);

    M5.Display.drawString("Connecting WiFi", M5.Display.width() / 2, M5.Display.height() / 2);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    setupOTA();

    M5.Display.clear();
    M5.Display.drawString("hello Android", M5.Display.width() / 2, M5.Display.height() / 2);
}

void loop() {
    M5.update();
    ArduinoOTA.handle();
}
