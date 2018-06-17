#include <pebble.h>

static Window *window;
static TextLayer *text_layer1;
static TextLayer *text_layer2;
static TextLayer *yes_layer;
static TextLayer *no_layer;
static BitmapLayer *s_bitmap_layer;


static GBitmap *s_bitmap;



static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  uint32_t segments[] = {200,200,200,200,700,300, 700,300,700};
  //text_layer_set_text(text_layer1, "Up");text_layer_destroy(text_layer2);
  text_layer_destroy(text_layer1);
  text_layer_destroy(text_layer2);
  text_layer_destroy(yes_layer);
  text_layer_destroy(no_layer);
  s_bitmap_layer = bitmap_layer_create(GRect(15, 15, 150, 150));
bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpSet);
bitmap_layer_set_bitmap(s_bitmap_layer, s_bitmap);
layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bitmap_layer));

 
//Create a VibePattern structure with the segments and length of the pattern as fields
VibePattern pattern = {
    .durations = segments,
    .num_segments = ARRAY_LENGTH(segments),
};
 
//Trigger the custom pattern to be executed
vibes_enqueue_custom_pattern(pattern);
}


static void click_config_provider(void *context) {
  //window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  //window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer1 = text_layer_create(GRect(20, 42, bounds.size.w, 34));
  // Use a system font in a TextLayer
  text_layer_set_font(text_layer1, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));

  text_layer_set_text(text_layer1, "Hey Nikki,");
  text_layer_set_text_alignment(text_layer1, GTextAlignmentLeft);
  
  
  text_layer2 = text_layer_create(GRect(20, 72, bounds.size.w, 34));
  // Use a system font in a TextLayer
  text_layer_set_font(text_layer2, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));

  text_layer_set_text(text_layer2, "be my girlfriend?");
  text_layer_set_text_alignment(text_layer2, GTextAlignmentLeft);
  
  
  /*yes or no*/
  yes_layer = text_layer_create(GRect(150, 37, 10, 34));
  // Use a system font in a TextLayer
  text_layer_set_font(yes_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));

  text_layer_set_text(yes_layer, "Y");
  text_layer_set_text_alignment(yes_layer, GTextAlignmentRight);
  
  no_layer = text_layer_create(GRect(150, 109, 10, 34));
  // Use a system font in a TextLayer
  text_layer_set_font(no_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));

  text_layer_set_text(no_layer, "N");
  text_layer_set_text_alignment(no_layer, GTextAlignmentRight);
  
  
  
  layer_add_child(window_layer, text_layer_get_layer(text_layer1));
  layer_add_child(window_layer, text_layer_get_layer(text_layer2));
  layer_add_child(window_layer, text_layer_get_layer(yes_layer));
  layer_add_child(window_layer, text_layer_get_layer(no_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer1);
  text_layer_destroy(text_layer2);
  text_layer_destroy(yes_layer);
  text_layer_destroy(no_layer);
  gbitmap_destroy(s_bitmap);
  bitmap_layer_destroy(s_bitmap_layer);

}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
  s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_DOGE_IMAGE);

}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
