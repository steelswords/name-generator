text-generator: obj/TextGenerationGrammar.o main.cpp
	g++ --std=c++17 -g obj/TextGenerationGrammar.o main.cpp -o text-generator

obj/TextGenerationGrammar.o: TextGenerationGrammar.hpp TextGenerationGrammar.cpp
	g++ --std=c++17 -g -c -o obj/TextGenerationGrammar.o TextGenerationGrammar.cpp -std=c++20

