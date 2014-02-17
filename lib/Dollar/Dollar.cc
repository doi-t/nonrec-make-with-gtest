#include "Dollar/Dollar.h"

Dollar *
Money::dollar(int amount){
	return new Dollar(amount);
}
