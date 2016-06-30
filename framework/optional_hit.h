#ifndef OPTIONALHIT_HPP
#define OPTIONALHIT_HPP


#include <memory>
#include <material.h> 


struct OptionalHit {
	OptionalHit(bool h, std::shared_ptr<Shape> const& s)
	: hit(h), shape(s)
	{}
	bool hit; // did we hit something
	std::shared_ptr<Shape> shape;
};


inline OptionalHit nothing() { return OptionalHit(false, nullptr); }


#endif