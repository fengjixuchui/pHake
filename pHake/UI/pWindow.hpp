#ifndef _PWINDOW_HPP_
#define _PWINDOW_HPP_

#include "pButton.hpp"
#include "pItem.hpp"
#include "pList.hpp"
#include "pMouse.hpp"

#include <SFML/Graphics.hpp>
#pragma comment (lib, "Dwmapi.lib")

class pWindow
{
private:
	sf::RenderWindow window_;
	sf::Font		 font_;
	pMouse			 mouse_;

public:
	pList			 list_;

	void Create();
	void Loop();

private:
	void FixSize();
};
#endif