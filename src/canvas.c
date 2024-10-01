#include "canvas.h"
#include "entity_movement.h"
#include "map.h"
#include "ecs.h"

// Declare entity_map as an external variable
extern map_base_t entity_map;

void canvas_resize(Canvas *canvas) {
    float scale = MIN(
        (float)GetScreenWidth()/canvas->width,
        (float)GetScreenHeight()/canvas->height
    );

    canvas->source.width = (float)canvas->width;
    canvas->source.height = -(float)canvas->height;

    canvas->dest.x = (GetScreenWidth() - ((float)canvas->width * scale)) * 0.5f;
    canvas->dest.y = (GetScreenHeight() - ((float)canvas->height * scale)) * 0.5f;
    canvas->dest.width = (float)canvas->width * scale;
    canvas->dest.height = (float)canvas->height * scale;
}

void canvas_begin(Canvas *canvas) {
    BeginTextureMode(canvas->target);
    ClearBackground(WHITE);
}

void canvas_end() {
    EndTextureMode();
}

void canvas_draw(Canvas *canvas) {
    ClearBackground(BLACK);

    // Draw the canvas texture
    DrawTexturePro(
        canvas->target.texture,
        canvas->source, 
        canvas->dest,
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    // Draw all entities on the canvas
    map_iter_t iter = map_iter_();
    const char *key;
    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity && entity->entity.isActive) {
            // Draw entities as circles (or any other primitive) using position and size
            DrawCircleV((Vector2){entity->position.x, entity->position.y}, 20, RED); 
        }
    }
}

