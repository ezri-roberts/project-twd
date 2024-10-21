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

<<<<<<< HEAD
    canvas->source.width = (float)canvas->width;
    canvas->source.height = -(float)canvas->height;

    canvas->dest.x = (GetScreenWidth() - ((float)canvas->width * scale)) * 0.5f;
    canvas->dest.y = (GetScreenHeight() - ((float)canvas->height * scale)) * 0.5f;
    canvas->dest.width = (float)canvas->width * scale;
    canvas->dest.height = (float)canvas->height * scale;
=======
	canvas.width = width;
	canvas.height = height;
	canvas.target = LoadRenderTexture(width, height);
	canvas.source.x = 0.0f;
	canvas.source.y = 0.0f;
	canvas.mouse = (Vector2){0, 0};

	SetTextureFilter(canvas.target.texture, filter);

	log_info("Initialized canvas.");

	return canvas;
}

void canvas_destroy(Canvas *canvas) {
	UnloadRenderTexture(canvas->target);
	log_info("Destroyed canvas");
}

void canvas_update(Canvas *canvas) {

	float scale = MIN(
		(float)GetScreenWidth()/canvas->width,
		(float)GetScreenHeight()/canvas->height
	);

	canvas->source.width = (float)canvas->width;
	canvas->source.height = -(float)canvas->height;

	canvas->dest.x = (GetScreenWidth() - ((float)canvas->width*scale)) * 0.5f;
	canvas->dest.y = (GetScreenHeight() - ((float)canvas->height*scale)) * 0.5f;
	canvas->dest.width = (float)canvas->width * scale;
	canvas->dest.height= (float)canvas->height * scale;

	Vector2 mouse = GetMousePosition();
	canvas->mouse.x = (mouse.x - (GetScreenWidth() - (canvas->width*scale))*0.5f)/scale;
	canvas->mouse.y = (mouse.y - (GetScreenHeight() - (canvas->height*scale))*0.5f)/scale;
	canvas->mouse = Vector2Clamp(canvas->mouse, (Vector2){ 0, 0 }, (Vector2){ (float)canvas->width, (float)canvas->height});
>>>>>>> 5cd81f77065e260827b9c3b347c794bb6cd98389
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

