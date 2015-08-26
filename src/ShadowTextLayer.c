#include <pebble.h>
#include "ShadowTextLayer.h"

static void root_layer_draw_proc(Layer *layer, GContext *ctx) {
  //GRect layerFrame = layer_get_frame(layer);
  // TODO How to get color from shadow_text_layer_set_background_color?
  //graphics_context_set_fill_color(ctx, GColorClear);
  //graphics_fill_rect(ctx, GRect(0, 0, layerFrame.size.w, layerFrame.size.h), 0, GCornerNone);
}

ShadowTextLayer *shadow_text_layer_create(GRect frame) {
  const size_t required_size = sizeof(ShadowTextLayer);

  ShadowTextLayer *result = malloc(required_size);

  memset(result, 0, required_size);

  Layer *rootLayer = layer_create(frame);
  layer_set_update_proc(rootLayer, root_layer_draw_proc);

  TextLayer *topLayer = text_layer_create(GRect(0, 0, frame.size.w, frame.size.h));
  TextLayer *shadowLayer = text_layer_create(GRect(0, 0, frame.size.w, frame.size.h));

  text_layer_set_background_color(topLayer, GColorClear);
  text_layer_set_background_color(shadowLayer, GColorClear);

  layer_add_child(rootLayer, text_layer_get_layer(shadowLayer));
  layer_add_child(rootLayer, text_layer_get_layer(topLayer));

  result->rootLayer = rootLayer;
  result->topLayer = topLayer;
  result->shadowLayer = shadowLayer;

  return result;
}

void shadow_text_layer_destroy(ShadowTextLayer *layer) {
  free(layer);
}

Layer *shadow_text_layer_get_layer(ShadowTextLayer *layer) {
  return layer->rootLayer;
}

void shadow_text_layer_set_text(ShadowTextLayer *layer, const char *text) {
  text_layer_set_text(layer->topLayer, text);
  text_layer_set_text(layer->shadowLayer, text);
}

const char *shadow_text_layer_get_text(ShadowTextLayer *layer) {
  return text_layer_get_text(layer->topLayer);
}

void shadow_text_layer_set_background_color(ShadowTextLayer *layer, GColor color) {
  // TODO set color to be used by root_layer_draw_proc
  // layer_mark_dirty(shadow_text_layer_get_layer(layer));
}

void shadow_text_layer_set_text_color(ShadowTextLayer *layer, GColor color) {
  text_layer_set_text_color(layer->topLayer, color);
}

void shadow_text_layer_set_shadow_color(ShadowTextLayer *layer, GColor color) {
  text_layer_set_text_color(layer->shadowLayer, color);
}

void shadow_text_layer_set_shadow_offset(ShadowTextLayer *layer, GPoint offset) {
  GRect frame = layer_get_frame(layer->rootLayer);
  layer_set_frame(text_layer_get_layer(layer->shadowLayer), GRect(offset.x, offset.y, frame.size.w, frame.size.h));

  /*
  GRect frame = layer_get_frame(layer->rootLayer);
  layer_set_bounds(text_layer_get_layer(layer->shadowLayer), GRect(offset.x, offset.y, frame.size.w, frame.size.h));
  */
}

void shadow_text_layer_set_overflow_mode(ShadowTextLayer *layer, GTextOverflowMode line_mode) {
  text_layer_set_overflow_mode(layer->topLayer, line_mode);
  text_layer_set_overflow_mode(layer->shadowLayer, line_mode);
}

void shadow_text_layer_set_font(ShadowTextLayer *layer, GFont font) {
  text_layer_set_font(layer->topLayer, font);
  text_layer_set_font(layer->shadowLayer, font);
}

void shadow_text_layer_set_text_alignment(ShadowTextLayer *layer, GTextAlignment text_alignment) {
  text_layer_set_text_alignment(layer->topLayer, text_alignment);
  text_layer_set_text_alignment(layer->shadowLayer, text_alignment);
}

GSize shadow_text_layer_get_content_size(ShadowTextLayer *layer) {
  return text_layer_get_content_size(layer->topLayer);
}

