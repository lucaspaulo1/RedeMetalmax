CC = g++ -g -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

# nome do programa
NAME = tp2 

# input do programa
INPUT = inputs.txt

# gere a lista de arquivos-fonte (todos os .cpp no diretório src)
SRCS = $(wildcard $(SRC)/*.cpp)

# gere a lista de objetos a partir dos arquivos-fonte
OBJS = $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))

# gere o executável
EXE = $(BIN)/$(NAME)

# compila o programa
all: create_dirs $(EXE)

create_dirs: 
	@mkdir -p $(OBJ) $(BIN) # -p evita erros se o diretorio ja existir

$(EXE): $(OBJS)
	@$(CC) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/%.o: $(SRC)/%.cpp $(wildcard $(INC)/*.h) | create_dirs # cria as pastas se elas nao existirem
	@$(CC) $(CFLAGS) -o $@ -c $<

# executa o programa
run: $(EXE)
	@$(EXE) < $(INPUT)

# executa o valgrind
valgrind: $(EXE)
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all $(EXE) < $(INPUT)

# faz um commit e sobe as mudancas para o repositorio no github
github: 
	@git add . 
	@git commit -m "Commit automatico"
	@git push

# reseta o repositorio local para o ultimo commit
reset:
	@git reset --hard HEAD

# limpa as pastas
clean:
	@rm -f $(EXE) $(OBJS) gmon.out

