#pragma once
#include <iostream>
#include <string>

template <int T>
constexpr auto bit = std::integral_constant<int, T>{};

template <int I>
class Bit
{
	constexpr static inline uint8_t mask() {	return (uint8_t)1 << I;		}
	uint8_t data;
public:
	void operator= (bool value) { data = ((data & ~mask()) | ((uint8_t)value << I)); }
	bool operator==(bool value) { return ((data & mask()) == value); }
	operator bool() const	{	return ((data & mask()) != 0);	}
};

class Byte
{
	uint8_t data;
public:
	Byte() : data(0) {}
	Byte(uint8_t _data) : data(_data) {}
	Byte(int _data) : data((uint8_t)_data) { }
	void Print() 
	{ 
		std::cout << "0d"
		<< (*this)[bit<7>]
		<< (*this)[bit<6>]
		<< (*this)[bit<5>]
		<< (*this)[bit<4>]
		<< (*this)[bit<3>]
		<< (*this)[bit<2>] 
		<< (*this)[bit<1>]
		<< (*this)[bit<0>] 
	}
	std::string to_string()
	{
		std::string string{};
		string.push_back('0');
		string.push_back('d');
		string.push_back((*this)[bit<7>] ? '1' : '0');
		string.push_back((*this)[bit<6>] ? '1' : '0');
		string.push_back((*this)[bit<5>] ? '1' : '0');
		string.push_back((*this)[bit<4>] ? '1' : '0');
		string.push_back((*this)[bit<3>] ? '1' : '0');
		string.push_back((*this)[bit<2>] ? '1' : '0');
		string.push_back((*this)[bit<1>] ? '1' : '0');
		string.push_back((*this)[bit<0>] ? '1' : '0');
		return string;
	}


	template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	bool operator==(const T& other) const {		return Byte(this->data == static_cast<uint8_t>(other));		}

	//+= Operator overload - addition of bytes should be done with this, if it overflows it returns true.
	template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	bool operator+=(const T& other) const 
	{
		int var = this->data += static_cast<uint8_t>(other);
		if (var < 255)
			return false;
		else
			return true;
	}

	uint8_t operator()() const {	return data;	}

	//Changable Value Bit Access - use bit<T> to access
	template<int T>
	constexpr Bit<T>& operator[](std::integral_constant<int, T>)
	{
		static_assert(T < 8 && T >= 0, "Byte.h - Template parameter T must be in the range [0, 7]");
		Bit<T>* ptr = (Bit<T>*)(&data);
		return *ptr;
	}
};
