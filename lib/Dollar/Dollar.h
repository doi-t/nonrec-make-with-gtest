#ifndef ___Dollar	
#define ___Dollar

#include <iostream>
#include <typeinfo>

class Dollar;

class Money {
protected:
	int amount;
public:
	virtual ~Money(){}
	bool operator==(const Money& other) const {
		std::cout << typeid(*this).name() << "\n";
		std::cout << typeid(other).name() << "\n";
		return (this->amount == other.amount && typeid(*this).name() == typeid(other).name());
	}
	Dollar dollar(int);
};

class Dollar : public Money {
public:
	Dollar(int amount){ this->amount = amount; }

	Money times(int multiplier){
		return Dollar(amount * multiplier);
	}
};

class Franc : public Money {
public:
	Franc(int amount){ this->amount = amount; }

	Money times(int multiplier){
		return Franc(amount * multiplier);
	}
};

#endif //___Dollar
