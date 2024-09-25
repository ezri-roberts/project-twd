#include <stdbool.h>
#include "game.h"
#include "assets.h"
#include "log.h"
#include "canvas.h"
#include "wordlist.h"
#include "text_input.h"

static Game game = {};
static bool initialized = false;

static WordList list;
static TextInput input;

void game_init() {

	if (initialized) {
		log_error("Game already initialized.");
		return;
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(1280, 720, "Project Tower Defense");
	SetTargetFPS(60);

	game.dt = 0.0f;
	game.canvas = canvas_init(480, 270, TEXTURE_FILTER_POINT);
	game.ui_canvas = canvas_init(1920, 1080, TEXTURE_FILTER_BILINEAR);

	assets_init();

	list = wordlist_init();
	input = text_input_init(list.easy);

	initialized = true;
	log_info("Game initialized.");
}

void game_shutdown() {

	if (!initialized) {
		log_error("Game not initialized.");
		return;
	}

	canvas_destroy(&game.canvas);
	assets_destory();
	CloseWindow();

	initialized = false;
	log_info("Game shutdown.");
}

void game_update() {

	if (!initialized) {
		log_error("Game not initialized.");
		return;
	}

	while (!WindowShouldClose()) {
		game.dt = GetFrameTime();	// Update delta time.
		text_input_update(&input);
		canvas_update(&game.canvas);
		canvas_update(&game.ui_canvas);
		game_draw();
	}

}

void game_draw() {

	if (!initialized) {
		log_error("Game not initialized.");
		return;
	}

	BeginDrawing();
	ClearBackground(WHITE);

	canvas_begin(&game.canvas);
	// Draw to canvas.
	canvas_end();

	canvas_begin(&game.ui_canvas);
	// Draw to canvas.
	text_input_draw(&input);
	canvas_end();

	canvas_draw(&game.canvas);
	canvas_draw(&game.ui_canvas);
	EndDrawing();
}