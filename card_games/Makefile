# Compiler
CXX = g++

# Flags
CXXFLAGS = -I.

# Targets
all: blackjack/blackjack clock_solitaire/clock_solitaire

# Build blackjack
blackjack/blackjack: blackjack/blackjack.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

#Build clock_solitaire
clock_solitaire/clock_solitaire: clock_solitaire/clock_solitaire.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean
clean:
	rm -f blackjack/blackjack clock_solitaire/clock_solitaire
