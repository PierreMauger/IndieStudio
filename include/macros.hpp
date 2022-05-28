/*
** EPITECH PROJECT, 2022
** macros.hpp
** File description:
** macros
*/

#ifndef MACROS_HPP
	#define MACROS_HPP

	#ifdef _WIN32
		#define CAST(type, ...) type{__VA_ARGS__}
	#else
		#define CAST(type, ...) (type){__VA_ARGS__}
	#endif

#endif // MACROS_HPP
