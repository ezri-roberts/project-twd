#define MAXWIDTH 128
#define MAXHEIGHT 128

#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

enum TileTypes {
    GROUND_FLAT = 1,
    GROUND_ELEVATE = 2,
    GROUND_SHADOW = 3,
    WATER = 4,
    WATER_ROCK1 = 5,
    WATER_ROCK2 = 6,
    WATER_ROCK3 = 7,
	WATER_ROCK4 = 8,
	BRIDGE = 9
};

typedef struct {
	int *asset_ptr;
	int tiles[128][128];
} Tilemap;


typedef struct {
	int difficulty;
	int waves;
	Tilemap tilemap;
} Scene;

<<<<<<< HEAD
=======
Scene scene_initialize(int difficulty, const char* path);
void scene_draw(Scene *scene);
void tileval_from_file(const char *filename, int (*arr)[TILEMAP_WIDTH]);
void scene_randomize(Scene *scene);

>>>>>>> d19befc1953f64d5e9afaac9b375224cffca78fd
#endif
