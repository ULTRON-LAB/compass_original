#include <Preferences.h>

#include "func.h"

void saveHomeLocation(Location location) {
  Preferences preferences;
  preferences.begin("mcompass", false);
  preferences.putFloat("latitude", location.latitude);
  preferences.putFloat("longitude", location.longitude);
  preferences.end();
}

void getHomeLocation(Location &location) {
  Preferences preferences;
  preferences.begin("mcompass", false);
  if (!preferences.isKey("latitude") || !preferences.isKey("longitude")) {
    preferences.end();
    return;
  }
  location.latitude = preferences.getFloat("latitude", 0);
  location.longitude = preferences.getFloat("longitude", 0);
  preferences.end();
}