MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)
CFLAGS=-O3

NAME= ./bin/libmlx.dylib

INC=-I.
# OPTI=-Ounchecked

BIN= ./bin

$(BIN):
	mkdir -p $@

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ) | $(BIN)
	swiftc -O $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz

%.o: %.swift
	swiftc -O $(OPTI) $(INC) -parse-as-library -c $< -o $@

%.swiftmodule: %.swift
	swiftc -O $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)

clean:
	rm -f $(NAME) $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~