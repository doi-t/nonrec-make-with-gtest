#ifndef ___Dollar	
#define ___Dollar

class Dollar {
public:
	Dollar(int amount){ this->amount = amount; }

	int amount;
	Dollar times(int multiplier){
		return Dollar(amount * multiplier);
	}
	bool equals(Dollar object){
		return true;
	}
};

#endif //___Dollar
