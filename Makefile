SRC=test.cpp
LIBS=-lvom -lvapiclient -lboost_system
OUT=test
WARN=-Wall -Wextra -std=c++11

all:
	g++ $(WARN) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm $(OUT)
