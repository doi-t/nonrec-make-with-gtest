#ifndef ___Dollar	
#define ___Dollar

#include <iostream>
#include <typeinfo>

class Money {
protected:
	int amount;
public:
	bool operator==(const Money& other) const {
		std::cout << "*this == " << typeid(*this).name() << "\n";
		std::cout << "other == " << typeid(other).name() << "\n";
		return (this->amount == other.amount && typeid(*this) == typeid(other));
	}
};

class Dollar : public Money {
public:
	Dollar(int amount){ this->amount = amount; }

	Dollar times(int multiplier){
		return Dollar(amount * multiplier);
	}
};

class Franc : public Money {
public:
	Franc(int amount){ this->amount = amount; }

	Franc times(int multiplier){
		return Franc(amount * multiplier);
	}
};

#endif //___Dollar
