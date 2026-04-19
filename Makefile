CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET   = movie_recommender
SRCS     = main.cpp Movie.cpp User.cpp Rating.cpp Manager.cpp
OBJS     = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)