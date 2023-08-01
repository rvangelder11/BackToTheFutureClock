void connectWiFi() {
  //WiFi.mode(WIFI_STA);                  // explicitly set mode, esp defaults to STA+AP
  WiFiManager wm;                       // WiFiManager to start as AP to enter WiFi credentials
  wm.setCountry("US");                  // default is china, they have other WiFi channels
  bool res = wm.autoConnect(HostName);  // open AP
  if (!res) {
    Serial.println("Failed to connect");
    WifiConnected = false;
    WiFi.mode(WIFI_AP);  //Set AccessPoint only
    delay(2000);
    bool succes = WiFi.softAP("BTCC_AP");
    if (succes) Serial.println("WiFi Ready");
    else Serial.println("WiFi failed");
    delay(250);
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("connected...yeey :)");  // if you get here you have connected to the WiFi
    delay(500);
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());
    WifiConnected = true;
  }
  delay(200);
  if (WifiConnected) {
    Serial.println("Wait for time sync");  // for accurate clock:
    while (!waitForSync(20)) Serial.println("Reconnecting...");
    Serial.println("time synced");
    Serial.println(myTZ.dateTime("H:i:s"));
    if (!myTZ.setCache(0)) myTZ.setLocation(F("nl"));  // set to Dutch time incl DST
  }
}
