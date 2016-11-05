/**
 * Copyright (C) 2016 Brian Douglass (bhdouglass.com)
 *
 * This program is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranties of MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see http://www.gnu.org/licenses/.
 */

#pragma once

#include <pebble.h>

//Move a layer to a new position (without having to know the size)
void layer_move(Layer *layer, int x, int y);
void text_layer_move(TextLayer *layer, int x, int y);
void bitmap_layer_move(BitmapLayer *layer, int x, int y);

//Shortcut for hiding layers
void layer_hide(Layer *layer);
void text_layer_hide(TextLayer *layer);
void bitmap_layer_hide(BitmapLayer *layer);

//Shortcut for showing layers
void layer_show(Layer *layer);
void text_layer_show(TextLayer *layer);
void bitmap_layer_show(BitmapLayer *layer);

//Initialize and setup layers in one function call
Layer *layer_init(Layer *window, GRect frame, LayerUpdateProc update_proc);
TextLayer *text_layer_init(Layer *window, GRect frame, GFont font, GColor background_color, GColor text_color, GTextAlignment alignment);
BitmapLayer *bitmap_layer_init(Layer *window, GRect frame, GBitmap *bitmap, GColor background_color);

//Safely destroy a layer
void layer_destroy_safe(Layer *layer);
void text_layer_destroy_safe(TextLayer *layer);
void bitmap_layer_destroy_safe(BitmapLayer *layer);

//Shortcut fof loading a custom font
GFont fonts_load_resource_font(uint32_t resource_id);

//Safely unload a font
void fonts_unload_custom_font_safe(GFont font);

//Get a GColor from an integer (see c file for more info)
GColor get_color(int color);

//Translate an app message result into something printable (based on https://github.com/smallstoneapps/message-queue/blob/master/message-queue.c#L222)
char *translate_message_error(AppMessageResult result);