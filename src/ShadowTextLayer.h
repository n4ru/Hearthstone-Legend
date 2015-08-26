#include <pebble.h>

typedef struct {
  Layer *rootLayer;
  TextLayer *topLayer;
  TextLayer *shadowLayer;
} ShadowTextLayer;

ShadowTextLayer *shadow_text_layer_create(GRect frame);

void shadow_text_layer_destroy(ShadowTextLayer *layer);

Layer *shadow_text_layer_get_layer(ShadowTextLayer *layer);

void shadow_text_layer_set_text(ShadowTextLayer *root_layer, const char *text);

const char *shadow_text_layer_get_text(ShadowTextLayer *layer);

void shadow_text_layer_set_background_color(ShadowTextLayer *layer, GColor color);

void shadow_text_layer_set_text_color(ShadowTextLayer *layer, GColor color);

void shadow_text_layer_set_shadow_color(ShadowTextLayer *layer, GColor color);

void shadow_text_layer_set_shadow_offset(ShadowTextLayer *layer, GPoint offset);

void shadow_text_layer_set_overflow_mode(ShadowTextLayer *layer, GTextOverflowMode line_mode);

void shadow_text_layer_set_font(ShadowTextLayer *layer, GFont font);

void shadow_text_layer_set_text_alignment(ShadowTextLayer *layer, GTextAlignment text_alignment);

GSize shadow_text_layer_get_content_size(ShadowTextLayer *layer);



