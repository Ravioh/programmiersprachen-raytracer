#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP

#include <iosfwd>
#include <string>
#include <sstream>
#include <vector>

#include "color.hpp"

class Material {
public:
	Material();
	Material(std::string name, const Color ka, const Color kd, const Color ks, float m);
	~Material();



	std::string getName();
	Color getKA() const;
	Color getKD() const;
	Color getKS() const;
	float getM() const;
	bool refraction;
	bool is_reflective() {
		return ks_.r > 0 && ks_.g > 0 && ks_.b > 0;
	}



	friend std::ostream& operator<<(std::ostream& os, Material& m);

private:


	std::string name_;
	Color ka_;
	Color kd_;
	Color ks_;
	float m_;


};

std::ostream& operator<<(std::ostream& os, Material& m);

#endif // BUW_MATERIAL_HPP
