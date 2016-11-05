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

#include <pebble.h>
#include "helpers.h"

void layer_move(Layer *layer, int x, int y) {
    GRect frame = layer_get_frame(layer);
    GPoint point = GPoint(x, y);

    if (!gpoint_equal(&frame.origin, &point)) {
        frame.origin = point;
        layer_set_frame(layer, frame);
    }
}

void text_layer_move(TextLayer *layer, int x, int y) {
    layer_move((Layer *) layer, x, y);
}

void bitmap_layer_move(BitmapLayer *layer, int x, int y) {
    layer_move((Layer *) layer, x, y);
}

void layer_hide(Layer *layer) {
    if (layer != NULL) {
        layer_set_hidden(layer, true);
    }
}

void text_layer_hide(TextLayer *layer) {
    if (layer != NULL) {
        layer_hide((Layer *) layer);
    }
}

void bitmap_layer_hide(BitmapLayer *layer) {
    if (layer != NULL) {
        layer_hide((Layer *) layer);
    }
}

void layer_show(Layer *layer) {
    if (layer != NULL) {
        layer_set_hidden(layer, false);
    }
}

void text_layer_show(TextLayer *layer) {
    if (layer != NULL) {
        layer_show((Layer *) layer);
    }
}

void bitmap_layer_show(BitmapLayer *layer) {
    if (layer != NULL) {
        layer_show((Layer *) layer);
    }
}

Layer *layer_init(Layer *window, GRect frame, LayerUpdateProc update_proc) {
    Layer *layer = layer_create(frame);
    layer_set_update_proc(layer, update_proc);
    layer_add_child(window, layer);

    return layer;
}

TextLayer *text_layer_init(Layer *window, GRect frame, GFont font, GColor background_color, GColor text_color, GTextAlignment alignment) {
    TextLayer *layer = text_layer_create(frame);
    text_layer_set_font(layer, font);
    text_layer_set_background_color(layer, background_color);
    text_layer_set_text_color(layer, text_color);
    text_layer_set_text_alignment(layer, alignment);
    layer_add_child(window, text_layer_get_layer(layer));

    return layer;
}

BitmapLayer *bitmap_layer_init(Layer *window, GRect frame, GBitmap *bitmap, GColor background_color) {
    BitmapLayer *layer = bitmap_layer_create(frame);
    bitmap_layer_set_bitmap(layer, bitmap);
    bitmap_layer_set_background_color(layer, background_color);
    layer_add_child(window, bitmap_layer_get_layer(layer));

    return layer;
}

void layer_destroy_safe(Layer *layer) {
    if (layer != NULL) {
        layer_destroy(layer);
        layer = NULL;
    }
}

void text_layer_destroy_safe(TextLayer *layer) {
    if (layer != NULL) {
        text_layer_destroy(layer);
        layer = NULL;
    }
}

void bitmap_layer_destroy_safe(BitmapLayer *layer) {
    if (layer != NULL) {
        bitmap_layer_destroy(layer);
        layer = NULL;
    }
}

GFont fonts_load_resource_font(uint32_t resource_id) {
    return fonts_load_custom_font(resource_get_handle(resource_id));
}

void fonts_unload_custom_font_safe(GFont font) {
    if (font != NULL) {
        fonts_unload_custom_font(font);
        font = NULL;
    }
}

GColor get_color(int color) {
    #ifdef PBL_COLOR
        if (color == 1) {
            return GColorWhite;
        }
        else {
            return GColorFromHEX(color);
        }
    #else
        if (color == 0) {
            return GColorBlack;
        }
        else if (color == 2) {
            return GColorDarkGray;
        }
        else {
            return GColorWhite;
        }
    #endif
}

//From https://github.com/smallstoneapps/message-queue/blob/master/message-queue.c#L222
char *translate_message_error(AppMessageResult result) {
    switch (result) {
        case APP_MSG_OK:
            return "APP_MSG_OK";
        case APP_MSG_SEND_TIMEOUT:
            return "APP_MSG_SEND_TIMEOUT";
        case APP_MSG_SEND_REJECTED:
            return "APP_MSG_SEND_REJECTED";
        case APP_MSG_NOT_CONNECTED:
            return "APP_MSG_NOT_CONNECTED";
        case APP_MSG_APP_NOT_RUNNING:
            return "APP_MSG_APP_NOT_RUNNING";
        case APP_MSG_INVALID_ARGS:
            return "APP_MSG_INVALID_ARGS";
        case APP_MSG_BUSY:
            return "APP_MSG_BUSY";
        case APP_MSG_BUFFER_OVERFLOW:
            return "APP_MSG_BUFFER_OVERFLOW";
        case APP_MSG_ALREADY_RELEASED:
            return "APP_MSG_ALREADY_RELEASED";
        case APP_MSG_CALLBACK_ALREADY_REGISTERED:
            return "APP_MSG_CALLBACK_ALREADY_REGISTERED";
        case APP_MSG_CALLBACK_NOT_REGISTERED:
            return "APP_MSG_CALLBACK_NOT_REGISTERED";
        case APP_MSG_OUT_OF_MEMORY:
            return "APP_MSG_OUT_OF_MEMORY";
        case APP_MSG_CLOSED:
            return "APP_MSG_CLOSED";
        case APP_MSG_INTERNAL_ERROR:
            return "APP_MSG_INTERNAL_ERROR";
        default:
            return "UNKNOWN ERROR";
    }
}