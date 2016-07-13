#include "material.h"

Material::Material() {
	name_ = "Standard";
	ka_ = Color(0.0, 0.0, 0.0);
	kd_ = Color(0.0, 0.0, 0.0);
	ks_ = Color(0.0, 0.0, 0.0);
	m_ = 0.0;
}
Material::Material(std::string name, Color ka, Color kd, Color ks, float m) : name_( name ), ka_( ka ), kd_( kd ), ks_( ks ), m_( m ) {}
Material::~Material() { }

float Material::getM() const {
	return m_;
}
Color Material::getKA() const {
	return ka_;
}
Color Material::getKD() const {
	return kd_;
}
Color Material::getKS() const {
	return ks_;
}
std::string Material::getName() {
	return name_;
}

std::ostream& operator<<(std::ostream& os, Material& m) {
	return os << "----------------\nMaterial:\nname: " << m.getName() << "\nka: " << m.getKA() << "ks: " << m.getKS() << "kd: " << m.getKD() << "m :" << m.getM() << std::endl;
}
