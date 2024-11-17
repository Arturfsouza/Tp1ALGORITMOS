# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Nome do executável
TARGET = tp1

# Arquivos fontes
SOURCES = main.cpp grafo.cpp

# Arquivos objeto (gerados automaticamente)
OBJECTS = $(SOURCES:.cpp=.o)

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para compilar os arquivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa arquivos gerados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Recompila tudo do zero
rebuild: clean all
