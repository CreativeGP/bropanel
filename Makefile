greatpanel: greatpanel.cpp
	g++ greatpanel.cpp -I./  -o greatpanel.o --std=c++2a -c -Wl,-Bdynamic,-lc,-ldl,-lpthread,-Bstatic,-lboost_system

