// g++ key_sun.cpp -o key_sun.cpp.o -lSDL2 -lSDL2_image && ./key_sun.cpp.o
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <filesystem> // to check if the input file exist
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

char KEYBOARD_FILE[22] = "/dev/input/event0";

int BUTTON_WIDTH =	100;
int BUTTON_HIEGHT =	60;

bool SHOW_CTRL =	true;
bool SHOW_SHIFT =	true;
bool SHOW_SUPER =	true;
bool SHOW_ALT =		true;
bool SHOW_BORDERS = true;

using namespace std;

void imageToTexture(string image_path, SDL_Texture* &tex_temp, SDL_Renderer* renderer_temp)
{
	// this is to convert a string to a const char * to be able to use it in IMG_Load
	const char * image_path_converted = image_path.c_str();
	// making the surfaces from the images
	SDL_Surface* sur_temp =	IMG_Load(image_path_converted);
	// making the texture from the surfaces
	tex_temp = SDL_CreateTextureFromSurface(renderer_temp, sur_temp);
	// we do not need the surfaces from now so we freed them
	SDL_FreeSurface(sur_temp);
}

void print_help() 
{
	system("man -c ./key-sun.1");
	exit(0);
}

int main(int argc, char* argv[]) {

	// variables for handing arguments
	int i;
	string arg_next;
	string arg_next2;

	int X=0,Y=0; // position variables
	short int nButtons = 1; // this shows the number of buttons including the general button
	#include "arg.h"
	// the x,y positons and width and hieght on the window
	SDL_Rect rect_ctrl;
	SDL_Rect rect_shift;
	SDL_Rect rect_super;
	SDL_Rect rect_alt;
	if (SHOW_CTRL) 
	{
		rect_ctrl =				{(nButtons-1)*BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HIEGHT}; 
		nButtons++;
	}
	if (SHOW_SHIFT)
	{
		rect_shift =			{(nButtons-1)*BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HIEGHT}; 
		nButtons++;
	}
	if (SHOW_SUPER)
	{
		rect_super =			{(nButtons-1)*BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HIEGHT}; 
		nButtons++;
	}
	if (SHOW_ALT)
	{
		rect_alt =				{(nButtons-1)*BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HIEGHT}; 
		nButtons++;
	}
	SDL_Rect rect_letters =		{(nButtons-1)*BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HIEGHT};

	// again to update the position after the change in nButtons
	// the first include to control the boolean variables
	#include "arg.h"

	SDL_Window* window = NULL;
	if (!SHOW_BORDERS)
		window = SDL_CreateWindow( "keysun", X, Y, BUTTON_WIDTH*nButtons, BUTTON_HIEGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_UTILITY | SDL_WINDOW_ALWAYS_ON_TOP);
	else
		window = SDL_CreateWindow( "keysun", X, Y, BUTTON_WIDTH*nButtons, BUTTON_HIEGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_UTILITY | SDL_WINDOW_ALWAYS_ON_TOP);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	// initializing outsize the if statments to be able to use them
	SDL_Texture* tex_ctrl =		NULL;
	SDL_Texture* tex_ctrlP =	NULL;
	SDL_Texture* tex_shift =	NULL;
	SDL_Texture* tex_shiftP =	NULL;
	SDL_Texture* tex_super =	NULL;
	SDL_Texture* tex_superP =	NULL;
	SDL_Texture* tex_alt =		NULL;
	SDL_Texture* tex_altP =		NULL;
	if (SHOW_CTRL) 
	{
		// making the surfaces from the images
		imageToTexture("resources/ctrl.png", tex_ctrl, renderer);
		imageToTexture("resources/ctrlP.png", tex_ctrlP, renderer); // P is short for pressed
		// render the normal button at the beginning
		SDL_RenderCopy(renderer, tex_ctrl,  NULL, &rect_ctrl);
	}
	if (SHOW_SHIFT) 
	{
		// making the surfaces from the images
		imageToTexture("resources/shift.png", tex_shift, renderer);
		imageToTexture("resources/shiftP.png", tex_shiftP, renderer); // P is short for pressed
		// render the normal button at the beginning
		SDL_RenderCopy(renderer, tex_shift,  NULL, &rect_shift);
	}
	if (SHOW_SUPER) 
	{
		// making the surfaces from the images
		imageToTexture("resources/super.png", tex_super, renderer);
		imageToTexture("resources/superP.png", tex_superP, renderer); // P is short for pressed
		// render the normal button at the beginning
		SDL_RenderCopy(renderer, tex_super,  NULL, &rect_super);
	}
	if (SHOW_ALT) 
	{
		// making the surfaces from the images
		imageToTexture("resources/alt.png", tex_alt, renderer);
		imageToTexture("resources/altP.png", tex_altP, renderer); // P is short for pressed
		// render the normal button at the beginning
		SDL_RenderCopy(renderer, tex_alt,  NULL, &rect_alt);
	}
	// the general button that will apear if there is no letter pressed
	SDL_Texture* tex_general =	NULL;	imageToTexture("resources/general_button.png", tex_general, renderer);
	SDL_RenderCopy(renderer, tex_general,  NULL, &rect_letters);

	SDL_RenderPresent(renderer);

	// the boring part of initializing all the letters
	SDL_Texture* tex_A =		NULL;	imageToTexture("resources/letters/A.png", tex_A, renderer);
	SDL_Texture* tex_B =		NULL;	imageToTexture("resources/letters/B.png", tex_B, renderer);
	SDL_Texture* tex_C =		NULL;	imageToTexture("resources/letters/C.png", tex_C, renderer);
	SDL_Texture* tex_D =		NULL;	imageToTexture("resources/letters/D.png", tex_D, renderer);
	SDL_Texture* tex_E =		NULL;	imageToTexture("resources/letters/E.png", tex_E, renderer);
	SDL_Texture* tex_F =		NULL;	imageToTexture("resources/letters/F.png", tex_F, renderer);
	SDL_Texture* tex_G =		NULL;	imageToTexture("resources/letters/G.png", tex_G, renderer);
	SDL_Texture* tex_H =		NULL;	imageToTexture("resources/letters/H.png", tex_H, renderer);
	SDL_Texture* tex_I =		NULL;	imageToTexture("resources/letters/I.png", tex_I, renderer);
	SDL_Texture* tex_J =		NULL;	imageToTexture("resources/letters/J.png", tex_J, renderer);
	SDL_Texture* tex_K =		NULL;	imageToTexture("resources/letters/K.png", tex_K, renderer);
	SDL_Texture* tex_L =		NULL;	imageToTexture("resources/letters/L.png", tex_L, renderer);
	SDL_Texture* tex_M =		NULL;	imageToTexture("resources/letters/M.png", tex_M, renderer);
	SDL_Texture* tex_N =		NULL;	imageToTexture("resources/letters/N.png", tex_N, renderer);
	SDL_Texture* tex_O =		NULL;	imageToTexture("resources/letters/O.png", tex_O, renderer);
	SDL_Texture* tex_P =		NULL;	imageToTexture("resources/letters/P.png", tex_P, renderer);
	SDL_Texture* tex_Q =		NULL;	imageToTexture("resources/letters/Q.png", tex_Q, renderer);
	SDL_Texture* tex_R =		NULL;	imageToTexture("resources/letters/R.png", tex_R, renderer);
	SDL_Texture* tex_S =		NULL;	imageToTexture("resources/letters/S.png", tex_S, renderer);
	SDL_Texture* tex_T =		NULL;	imageToTexture("resources/letters/T.png", tex_T, renderer);
	SDL_Texture* tex_U =		NULL;	imageToTexture("resources/letters/U.png", tex_U, renderer);
	SDL_Texture* tex_V =		NULL;	imageToTexture("resources/letters/V.png", tex_V, renderer);
	SDL_Texture* tex_W =		NULL;	imageToTexture("resources/letters/W.png", tex_W, renderer);
	SDL_Texture* tex_X =		NULL;	imageToTexture("resources/letters/X.png", tex_X, renderer);
	SDL_Texture* tex_Y =		NULL;	imageToTexture("resources/letters/Y.png", tex_Y, renderer);
	SDL_Texture* tex_Z =		NULL;	imageToTexture("resources/letters/Z.png", tex_Z, renderer);
	SDL_Texture* tex_0 =		NULL;	imageToTexture("resources/letters/0.png", tex_0, renderer);
	SDL_Texture* tex_1 =		NULL;	imageToTexture("resources/letters/1.png", tex_1, renderer);
	SDL_Texture* tex_2 =		NULL;	imageToTexture("resources/letters/2.png", tex_2, renderer);
	SDL_Texture* tex_3 =		NULL;	imageToTexture("resources/letters/3.png", tex_3, renderer);
	SDL_Texture* tex_4 =		NULL;	imageToTexture("resources/letters/4.png", tex_4, renderer);
	SDL_Texture* tex_5 =		NULL;	imageToTexture("resources/letters/5.png", tex_5, renderer);
	SDL_Texture* tex_6 =		NULL;	imageToTexture("resources/letters/6.png", tex_6, renderer);
	SDL_Texture* tex_7 =		NULL;	imageToTexture("resources/letters/7.png", tex_7, renderer);
	SDL_Texture* tex_8 =		NULL;	imageToTexture("resources/letters/8.png", tex_8, renderer);
	SDL_Texture* tex_9 =		NULL;	imageToTexture("resources/letters/9.png", tex_9, renderer);
	SDL_Texture* tex_APOSTROPHE=NULL;	imageToTexture("resources/letters/APOSTROPHE.png", tex_APOSTROPHE, renderer);
	SDL_Texture* tex_BACKSLASH =NULL;	imageToTexture("resources/letters/BACKSLASH.png", tex_BACKSLASH, renderer);
	SDL_Texture* tex_BACKSPACE =NULL;	imageToTexture("resources/letters/BACKSPACE.png", tex_BACKSPACE, renderer);
	SDL_Texture* tex_COMMA =	NULL;	imageToTexture("resources/letters/COMMA.png", tex_COMMA, renderer);
	SDL_Texture* tex_DELETE =	NULL;	imageToTexture("resources/letters/DELETE.png", tex_DELETE, renderer);
	SDL_Texture* tex_DOT =		NULL;	imageToTexture("resources/letters/DOT.png", tex_DOT, renderer);
	SDL_Texture* tex_ENTER =	NULL;	imageToTexture("resources/letters/ENTER.png", tex_ENTER, renderer);
	SDL_Texture* tex_EQUAL =	NULL;	imageToTexture("resources/letters/EQUAL.png", tex_EQUAL, renderer);
	SDL_Texture* tex_ESC =		NULL;	imageToTexture("resources/letters/ESC.png", tex_ESC, renderer);
	SDL_Texture* tex_GRAVE =	NULL;	imageToTexture("resources/letters/GRAVE.png", tex_GRAVE, renderer);
	SDL_Texture* tex_LEFTBRACE =NULL;	imageToTexture("resources/letters/LEFTBRACE.png", tex_LEFTBRACE, renderer);
	SDL_Texture* tex_MINUS =	NULL;	imageToTexture("resources/letters/MINUS.png", tex_MINUS, renderer);
	SDL_Texture* tex_RIGHTBRACE=NULL;	imageToTexture("resources/letters/RIGHTBRACE.png", tex_RIGHTBRACE, renderer);
	SDL_Texture* tex_SEMICOLON =NULL;	imageToTexture("resources/letters/SEMICOLON.png", tex_SEMICOLON, renderer);
	SDL_Texture* tex_SLASH =	NULL;	imageToTexture("resources/letters/SLASH.png", tex_SLASH, renderer);
	SDL_Texture* tex_SPACE =	NULL;	imageToTexture("resources/letters/SPACE.png", tex_SPACE, renderer);
	SDL_Texture* tex_TAB =		NULL;	imageToTexture("resources/letters/TAB.png", tex_TAB, renderer);

	int keyboard_input = open(KEYBOARD_FILE, O_RDONLY);
	if (keyboard_input == -1) {
		cout << "Cannot open " << KEYBOARD_FILE << endl;
		return 1;
	}

	SDL_Event sdl_input; // the input from SDL2 (the input when the application is in focus)
	struct input_event global_keyboard; // the global input from the keyboard input file
	bool close = false; // if set to true the loop exit (to close the app)
	while (!close)
	{
		ssize_t keyboard_bytesRead = read(keyboard_input, &global_keyboard, sizeof(global_keyboard));
		if (keyboard_bytesRead == (ssize_t)-1) {
			cout << "Failed to read from " << KEYBOARD_FILE << ". but it was opened successfuly" << endl;
			return 1;
		}

		// checking if the type is pressed or released
		if (global_keyboard.type == EV_KEY)
		{

			if (global_keyboard.value == 0)
			{
				switch (global_keyboard.code)
				{
					case KEY_RIGHTCTRL:
					case KEY_LEFTCTRL:		if (SHOW_CTRL) SDL_RenderCopy(renderer, tex_ctrl,  NULL, &rect_ctrl); break;
					case KEY_RIGHTSHIFT:
					case KEY_LEFTSHIFT:		if (SHOW_SHIFT) SDL_RenderCopy(renderer, tex_shift,  NULL, &rect_shift); break;
					case KEY_LEFTMETA:		if (SHOW_SUPER) SDL_RenderCopy(renderer, tex_super,  NULL, &rect_super); break;
					case KEY_RIGHTALT:
					case KEY_LEFTALT:		if (SHOW_ALT) SDL_RenderCopy(renderer, tex_alt,  NULL, &rect_alt); break;
					default: SDL_RenderCopy(renderer, tex_general,  NULL, &rect_letters);
				}
			}
			if (global_keyboard.value == 1)
			{
				switch (global_keyboard.code)
				{
					case KEY_RIGHTCTRL:
					case KEY_LEFTCTRL:		if (SHOW_CTRL) SDL_RenderCopy(renderer, tex_ctrlP,  NULL, &rect_ctrl); break;
					case KEY_RIGHTSHIFT:
					case KEY_LEFTSHIFT:		if (SHOW_SHIFT) SDL_RenderCopy(renderer, tex_shiftP,  NULL, &rect_shift); break;
					case KEY_LEFTMETA:		if (SHOW_SUPER) SDL_RenderCopy(renderer, tex_superP,  NULL, &rect_super); break;
					case KEY_RIGHTALT:
					case KEY_LEFTALT:		if (SHOW_ALT) SDL_RenderCopy(renderer, tex_altP,  NULL, &rect_alt); break;
					// the boring part of checking all the letters
					case KEY_A:				SDL_RenderCopy(renderer, tex_A,			NULL, &rect_letters); break;
					case KEY_B:				SDL_RenderCopy(renderer, tex_B,			NULL, &rect_letters); break;
					case KEY_C:				SDL_RenderCopy(renderer, tex_C,			NULL, &rect_letters); break;
					case KEY_D:				SDL_RenderCopy(renderer, tex_D,			NULL, &rect_letters); break;
					case KEY_E:				SDL_RenderCopy(renderer, tex_E,			NULL, &rect_letters); break;
					case KEY_F:				SDL_RenderCopy(renderer, tex_F,			NULL, &rect_letters); break;
					case KEY_G:				SDL_RenderCopy(renderer, tex_G,			NULL, &rect_letters); break;
					case KEY_H:				SDL_RenderCopy(renderer, tex_H,			NULL, &rect_letters); break;
					case KEY_I:				SDL_RenderCopy(renderer, tex_I,			NULL, &rect_letters); break;
					case KEY_J:				SDL_RenderCopy(renderer, tex_J,			NULL, &rect_letters); break;
					case KEY_K:				SDL_RenderCopy(renderer, tex_K,			NULL, &rect_letters); break;
					case KEY_L:				SDL_RenderCopy(renderer, tex_L,			NULL, &rect_letters); break;
					case KEY_M:				SDL_RenderCopy(renderer, tex_M,			NULL, &rect_letters); break;
					case KEY_N:				SDL_RenderCopy(renderer, tex_N,			NULL, &rect_letters); break;
					case KEY_O:				SDL_RenderCopy(renderer, tex_O,			NULL, &rect_letters); break;
					case KEY_P:				SDL_RenderCopy(renderer, tex_P,			NULL, &rect_letters); break;
					case KEY_Q:				SDL_RenderCopy(renderer, tex_Q,			NULL, &rect_letters); break;
					case KEY_R:				SDL_RenderCopy(renderer, tex_R,			NULL, &rect_letters); break;
					case KEY_S:				SDL_RenderCopy(renderer, tex_S,			NULL, &rect_letters); break;
					case KEY_T:				SDL_RenderCopy(renderer, tex_T,			NULL, &rect_letters); break;
					case KEY_U:				SDL_RenderCopy(renderer, tex_U,			NULL, &rect_letters); break;
					case KEY_V:				SDL_RenderCopy(renderer, tex_V,			NULL, &rect_letters); break;
					case KEY_W:				SDL_RenderCopy(renderer, tex_W,			NULL, &rect_letters); break;
					case KEY_X:				SDL_RenderCopy(renderer, tex_X,			NULL, &rect_letters); break;
					case KEY_Y:				SDL_RenderCopy(renderer, tex_Y,			NULL, &rect_letters); break;
					case KEY_Z:				SDL_RenderCopy(renderer, tex_Z,			NULL, &rect_letters); break;
					case KEY_0:				SDL_RenderCopy(renderer, tex_0,			NULL, &rect_letters); break;
					case KEY_1:				SDL_RenderCopy(renderer, tex_1,			NULL, &rect_letters); break;
					case KEY_2:				SDL_RenderCopy(renderer, tex_2,			NULL, &rect_letters); break;
					case KEY_3:				SDL_RenderCopy(renderer, tex_3,			NULL, &rect_letters); break;
					case KEY_4:				SDL_RenderCopy(renderer, tex_4,			NULL, &rect_letters); break;
					case KEY_5:				SDL_RenderCopy(renderer, tex_5,			NULL, &rect_letters); break;
					case KEY_6:				SDL_RenderCopy(renderer, tex_6,			NULL, &rect_letters); break;
					case KEY_7:				SDL_RenderCopy(renderer, tex_7,			NULL, &rect_letters); break;
					case KEY_8:				SDL_RenderCopy(renderer, tex_8,			NULL, &rect_letters); break;
					case KEY_9:				SDL_RenderCopy(renderer, tex_9,			NULL, &rect_letters); break;
					case KEY_APOSTROPHE:	SDL_RenderCopy(renderer, tex_APOSTROPHE,NULL, &rect_letters); break;
					case KEY_BACKSLASH:		SDL_RenderCopy(renderer, tex_BACKSLASH,	NULL, &rect_letters); break;
					case KEY_BACKSPACE:		SDL_RenderCopy(renderer, tex_BACKSPACE,	NULL, &rect_letters); break;
					case KEY_COMMA:			SDL_RenderCopy(renderer, tex_COMMA,		NULL, &rect_letters); break;
					case KEY_DELETE:		SDL_RenderCopy(renderer, tex_DELETE,	NULL, &rect_letters); break;
					case KEY_DOT:			SDL_RenderCopy(renderer, tex_DOT,		NULL, &rect_letters); break;
					case KEY_ENTER:			SDL_RenderCopy(renderer, tex_ENTER,		NULL, &rect_letters); break;
					case KEY_EQUAL:			SDL_RenderCopy(renderer, tex_EQUAL,		NULL, &rect_letters); break;
					case KEY_ESC:			SDL_RenderCopy(renderer, tex_ESC,		NULL, &rect_letters); break;
					case KEY_GRAVE:			SDL_RenderCopy(renderer, tex_GRAVE,		NULL, &rect_letters); break;
					case KEY_LEFTBRACE:		SDL_RenderCopy(renderer, tex_LEFTBRACE,	NULL, &rect_letters); break;
					case KEY_MINUS:			SDL_RenderCopy(renderer, tex_MINUS,		NULL, &rect_letters); break;
					case KEY_RIGHTBRACE:	SDL_RenderCopy(renderer, tex_RIGHTBRACE,NULL, &rect_letters); break;
					case KEY_SEMICOLON:		SDL_RenderCopy(renderer, tex_SEMICOLON,	NULL, &rect_letters); break;
					case KEY_SLASH:			SDL_RenderCopy(renderer, tex_SLASH,		NULL, &rect_letters); break;
					case KEY_SPACE:			SDL_RenderCopy(renderer, tex_SPACE,		NULL, &rect_letters); break;
					case KEY_TAB:			SDL_RenderCopy(renderer, tex_TAB,		NULL, &rect_letters); break;

					default: cout << "code:" << global_keyboard.code << endl;
				}
			}

			SDL_RenderPresent(renderer);


			while ( SDL_PollEvent( &sdl_input ) != 0 ) 
			{
				// checking if you want to close the app
				if (sdl_input.type == SDL_QUIT) close =true;
			}
		}
	}


	SDL_Quit();
	cout << "closed normally" << endl;
	return 0;
}
