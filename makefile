all: autocorrect

autocorrect: autocorrect.cpp autocorrectlib.cpp autocorrectlib.h
	g++	autocorrect.cpp	-o autocorrect -I.
