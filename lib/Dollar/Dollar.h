#ifndef ___Dollar	
#define ___Dollar

class Dollar {
public:
	Dollar(int amount){ this->amount = amount; }

	int amount;
	Dollar times(int multiplier){
		amount *= multiplier;
		return 0;
	}
};

#endif //___Dollar
