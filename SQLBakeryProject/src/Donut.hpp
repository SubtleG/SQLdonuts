/*
 * Donut.hpp
 *
 *  Created on: Dec 12, 2017
 *      Author: BryceX1
 */

#ifndef DONUT_HPP_
#define DONUT_HPP_
#include <string>
class Donut {
public:
	Donut();
	virtual ~Donut();


	std::string Flavor;
	double Price;
	double Cost;
	int Calories;
	std::string Filling;

};

#endif /* DONUT_HPP_ */
