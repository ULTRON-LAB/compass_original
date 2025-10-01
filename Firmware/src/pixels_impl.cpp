#include <FastLED.h>

#include "compass_frames.h"
#include "func.h"
#include "macro_def.h"

CRGB leds[NUM_LEDS];

[[deprecated]]
void lostBearing() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = frames[27][i];
  }
  FastLED.show();
}

void theNether() {
  // 当前帧索引
  static int curIndex = 0;
  // 目标帧索引
  static int targetIndex = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = frames[curIndex][i];
  }
  FastLED.show();
  if (curIndex == targetIndex) {
    targetIndex = random(0, MAX_FRAME_INDEX);
  } else {
    if (curIndex < targetIndex) {
      curIndex += 1;
    } else {
      curIndex -= 1;
    }
  }
  if (curIndex < 0) {
    curIndex = MAX_FRAME_INDEX;
  }
  if (curIndex > MAX_FRAME_INDEX) {
    curIndex = 0;
  }
}

void showFrame(int index, int overrideColor) {
  // Serial.printf("showFrame: relative index=%f,", index);
  static uint32_t color = 0;
  color = overrideColor;
  for (int i = 0; i < NUM_LEDS; i++) {
    // TODO("这里应该使用一个指针数据的模板来设置颜色")
    leds[i] = frames[index][i] == DEFAULT_NEEDLE_COLOR || frames[index][i] == 0xcb1a1a ||
                      frames[index][i] == 0xbe1515 
                  ? color
                  : frames[index][i];
  }
  FastLED.show();
}

void showFrameByAzimuth(float azimuth) {
  if (azimuth < 0 || azimuth > 360) {
    // 不响应不合法的方位角
    return;
  }

  // TODO 指针过冲效果实现

  // 原始素材中指针的方位角不是均匀分布的
  // 去除高度重复帧后, 得到27帧不同的图像, 其中第N张图像对应
  // 1 正上
  // 8 正右
  // 14 正下
  // 21 正右
  int index = 0;
  // 较小的间距
  float step_small = 90.0 / 7.0;
  // 间距(90°~180°)
  float step = 90.0 / 6.0;
  if (azimuth < step_small * 6) {
    // 90.0 / (8 - 1)
    index = static_cast<int>(azimuth / step_small);
  } else if (azimuth < 90 + step * 5) {
    // 90.0 / (14 - 8)
    index = 7 + static_cast<int>((azimuth - 90.0) / step);
  } else if (azimuth < 180 + step_small * 6) {
    // 90.0 / (21 - 14)
    index = 13 + static_cast<int>((azimuth - 180.0) / step_small);
  } else {
    // 90.0 / (28 - 21)
    index = 20 + static_cast<int>((azimuth - 270.0) / step_small);
  }

  // 限制边界
  index = min(MAX_FRAME_INDEX, index);
  index = max(0, index);
  // Serial.printf("showFrameByAzimuth: relative azimuth=%f, index=%d\n", azimuth,
  //               index);
  showFrame(index);
}

void showFrameByBearing(float bearing, int azimuth) {
  // 当前方位角对应的索引
  int aIndex = (int)(azimuth / 360.0 * MAX_FRAME_INDEX);
  // 目标方位角对应的索引
  int bIndex = (int)(bearing / 360.0 * MAX_FRAME_INDEX);
  // 计算差值
  // int index = aIndex - bIndex;
  Serial.printf("showFrameByBearing: bearing=%f azimuth=%d \n", bearing,
                azimuth);
  float degree = bearing - azimuth;
  if (degree < 0) {
    degree += 360;
  }
  showFrameByAzimuth(degree);
}

void showFrameByLocation(float latA, float lonA, float latB, float lonB,
                         int azimuth) {
  // Serial.printf("showFrameByLocation:azimuth=%d\n", azimuth);
  float bearing = calculateBearing(latA, lonA, latB, lonB);
  showFrameByBearing(bearing, azimuth);
}

[[deprecated]]
void showHotspot() {
  FastLED.clear();
  static int blink = 0;
  if (blink == 0) {
    fill_solid(leds, NUM_LEDS, CRGB::Yellow);
  } else {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
  }
  FastLED.show();
  delay(1000);
  blink = 1 - blink;
}

[[deprecated]]
void showConnectingWifi() {
  FastLED.clear();
  static int index = 0;
  for (int i = 0; i < index; i++) {
    leds[i] = CRGB::Green;
  }
  index += 1;
  if (index > NUM_LEDS) {
    index = 0;
  }
  FastLED.show();
  delay(100);
}

void showSolid(int color) {
  fill_solid(leds, NUM_LEDS, CRGB(color));
  FastLED.show();
}

[[deprecated]]
void showServerColors() {
  // 彩虹色
  static int hue = 0;
  fill_rainbow(leds, NUM_LEDS, hue, 1);
  FastLED.show();
  hue += 1;
  delay(16);
}

static void showBouncing(int color) {
  FastLED.clear();
  static int indexes[] = {0, 2, 6, 11, 16, 21, 26, 31, 35, 40};
  static int dir = 1;
  static int index = 0;

  if (index >= 9) {
    dir = -1;
  } else if (index <= 0) {
    dir = 1;
  }

  for (int i = 0; i < 10; i++) {
    // Calculate distance from current index (0-9)
    float distance = abs(i - index);
    // Use gaussian/normal distribution formula
    float brightness = 255 * exp(-(distance * distance) /
                                 (2 * 1.5)); // sigma=1.5 controls spread

    leds[indexes[i]] = color;
    // Apply calculated brightness
    if (distance > 0) {
      leds[indexes[i]].fadeToBlackBy(255 - (int)brightness);
    }
  }
  index += dir;
  FastLED.show();
}

void showServerWifi() {
  showBouncing(CRGB::Green);
  delay(100);
}

void showServerSpawn() {
  showBouncing(CRGB::Blue);
  delay(100);
}

void showServerInfo() {
  showBouncing(CRGB::Red);
  delay(100);
}
