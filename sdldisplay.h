#ifndef SDLDISPLAY_USING_NOW
#define SDLDISPLAY_USING_NOW
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include "SDL2/SDL.h"
std::string sep_type(const std::string&); //separate file type from address
class Picture
{
	private:
		std::string address;
		std::string type;
		int length;
		int width;
		void set_type(std::string);
	public:
		Picture(const std::string&, const int&, const int&);
		Picture(const std::string&,const std::string&, const int&, const int&);
		void set_address(const std::string&);
		void set_size(const int&, const int&);
		std::string get_address();
		std::string get_type();
		int get_length();
		int get_width();
		~Picture();
};
#endif