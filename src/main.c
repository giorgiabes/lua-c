#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

// #include "../lib/lua/src/lua.h"
// #include "../lib/lua/src/lualib.h"
// #include "../lib/lua/src/lauxlib.h"


#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int is_running = FALSE;
int last_frame_time;

struct player {
	float x;
	float y;
	float width;
	float height;
} player;

int initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return FALSE;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		fprintf(stderr, "Error creating SDL window.\n");
		return FALSE;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL renderer.\n");
		return FALSE;
	}
	return TRUE;
}

void process_input(void) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT: {
			is_running = FALSE;
			break;
		}
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_running = FALSE;
			break;
		}
	}
}

void setup(void) {
	player.x = 20;
	player.y = 20;
	player.width = 10;
	player.height = 10;
}

void update(void) {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TIME_LENGTH));
	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
	last_frame_time = SDL_GetTicks();
	player.x += 100 * delta_time;
	player.y += 50 * delta_time;
}

void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// draw the player at position x, y
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect player_rect = {
		(int)player.x,
		(int)player.y, 
		(int)player.width, 
		(int)player.height
	};
	SDL_RenderFillRect(renderer, &player_rect);
	
	SDL_RenderPresent(renderer);
}

void destroy_window(void) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char *argv[]) {
	is_running = initialize_window();

	setup();

	while (is_running) {
		process_input();
		update();
		render();
	}

	destroy_window();
	return 0;
}
