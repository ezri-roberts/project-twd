#include <stdbool.h>
#include "raylib.h"
#include "scene_builder.h"
#include "game.h"
#include "assets.h"
#include "log.h"
#include "ecs.h"

extern map_base_t entity_map;

// List of tile paths
const char* TilePaths[] = {
    "",
    "assets/Terrain/Ground/Tilemap_Flat.png",
    "assets/Terrain/Ground/Tilemap_Elevation.png",
    "assets/Terrain/Ground/Shadows.png",
    "assets/Terrain/Water/Water.png",
    "assets/Terrain/Water/Rocks/Rocks_01.png",
    "assets/Terrain/Water/Rocks/Rocks_02.png",
    "assets/Terrain/Water/Rocks/Rocks_03.png",
    "assets/Terrain/Water/Rocks/Rocks_04.png",
    "assets/Terrain/Bridge/Bridge_All.png"
};

// Get the file path for a tile type
const char* get_tile_file_path(int TileType) {
    return TilePaths[TileType];
}

// Initialize the scene with a difficulty level
void scene_initialize(int difficulty) {
    Scene NewScene;
    NewScene.difficulty = difficulty;
    scene_populate(NewScene);
}

// Populate the scene with tiles and optionally draw entities (like enemies)
void scene_populate(Scene NewScene) {
    for (int i = 0; i < MAXHEIGHT; i++) {
        for (int j = 0; j < MAXWIDTH; j++) {
            BeginDrawing();
            
            // Get the tile texture and draw it
            NewScene.tilemap.asset_ptr = assets_get(get_tile_file_path(NewScene.tilemap.tiles[i][j]));
			DrawTexture(NewScene.tilemap.asset_ptr->data.texture, j * GAME_MAX_SCENES, i * GAME_MAX_SCENES, WHITE);
			
            // Draw all active entities (like enemies) on the scene
            map_iter_t iter = map_iter_();
            const char *key;
            while ((key = map_next_(&entity_map, &iter))) {
                GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
                if (entity && entity->entity.isActive) {
                    // Draw entities as simple shapes (circles or rectangles)
                    DrawCircleV((Vector2){entity->position.x, entity->position.y}, 20, RED);  // Example: Draw entity as a red circle
                }
            }

            EndDrawing();
        }
    }
}

