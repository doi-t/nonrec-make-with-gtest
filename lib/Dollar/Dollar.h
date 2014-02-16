#ifndef ___Dollar	
#define ___Dollar

class Dollar {
public:
	Dollar(int amount){ this->amount = amount; }

	int amount;
	void times(int multiplier){ amount = amount*2; }
};

#endif //___Dollar
