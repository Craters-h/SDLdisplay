#include "sdldisplay.h"
std::string get_address();
void main_menu();
void get_address(Picture&);
void set_size(Picture&);
void before_display(const Picture&);
void display(Picture&);
void after_display(Picture&);
inline void display_error() { std::cout << "Can't display picture:" << SDL_GetError() << std::endl; return;}
const int default_length = 640;
const int default_width = 480;
int main(int argc, char** argv)
{
	Picture picture("\0", (int)0, (int)0);
	while (1)
	{
		main_menu();
		get_address(picture);
		set_size(picture);
		before_display(picture);
		display(picture);
		after_display(picture);
	}
}
void main_menu()
{
	std::cout << "SDLdisplay version 0.01"<< std::endl;
    std::cout << "Support BMP picture files." << std::endl;
}
void get_address(Picture& picture)
{
	std::string address;
    while (1)
    {
		std::cout << "Please enter the address of the image." << std::endl;
		std::cin >> address;
		std::ifstream file(address.c_str());
		if (file.good() == false)
		{
			std::cout << "File not found, please try again." << std::endl;
			continue;
		}
		else
		{
			picture.set_address(address);
			break;
		}
	}
}
void set_size(Picture& picture)
{
	int length = 0;
	int width = 0;
	while (1)
    {
    	std::cout << "Please enter the size of the image.(Format:length width)" << std::endl;
    	std::cout << "If you enter length 0 or width 0, size will be set to default." << std::endl;
		std::cin >> length >> width;
		if (length < 0 || width < 0)
		{
			std::cout << "Please enter valid values." << std::endl;
			continue;
		}
		else
		{
			picture.set_size(length, width);
			break;
		}
	}
}
void before_display(const Picture& picture)
{
	std::cout << "The picture is about to be displayed, you can exit by clicking the mouse." << std::endl;
}
void display(Picture& picture)
{
	std::string address = "SDLdisplay" + picture.get_address();
	if (picture.get_length() == 0 || picture.get_width() == 0)
    {
		picture.set_size(default_width, default_length);
    }
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
        display_error();
    }
    SDL_Window* display_win = SDL_CreateWindow(address.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, picture.get_length(), picture.get_width(), SDL_WINDOW_SHOWN);
    if (display_win == nullptr)
    {
		display_error();
    }
    SDL_Renderer* display_ren = SDL_CreateRenderer(display_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (display_ren == nullptr)
    {
		display_error();
    }
    std::string type = picture.get_type();
    for (int a = 0; a <= type.length() - 1; a++)
    {
		type[a] = tolower(type[a]);
    }
    if (type == "bmp")
    {
		SDL_Surface* display_sur = SDL_LoadBMP(picture.get_address().c_str());
		if (display_sur == nullptr)
		{
			display_error();
		}
		SDL_Texture* display_tex = SDL_CreateTextureFromSurface(display_ren, display_sur);
		SDL_RenderClear(display_ren); //Clear screen.
		SDL_RenderCopy(display_ren, display_tex, NULL, NULL); //Copy the content to the renderer.
		SDL_RenderPresent(display_ren); //Update screen content.
		SDL_Event mouse_event;
		bool no_break = true;
		while (no_break)
		{
			while (SDL_PollEvent(&mouse_event))
			{
				if (mouse_event.type == SDL_MOUSEBUTTONDOWN)
				{
					no_break = false;
				}
			}
		}
		SDL_FreeSurface(display_sur);
		SDL_DestroyTexture(display_tex);
		SDL_DestroyRenderer(display_ren);
		SDL_DestroyWindow(display_win);
	}
	SDL_Quit();
}
void after_display(Picture& picture)
{
	if (picture.get_length() == default_length && picture.get_width() == default_width)
    {
		picture.set_size(0, 0);
    }
}
std::string sep_type(const std::string& address)
{
	return address.substr(address.find_last_of('.') + 1);
}
Picture::Picture(const std::string& address, const int& length, const int& width)
{
	this->address = address;
	this->type = sep_type(address);
	this->length = length;
	this->width = width;
}
Picture::Picture(const std::string& address, const std::string& type, const int& length, const int& width)
{
	this->address = address;
	this->type = type;
	this->length = length;
	this->width = width;
}
void Picture::set_address(const std::string& address)
{
	this->address = address;
	this->type = sep_type(address);
}
void Picture::set_size(const int& length, const int& width)
{
	this->length = length;
	this->width = width;
}
std::string Picture::get_address()
{
	return this->address;
}
std::string Picture::get_type()
{
	return this->type;
}
int Picture::get_length()
{
	return this->length;
}
int Picture::get_width()
{
	return this->width;
}
Picture::~Picture()
{
	;
}