all: autocorrect

autocorrect: autocorrect.cpp autocorrectlib.cpp inc/autocorrectlib.h
	g++	autocorrect.cpp	-o autocorrect -I.
