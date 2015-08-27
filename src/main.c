#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer1;
static TextLayer *s_time_layer2;
static TextLayer *s_time_layer3;
static TextLayer *s_time_layer4;
static TextLayer *s_time_layer;

static GFont s_time_font;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    //Use 2h hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    //Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer1, buffer);
  text_layer_set_text(s_time_layer2, buffer);
  text_layer_set_text(s_time_layer3, buffer);
  text_layer_set_text(s_time_layer4, buffer);
  text_layer_set_text(s_time_layer, buffer);
}

static void main_window_load(Window *window) {
  //Create GBitmap, then set to created BitmapLayer
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BACKGROUND);
  s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));
	
  // Stroke Text
  s_time_layer1 = text_layer_create(GRect(-2, 63, 144, 50));
  text_layer_set_background_color(s_time_layer1, GColorClear);
  text_layer_set_text_color(s_time_layer1, GColorBlack);
  text_layer_set_text(s_time_layer1, "00:00");
  s_time_layer2 = text_layer_create(GRect(-2, 67, 144, 50));
  text_layer_set_background_color(s_time_layer2, GColorClear);
  text_layer_set_text_color(s_time_layer2, GColorBlack);
  text_layer_set_text(s_time_layer2, "00:00");
  s_time_layer3 = text_layer_create(GRect(2, 63, 144, 50));
  text_layer_set_background_color(s_time_layer3, GColorClear);
  text_layer_set_text_color(s_time_layer3, GColorBlack);
  text_layer_set_text(s_time_layer3, "00:00");
  s_time_layer4 = text_layer_create(GRect(2, 67, 144, 50));
  text_layer_set_background_color(s_time_layer4, GColorClear);
  text_layer_set_text_color(s_time_layer4, GColorBlack);
  text_layer_set_text(s_time_layer4, "00:00");
  
  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 65, 144, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_text(s_time_layer, "00:00");
  
  //Create GFont
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_BELWE_BOLD_42));

  //Apply to TextLayer
  text_layer_set_text_alignment(s_time_layer1, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer2, s_time_font);
  text_layer_set_text_alignment(s_time_layer2, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer3, s_time_font);
  text_layer_set_text_alignment(s_time_layer3, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer4, s_time_font);
  text_layer_set_text_alignment(s_time_layer4, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer1, s_time_font);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer1));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer2));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer3));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer4));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  
  // Make sure the time is displayed from the start
  update_time();
}

static void main_window_unload(Window *window) {
  //Unload GFont
  fonts_unload_custom_font(s_time_font);
  
  //Destroy GBitmap
  gbitmap_destroy(s_background_bitmap);

  //Destroy BitmapLayer
  bitmap_layer_destroy(s_background_layer);
  
  // Destroy TextLayer
  text_layer_destroy(s_time_layer1);
  text_layer_destroy(s_time_layer2);
  text_layer_destroy(s_time_layer3);
  text_layer_destroy(s_time_layer4);
  text_layer_destroy(s_time_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
