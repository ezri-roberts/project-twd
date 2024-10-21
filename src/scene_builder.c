<<<<<<< HEAD
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

=======
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/raylib/src/raylib.h"
#include "scene_builder.h"
#include "scene_path.h"
#include "assets.h"

void tileval_from_file(const char *filename, int (*tiles)[TILEMAP_WIDTH]) {

	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		printf("Error opening file.\n");
	}

	int num;
	for(int y=0; y<TILEMAP_HEIGHT; y++) {

		for(int x=0; x<TILEMAP_WIDTH; x++) {

			fscanf(file, "%d,", &num);
			tiles[y][x] = num;
		}
	}

	fclose(file);
}


void scene_draw(Scene *scene)
{
	Vector2 tile_tex_coords[10] = {
		(Vector2){0,0},
		(Vector2){16,0},
		(Vector2){32,0},
		(Vector2){48,0},
		(Vector2){64,0},
		(Vector2){80,0},
		(Vector2){96,0},
		(Vector2){112,0},
		(Vector2){0,16},
		(Vector2){16,16}
	};

	for(int y=0; y<TILEMAP_HEIGHT; y++) {

		for(int x=0; x<TILEMAP_WIDTH; x++) {

			int tile = scene->tilemap.tiles[y][x];
			int xp = x * TILESIZE;
			int yp = y * TILESIZE;

			asset_draw_tile(scene->tilemap.asset_ptr, tile, xp, yp);
		}
	}
}

Scene scene_init(int difficulty, const char* path) {

	Scene scene;
	scene.difficulty = difficulty;
	// tileval_from_file("src/numbers.txt", NewScene.tilemap.tiles);

	scene_randomize(&scene);

	scene.tilemap.asset_ptr = assets_get(path);
	return scene;
}

void scene_randomize(Scene *scene) {

	for (int y = 0; y < TILEMAP_HEIGHT; y++) {
		for (int x = 0; x < TILEMAP_WIDTH; x++) {

			//if (y == 8) {
				//scene->tilemap.tiles[y][x] = 5;
			//} else {

				int r = GetRandomValue(0, 10);
				if (r <= 4) {
					scene->tilemap.tiles[y][x] = 0;
				} else if (r > 4 && r <= 8) {
					scene->tilemap.tiles[y][x] = 1;
				} else if (r > 8 && r <= 9) {
					scene->tilemap.tiles[y][x] = 2;
				} else if (r == 10) {
					scene->tilemap.tiles[y][x] = 3;
				}
			//}

		}
	}
	gen_random_path(scene);
}
>>>>>>> d19befc1953f64d5e9afaac9b375224cffca78fd
