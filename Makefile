# ==========================================
# Configurações do Compilador
# ==========================================
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -pedantic -O2

# ==========================================
# Diretórios
# ==========================================
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build
BIN_DIR   := bin

TARGET    := $(BIN_DIR)/programa

# Opções do pré-processador e da linkagem
CPPFLAGS  := -I$(INC_DIR) -MMD -MP
LDFLAGS   :=
LDLIBS    :=

# ==========================================
# Descoberta de Arquivos Fontes e Objetos
# ==========================================
SRCS      := $(wildcard $(SRC_DIR)/*.cpp)
OBJS      := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
DEPS      := $(OBJS:.o=.d)

# ==========================================
# Regras Principais
# ==========================================
.PHONY: all clean run

all: $(TARGET)

# Linkagem final do executável
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

# Compilação dos arquivos .cpp em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Criação das pastas de saída caso não existam
$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

# Executa o programa compilado
run: all
	./$(TARGET)

# Limpeza dos artefatos de compilação
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Inclui as dependências automáticas geradas por -MMD -MP
-include $(DEPS)