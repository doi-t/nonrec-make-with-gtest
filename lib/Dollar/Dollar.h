#ifndef ___Dollar	
#define ___Dollar

class Money {
protected:
	int amount;
public:
	bool operator==(const Money& other) const {
		return this->amount == other.amount;
	}
};

class Dollar : public Money {
public:
	Dollar(int amount){ this->amount = amount; }

	Dollar times(int multiplier){
		return Dollar(amount * multiplier);
	}
};

class Franc {
private:
	int amount;
public:
	Franc(int amount){ this->amount = amount; }

	Franc times(int multiplier){
		return Franc(amount * multiplier);
	}

	bool operator==(const Franc& other) const {
		return this->amount == other.amount;
	}
};

#endif //___Dollar
