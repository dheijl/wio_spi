#pragma once

#include <rpcWiFi.h>

bool is_wifi_connected();
bool start_wifi(String ssid, String psw);
void stop_wifi();
