#ifndef ___Dollar	
#define ___Dollar

class Money {

};

class Dollar : public Money {
private:
	int amount;
public:
	Dollar(int amount){ this->amount = amount; }

	Dollar times(int multiplier){
		return Dollar(amount * multiplier);
	}

	bool operator==(const Dollar& other) const {
		return this->amount == other.amount;
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
