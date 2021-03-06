
void configModeCallback (WiFiManager *myWiFiManager) {
  ticker.attach(0.2, tick);
}

void saveConfigCallback () {
  DEBUG_PRINTLNC(F("[WM] Should save config"));
  shouldSaveConfig = true;
}

void setupWifiManager () {
  WiFiManagerParameter custom_device_id("device_id", "DeviceID", device_id, 40);
  WiFiManagerParameter custom_device_token("device_token", "DeviceToken", device_token, 70);
  WiFiManagerParameter custom_client_id("client_id", "ClientID", client_id, 40);

  WiFiManager wifiManager;

  wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.setAPCallback(configModeCallback);

  wifiManager.addParameter(&custom_device_id);
  wifiManager.addParameter(&custom_device_token);
  wifiManager.addParameter(&custom_client_id);

  if (!wifiManager.autoConnect("ESP-32")) {
    DEBUG_PRINTLNC(F("[WM] failed to connect and hit timeout"));
    delay(3000);

    ESP.restart();
    delay(5000);
  }

  DEBUG_PRINTLNC(F("[WIFI] Connected"));

  strcpy(device_id, custom_device_id.getValue());
  strcpy(device_token, custom_device_token.getValue());
  strcpy(client_id, custom_client_id.getValue());

  if (shouldSaveConfig) {
    DEBUG_PRINTLNC(F("[WM] Saving config"));

    DEBUG_PRINTC(F("[WM] API: "));
    DEBUG_PRINTLN(API_URL);

    DEBUG_PRINTC(F("[WM] DeviceID: "));
    DEBUG_PRINTLN(device_id);

    DEBUG_PRINTC(F("[WM] DeviceToken: "));
    DEBUG_PRINTLN(device_token);

    DEBUG_PRINTC(F("[WM] ClientID: "));
    DEBUG_PRINTLN(client_id);

    setDeviceID(device_id);
    setDeviceToken(device_token);
    setClientID(client_id);
  }
}

