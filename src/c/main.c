#include <pebble.h>
#include "helpers.h"

static Window *s_main_window;
static TextLayer *s_cmd_layer;
static TextLayer *s_time_layer;
static TextLayer *s_bt_cmd_layer;
static TextLayer *s_batt_layer;
static GFont s_time_font;
static int s_battery_level;

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DOS_15));
    
  s_cmd_layer = text_layer_init(window_layer, GRect(1, 2, bounds.size.w, 15), s_time_font, GColorClear, GColorBlack, GTextAlignmentLeft);
  s_time_layer = text_layer_init(window_layer, GRect(1, 17, bounds.size.w, 30), s_time_font, GColorClear, GColorBlack, GTextAlignmentLeft);
  s_bt_cmd_layer = text_layer_init(window_layer, GRect(1, 47, bounds.size.w, 15), s_time_font, GColorClear, GColorBlack, GTextAlignmentLeft);
  s_batt_layer = text_layer_init(window_layer, GRect(1, 62, bounds.size.w, 15), s_time_font, GColorClear, GColorBlack, GTextAlignmentLeft);

  text_layer_set_text(s_cmd_layer, "$ ./datetime.sh");
  text_layer_set_text(s_bt_cmd_layer, "$ ./batt.sh");
}

static void main_window_unload(Window *window) {
  text_layer_destroy_safe(s_time_layer);
  text_layer_destroy_safe(s_cmd_layer);
  text_layer_destroy_safe(s_bt_cmd_layer);
  text_layer_destroy_safe(s_batt_layer);
  fonts_unload_custom_font(s_time_font);
}

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  static char s_time[8];
  strftime(s_time, sizeof(s_time), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
  
  static char s_date[11];
  strftime(s_date, sizeof(s_date), "%Y-%m-%d", tick_time);
  
  static char line[] = "DATE: 2016-11-04\nTIME: 24:00";
  snprintf(line, sizeof(line), "DATE: %s\nTIME: %s", s_date, s_time);
    
  text_layer_set_text(s_time_layer, line);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void battery_callback(BatteryChargeState state) {
  s_battery_level = state.charge_percent;
  
  static char line[] = "100%";
  snprintf(line, sizeof(line), "%d%%", s_battery_level);
    
  text_layer_set_text(s_batt_layer, line);
}

static void init() {
  s_main_window = window_create();
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  window_stack_push(s_main_window, true);
  
  update_time();
  battery_callback(battery_state_service_peek());
  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  battery_state_service_subscribe(battery_callback);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}