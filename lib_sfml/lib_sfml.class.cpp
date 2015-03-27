/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_sfml.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/26 15:07:24 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/27 16:11:06 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_sfml.class.hpp"

Graphic::Graphic( void ) :	_key(NULL) {}

Graphic::Graphic( Graphic const & src ) {
	*this = src;
}

Graphic & Graphic::operator=( Graphic const & rhs ) {
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		// this->_window = rhs.getWindow();
		this->_x = rhs.getX();
		this->_y = rhs.getY();
		this->_key = rhs.getKey();
		this->_map = rhs.getMap();
	}
	return (*this);
}

Graphic::~Graphic( void ) {}



void	Graphic::init( int ac, char** av, int x, int y, char *title, char **map ) {
	this->_x = x;
	this->_y = y;
	this->_name = title;
	this->_map = map;
	this->_key = new std::vector<int>;
	static_cast<void>(ac);
	static_cast<void>(av);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	this->_event = new sf::Event();

	this->_window = new sf::RenderWindow(sf::VideoMode(y * 10, x * 10), title, sf::Style::Default, settings);

	this->_queue = new sf::CircleShape(5.f);
	this->_queue->setFillColor(sf::Color::Green);

	this->_head = new sf::CircleShape(5.f);
	this->_head->setFillColor(sf::Color::Red);

	this->_fruit = new sf::CircleShape(5.f, 4);
	this->_fruit->setFillColor(sf::Color::Cyan);

	this->_wall = new sf::CircleShape(5.f);
	this->_wall->setFillColor(sf::Color::Green);
}

void	Graphic::close( void ) {
	this->_window->clear();
	this->_window->close();
}

void	Graphic::keyboard( void ) {
	this->_window->pollEvent(*this->_event);
	if (this->_event->type == sf::Event::KeyPressed)
	{
		if (this->_event->key.code == sf::Keyboard::Left)
			this->_key->push_back(LEFT);
		else if (this->_event->key.code == sf::Keyboard::Right)
			this->_key->push_back(RIGHT);
		else if (this->_event->key.code == sf::Keyboard::Up)
			this->_key->push_back(UP);
		else if (this->_event->key.code == sf::Keyboard::Down)
			this->_key->push_back(DOWN);
		else if (this->_event->key.code == sf::Keyboard::Escape)
			this->_key->push_back(27);
	}
}

void	Graphic::render_scene( void ) {
	keyboard();
	this->_window->clear(sf::Color::Black);
	for (int y = 0; y < this->_y; ++y)
	{
		for (int x = 0; x < this->_x; ++x)
		{
			if (this->_map[y][x] == WALL)
			{
				this->_wall->setPosition(x * 10.f, y * 10.f);
				this->_window->draw(*this->_wall);
			}
			else if (this->_map[y][x] == HEAD)
			{
				this->_head->setPosition(x * 10.f, y * 10.f);
				this->_window->draw(*this->_head);
			}
			else if (this->_map[y][x] == QUEUE)
			{
				this->_queue->setPosition(x * 10.f, y * 10.f);
				this->_window->draw(*this->_queue);
			}
			else if (this->_map[y][x] == FRUIT)
			{
				this->_fruit->setPosition(x * 10.f, y * 10.f);
				this->_window->draw(*this->_fruit);
			}
		}
	}
	this->_window->display();
	keyboard();
}

// void	Graphic::render_scene( void ) {
// 	int	x;
// 	int	y;
// 	int	state = 1;

// 	keyboard();	// maybe put keyboard in the for ?
// 	werase(this->_window);
// 	wattron(this->_window, COLOR_PAIR(1));
// 	for (y = 0; y < this->_y; y++)
// 	{
// 		for (x = 0; x < this->_x; x++)
// 		{
// 			if (state != 1 && this->_map[y][x] == WALL)
// 			{
// 				wattroff(this->_window, COLOR_PAIR(state));
// 				wattron(this->_window, COLOR_PAIR(1));
// 				state = 1;
// 			}
// 			else if (state != 3 && this->_map[y][x] == FRUIT)
// 			{
// 				wattroff(this->_window, COLOR_PAIR(state));
// 				wattron(this->_window, COLOR_PAIR(3));
// 				state = 3;
// 			}
// 			else if (state != 2 && (this->_map[y][x] == QUEUE || this->_map[y][x] == HEAD))
// 			{
// 				wattroff(this->_window, COLOR_PAIR(state));
// 				wattron(this->_window, COLOR_PAIR(2));
// 				state = 2;
// 			}
// 			mvwprintw(this->_window, y, x, "%c", this->_map[y][x]);
// 		}
// 	}
// 	wrefresh(this->_window);
// }


std::vector<int> **Graphic::get_touch_list( void ) { return (&this->_key); }

char				*Graphic::getName( void ) const { return (this->_name); }

// WINDOW				*Graphic::getWindow( void ) const { return (this->_window); }

int					Graphic::getX( void ) const { return (this->_x); }

int					Graphic::getY( void ) const { return (this->_y); }

std::vector<int>	*Graphic::getKey( void ) const {return (this->_key); }

char				**Graphic::getMap( void ) const {return (this->_map); }

extern "C"	Api				*newObject( void )
{
	return (new Graphic());
}
