// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   api.class.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/23 16:00:39 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/23 16:00:40 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef API_CLASS_HPP
# define API_CLASS_HPP
# include <stdexcept>
# include <vector>
# include <string>
# include <iostream>
# include <strings.h>

# define WALL		'#'
# define HEAD		'*'
# define QUEUE		'o'
# define FRUIT		'@'
# define SPECIAL	'?'

# define UP			65
# define DOWN		66
# define LEFT		68
# define RIGHT		67
# define ECHAP		27
# define ONE		49
# define TWO		50
# define THREE		51
# define SPACE		32

class	Api {
	public:
		Api( void );
		virtual ~Api( void );

		virtual void				init( int ac, char** av, int x, int y, char *title, char **map ) = 0;
		virtual void				close( void ) = 0;
		virtual void				render_scene( void ) = 0;
		virtual std::vector<int>	**get_touch_list( void ) = 0;

	private:
		Api( Api const & src );
		Api & operator=( Api const & rhs );
};

#endif
