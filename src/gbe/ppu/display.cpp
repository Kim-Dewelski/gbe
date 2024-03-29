#include"display.h"

void gbe::display_t::create_window(){
	this->window_handle 	= SDL_CreateWindow("gbe", 0, 0, 160, 144, 
		SDL_WINDOW_SHOWN 	|
		SDL_WINDOW_OPENGL);
	
	this->surface_handler 	= SDL_GetWindowSurface(this->window_handle);
	this->renderer_handle	= SDL_GetRenderer(this->window_handle);
	SDL_SetRenderDrawColor(this->renderer_handle, 255, 255, 255, 255);
	SDL_RenderClear(this->renderer_handle);
	SDL_RenderPresent(this->renderer_handle);

	SDL_Rect rect;
	int col = 0xFFFFFFFF;
	rect.x=0;rect.y=0;rect.w=160;rect.h=144;
	SDL_FillRect(this->surface_handler, &rect, col);
	SDL_UpdateWindowSurface(this->window_handle);
}

int gbe::display_t::determine_colour(byte bit1, byte bit2){
	return this->colour_array[(bit1<<1)|bit2];
}
int gbe::display_t::determine_colour(byte bits){
	return this->colour_array[bits];
}

void gbe::display_t::draw_row_8(int x, int y, byte row[8]){
	if(y >= SCR_H)
		return;
	int* pixel_buffer = reinterpret_cast<int*>(surface_handler->pixels)+x+y*SCR_W;
	int* end_of_buffer = pixel_buffer+SCR_W;
	for(int i = 0; i < 8; ++i, ++pixel_buffer){
		if(pixel_buffer >= end_of_buffer || x+i >= SCR_W)
			break;
		*pixel_buffer = this->colour_array[row[i]&0b11];
	}
}

void gbe::display_t::render_buffer(){
	//auto& surface = *this->surface_handler;
	//for(int i = 0; i < SCR_W*SCR_H; ++i){	
	//	((int*)surface.pixels)[i] = sprite_buffer[i] ? sprite_buffer[i] : background_buffer[i];
	//}
	SDL_UpdateWindowSurface(this->window_handle);
	//SDL_RenderPresent(this->renderer_handle);
}