#ifndef ___Dollar	
#define ___Dollar

class Dollar {
public:
	Dollar(int amount){ this->amount = amount; }

	int amount;
	Dollar times(int multiplier){
		return Dollar(amount * multiplier);
	}
	bool operator==(const Dollar& other) const {
		return this->amount == other.amount;
	}
};

#endif //___Dollar
