#ifndef ___Dollar	
#define ___Dollar

class Dollar {
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

#endif //___Dollar
