#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

TonySHT31 sht31;
TonyTFT tft = TonyTFT(SLOT1, TFT_240_320);

unsigned long lastMeasure = 0;
unsigned long interval = 1000;
unsigned long now = 0;

lv_obj_t * label_Temp;
lv_obj_t * label_Humi;
lv_obj_t * lmeter_Temp;
lv_obj_t * lmeter_Humi;
lv_obj_t * chart;
lv_chart_series_t * ser_Temp;
lv_chart_series_t * ser_Humi;

void setup() {
  Serial.begin(115200);
  Tony.begin();
  sht31.begin(0x44);
  lvglInit(&tft);
  startLvglHandle();
  lv_theme_t * themes = lv_theme_alien_init(20, NULL);
  lv_theme_set_current(themes);
  lv_obj_t * cont_Temp =
    lv_cont_create(lv_disp_get_scr_act(NULL), NULL);
  lv_obj_set_size(cont_Temp, 95, 110);
  lv_obj_align(cont_Temp, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 30);
  lv_obj_t * cont_Humi =
    lv_cont_create(lv_disp_get_scr_act(NULL), NULL);
  lv_obj_set_size(cont_Humi, 95, 110);
  lv_obj_align(cont_Humi, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 30);
  lmeter_Temp = lv_lmeter_create(cont_Temp, NULL);
  lv_lmeter_set_range(lmeter_Temp, 0, 100);
  lv_lmeter_set_value(lmeter_Temp, 80);
  lv_lmeter_set_scale(lmeter_Temp, 240, 21);
  lv_obj_set_size(lmeter_Temp, 80, 80);
  lv_obj_align(lmeter_Temp, NULL, LV_ALIGN_CENTER, 0, 0);
  lmeter_Humi = lv_lmeter_create(cont_Humi, NULL);
  lv_lmeter_set_range(lmeter_Humi, 0, 100);
  lv_lmeter_set_value(lmeter_Humi, 20);
  lv_lmeter_set_scale(lmeter_Humi, 240, 21);
  lv_obj_set_size(lmeter_Humi, 80, 80);
  lv_obj_align(lmeter_Humi, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_t * symbol_Temp = lv_label_create(cont_Temp, NULL);
  lv_label_set_text(symbol_Temp, "T");
  lv_obj_align(symbol_Temp, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_t * symbol_Humi = lv_label_create(cont_Humi, NULL);
  lv_label_set_text(symbol_Humi, "H");
  lv_obj_align(symbol_Humi, NULL, LV_ALIGN_CENTER, 0, 0);
  label_Temp = lv_label_create(cont_Temp, NULL);
  lv_label_set_text(label_Temp, "00.00");
  lv_obj_align(label_Temp, NULL, LV_ALIGN_CENTER, 0, 40);
  label_Humi = lv_label_create(cont_Humi, NULL);
  lv_label_set_text(label_Humi, "00.00");
  lv_obj_align(label_Humi, NULL, LV_ALIGN_CENTER, 0, 40);
  chart = lv_chart_create(lv_scr_act(), NULL);
  lv_obj_set_size(chart, 200, 150);
  lv_obj_align(chart, NULL, LV_ALIGN_CENTER, 0, 60);
  lv_chart_set_type(chart, LV_CHART_TYPE_POINT |
                    LV_CHART_TYPE_LINE);
  lv_chart_set_series_width(chart, 4);
  lv_chart_set_range(chart, 0, 100);
  ser_Temp = lv_chart_add_series(chart, LV_COLOR_RED);
  ser_Humi = lv_chart_add_series(chart, LV_COLOR_CYAN);
}

void loop()
{
  now = millis();
  if (now - lastMeasure > interval)
  {
    lastMeasure = now;
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();
    String temp = String(t, 2);
    String humi = String(h, 2);
    if (!isnan(t)) {
      lv_label_set_text(label_Temp, temp.c_str());
      lv_lmeter_set_value(lmeter_Temp, t);
      lv_chart_set_next(chart, ser_Temp, t);
    }
    else {
      Serial.println("Failed to read temperature");
    }
    if (!isnan(h)) {
      lv_label_set_text(label_Humi, humi.c_str());
      lv_lmeter_set_value(lmeter_Humi, h);
      lv_chart_set_next(chart, ser_Humi, h);
    }
    else {
      Serial.println("Failed to read humidity");
    }
    delay(10);
  }
}
