//
// Created by diego on 2/14/22.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#ifndef PROJECT_ORACLE_RENDERING_H
#define PROJECT_ORACLE_RENDERING_H

#define LINE_THICKNESS 2.5

#include <cstdlib>

#include "raylib.h"
#include "tmx.h"

void* raylib_tex_loader(const char *path) {
    auto *returnValue = static_cast<Texture2D *>(malloc(sizeof(Texture2D)));
    *returnValue = LoadTexture(path);
    return returnValue;
}

void raylib_free_tex(void *ptr)
{
    UnloadTexture(*((Texture2D*)ptr));
    free(ptr);
}

Color int_to_color(int color) {
    tmx_col_bytes res = tmx_col_to_bytes(color);
    return *((Color*)&res);
}

void draw_tile(void *image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
               unsigned int dx, unsigned int dy, float opacity, unsigned int flags) {
    auto *texture = (Texture2D*)image;
    int op = 0xFF * opacity;
    DrawTextureRec(*texture, (Rectangle) {static_cast<float>(sx), static_cast<float>(sy), static_cast<float>(sw), static_cast<float>(sh)}, (Vector2) {static_cast<float>(dx), static_cast<float>(dy)}, (Color) {static_cast<unsigned char>(op), static_cast<unsigned char>(op), static_cast<unsigned char>(op), static_cast<unsigned char>(op)});
}

void draw_image_layer(_tmx_img *image) {
    auto *texture = (Texture2D*)image->resource_image;
    DrawTexture(*texture, 0, 0, WHITE);
}

void draw_layer(tmx_map *map, tmx_layer *layer) {
    unsigned long i, j;
    unsigned int gid, x, y, w, h, flags;
    float op;
    tmx_tileset *ts;
    tmx_image *im;
    void* image;
    op = layer->opacity;
    for (i=0; i<map->height; i++) {
        for (j=0; j<map->width; j++) {
            gid = layer->content.gids[(i * map->width) + j] & TMX_FLIP_BITS_REMOVAL;
            if (map->tiles[gid] != nullptr) {
                ts = map->tiles[gid]->tileset;
                im = map->tiles[gid]->image;
                x  = map->tiles[gid]->ul_x;
                y  = map->tiles[gid]->ul_y;
                w  = ts->tile_width;
                h  = ts->tile_height;
                if (im) {
                    image = im->resource_image;
                }
                else {
                    image = ts->image->resource_image;
                }
                flags = layer->content.gids[(i * map->width) + j] & ~TMX_FLIP_BITS_REMOVAL;
                draw_tile(image, x, y, w, h, j*ts->tile_width, i*ts->tile_height, op, flags);
            }
        }
    }
}

void draw_polyline(double offset_x, double offset_y, double **points, int points_count, Color color) {
    int i;
    for (i=1; i<points_count; i++) {
        DrawLineEx((Vector2){static_cast<float>(offset_x + points[i-1][0]), static_cast<float>(offset_y + points[i-1][1])},
                   (Vector2){static_cast<float>(offset_x + points[i][0]), static_cast<float>(offset_y + points[i][1])},
                   LINE_THICKNESS, color);
    }
}

void draw_polygon(double offset_x, double offset_y, double **points, int points_count, Color color) {
    draw_polyline(offset_x, offset_y, points, points_count, color);
    if (points_count > 2) {
        DrawLineEx((Vector2){static_cast<float>(offset_x + points[0][0]), static_cast<float>(offset_y + points[0][1])},
                   (Vector2){static_cast<float>(offset_x + points[points_count-1][0]), static_cast<float>(offset_y + points[points_count-1][1])},
                   LINE_THICKNESS, color);
    }
}

void draw_objects(tmx_object_group *objgr) {
    tmx_object *head = objgr->head;
    Color color = int_to_color(objgr->color);

    while (head) {
        if (head->visible) {
            if (head->obj_type == OT_SQUARE) {
                DrawRectangleLinesEx((Rectangle){static_cast<float>(head->x), static_cast<float>(head->y), static_cast<float>(head->width), static_cast<float>(head->height)}, LINE_THICKNESS, color);
            }
            else if (head->obj_type  == OT_POLYGON) {
                draw_polygon(head->x, head->y, head->content.shape->points, head->content.shape->points_len, color);
            }
            else if (head->obj_type == OT_POLYLINE) {
                draw_polyline(head->x, head->y, head->content.shape->points, head->content.shape->points_len, color);
            }
            else if (head->obj_type == OT_ELLIPSE) {
                DrawEllipseLines(head->x + head->width/2.0, head->y + head->height/2.0, head->width/2.0, head->height/2.0, color);
            }
        }
        head = head->next;
    }
}

void draw_all_layers(tmx_map *map, tmx_layer *layers) {
    while (layers) {
        if (layers->visible) {
            if (layers->type == L_GROUP) {
                draw_all_layers(map, layers->content.group_head);
            }
            else if (layers->type == L_OBJGR) {
                draw_objects(layers->content.objgr);
            }
            else if (layers->type == L_IMAGE) {
                draw_image_layer(layers->content.image);
            }
            else if (layers->type == L_LAYER) {
                draw_layer(map, layers);
            }
        }

        layers = layers->next;
    }
}

void render_map(tmx_map *map) {
    ClearBackground(int_to_color(map->backgroundcolor));
    draw_all_layers(map, map->ly_head); // Function to be implemented
}


#endif //PROJECT_ORACLE_RENDERING_H

#pragma clang diagnostic pop