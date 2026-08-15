#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_FRect rect = {
	.x = 120,
	.y = 100,
	.w = 50,
	.h = 50,
};
int v_x = 4;
int v_y = 2;
Uint64 ticks;
Uint64 prev_time;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("Init failed\n");
		return SDL_APP_FAILURE;
	};
	if (!SDL_CreateWindowAndRenderer("Test", 1000, 1000, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		printf("Window failed\n");
		return SDL_APP_FAILURE;
	}	
	SDL_SetRenderLogicalPresentation(renderer, 1000, 1000, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	prev_time = SDL_GetTicks();
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	ticks += SDL_GetTicks() - prev_time;	
	while (ticks >= 10) {
		rect.x += v_x;
		rect.y += v_y;
		ticks -= 10;
	}

	prev_time = SDL_GetTicks();
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
	if (rect.x + rect.w >= 1000 && v_x > 0) {
		v_x *= -1;
	} else if (rect.x <= 0 && v_x < 0) {
		v_x *= -1;
	}
	if (rect.y + rect.h >= 1000 && v_y > 0) {
		v_y *= -1;
	} else if (rect.y <= 0 && v_y < 0) {
		v_y *= -1;
	}

	printf("Prev time: %lu\r", prev_time);
	fflush(stdout);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {

}


