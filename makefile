source = src/*.cc src/creature/*.cc src/handle/*.cc src/item/*.cc\
		src/map/*.cc src/position/*.cc src/utility/*.cc

nethack : $(source)
	g++ -std=c++14 $(source) -I include -o nethack

run :
	./nethack