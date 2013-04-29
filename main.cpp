/*
 * SDL Tic Tac Toe AI (to be implemented)
 * Author: Tudor Marcu
 * Copyright (C)  Tudor Marcu 2013. All rights reserved.
 */


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

bool player = true; /* True = X False = O Player */
	
int handle_button(int *, int *, SDL_Rect *, short int *);
int check_win(short int *);

int main(int argc, char *argv[]) 
{
	SDL_Surface *surface;
	SDL_Event event;
	SDL_Rect squares[9] = {{0, 0, 130, 130}, {140, 0, 130, 130}, {280, 0, 130, 130},
				{0, 140, 130, 130}, {140, 140, 130, 130}, {280, 140, 130, 130},
				{0, 280, 130, 130}, {140, 280, 130, 130}, {280, 280, 130, 130}};
	SDL_Rect imagepos = {0, 0, 0, 0};
	SDL_Surface *imagex;
	SDL_Surface *imageo;
	short int states[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int valid = 0;
	int i;
	int ret;
	int mx, my;

	bool done = false;

	SDL_Init(SDL_INIT_VIDEO);

	imagex = SDL_LoadBMP("x.bmp");
	imageo = SDL_LoadBMP("o.bmp");
	if (imagex == NULL || imageo == NULL) {
		fprintf(stderr, "Could not load image: %s\n", SDL_GetError());
		return -1;
	}

	/* Control window position */
	putenv(strdup("SDL_VIDEO_CENTERED=1"));
 
	surface = SDL_SetVideoMode(410, 410, 16, SDL_SWSURFACE);
	if (!surface) {
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		return -1;
	}

	SDL_WM_SetCaption("TICTACTOE", "Can't Beat Me");

	/* Fill screen and then put white squares on top */
	SDL_FillRect(surface, &surface->clip_rect, SDL_MapRGB(surface->format, 0x0, 0x0, 0x0));
	for (i = 0; i < 9; i++)
		SDL_FillRect(surface, &squares[i], 0xFFFFFF);

	/* Update screen buffer */
	SDL_Flip(surface);
	SDL_Surface *image = NULL;
	while(!done) {
		while(SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					done = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					valid = handle_button(&mx, &my, &imagepos, states);
					if (valid == 0)
						player = !player;
					break;
			}
		}
		if (imagepos.x != 0 && valid == 0) {
			image = player ? imageo : imagex;
			if (SDL_BlitSurface(image, NULL, surface, &imagepos) != 0) {
				fprintf(stderr, "Failed to blit image: %s\n", SDL_GetError());
				return -1;
			}
			SDL_Flip(surface);
		}
		ret = check_win(states);
		if (ret == 1) {
			printf("Player 1 won\n");
			done = true;
		} else if (ret == 2) {
			printf("Player 2 won\n");
			done = true;
		} else if (ret == 0){
			printf("Draw!\n");
			done = true;
		} else {
			continue;
		}
	}

	SDL_Quit();

	return 0;
}

int check_win(short int *state)
{
	int i;

	/* Player one won -> 1 + 1 + 1 */
	if ((state[0] + state[1] + state[2] == 3) ||
		(state[3] + state[4] + state[5] == 3) ||
		(state[6] + state[7] + state[8] == 3) ||
		(state[0] + state[3] + state[6] == 3) ||
		(state[1] + state[4] + state[7] == 3) ||
		(state[2] + state[5] + state[8] == 3) ||
		(state[0] + state[4] + state[8] == 3) ||
		(state[2] + state[4] + state[6] == 3)) {
			return 1;
	}

	if ((state[0] + state[1] + state[2] == 30) ||
		(state[3] + state[4] + state[5] == 30) ||
		(state[6] + state[7] + state[8] == 30) ||
		(state[0] + state[3] + state[6] == 30) ||
		(state[1] + state[4] + state[7] == 30) ||
		(state[2] + state[5] + state[8] == 30) ||
		(state[0] + state[4] + state[8] == 30) ||
		(state[2] + state[4] + state[6] == 30)) {
			return 2;
	}
	
	for (i = 0; i < 9; i++) {
		if (state[i] == 0)
			return -1;
	}

	return 0;
}

/* Set the x/y coordinate for the X and O images to be places based on mouse */
int handle_button(int *x, int *y, SDL_Rect *pos, short int *state)
{	
	SDL_GetMouseState(x, y);
	if (*x < 130 && *y < 130) { /* First row */
		pos->x = 50;
		pos->y = 50;
		pos->h = 0;
		pos->w = 0;
		if (state[0] == 0) {
			state[0] = player ? 1 : 10;
			return 0;
		} else return -1;
	} else if (*x > 140 && *x < 270 && *y < 130) {
		pos->x = 190;
		pos->y = 50;
		pos->h = 0;
		pos->w = 0;
		if (state[1] == 0) {
			state[1] = player ? 1 : 10;
			return 0;
		} else return -1;
	} else if (*x > 280 && *x < 410 && *y < 130) {
		pos->x = 330;
		pos->y = 50;
		pos->h = 0;
		pos->w = 0;
		if (state[2] == 0) {
			state[2] = player ? 1 : 10;
			return 0;
		} else return -1;
	} else if (*x < 130 && *y > 130 && *y < 270) { /* Second Row */
		pos->x = 50;
		pos->y = 190;
		pos->h = 0;
		pos->w = 0;
		if (state[3] == 0) {
			state[3] = player ? 1 : 10;
			return 0;
		} else return -1;
	} else if (*x > 140 && *x < 270 && *y > 130 && *y < 270) {
		pos->x = 190;
		pos->y = 190;
		pos->h = 0;
		pos->w = 0;
		if (state[4] == 0) {
			state[4] = player ? 1 : 10;
			return 0;
		} else return -1;
	} else 	if (*x > 280 && *x < 410 && *y > 130 && *y < 270) {
		pos->x = 330;
		pos->y = 190;
		pos->h = 0;
		pos->w = 0;
		if (state[5] == 0) {
			state[5] = player ? 1 : 10;
			return 0;
		} else return -1;
	} else if (*x < 130 && *y > 280 && *y < 410) { /* Third Row */
		pos->x = 50;
		pos->y = 330;
		pos->h = 0;
		pos->w = 0;
		if (state[6] == 0) {
			state[6] = player ? 1 : 10;
			return 0;
		} else return -1;
	} else if (*x > 140 && *x < 270 && *y > 280 && *y < 410) {
		pos->x = 190;
		pos->y = 330;
		pos->h = 0;
		pos->w = 0;
		if (state[7] == 0) {
			state[7] = player ? 1 : 10;
			return 0;
		} else return -1;
	} else if (*x > 280 && *x < 410 && *y > 280 && *y < 410) {
		pos->x = 330;
		pos->y = 330;
		pos->h = 0;
		pos->w = 0;
		if (state[8] == 0) {
			state[8] = player ? 1 : 10;
			return 0;
		} else return -1;
	}
	return -1;
}
