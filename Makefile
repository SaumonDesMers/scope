CC			= clang++
CFLAGS		= -g -Wall -Wextra -Werror
# VALGRIND	= valgrind --tool=memcheck --leak-check=full --leak-resolution=high --track-origins=yes --show-reachable=yes --log-file=valgrind.log

NAME		= scope

SRC_DIR		= src
SRC			= $(patsubst %, $(SRC_DIR)/%, main.cpp shader.cpp)
HEADER_DIR	= include

OBJ_DIR		= obj
OBJ			= $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP_DIR		= dep
DEP			= $(SRC:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -lglfw -lGLEW -lGL $(OBJ) -o $@
			@echo -e "$(Green)*** $(UGreen)Successfully compiled $(NAME)$(Green) ***$(nc)"
# -lglut

-include $(DEP)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
			@mkdir -p $(OBJ_DIR) $(DEP_DIR)
			$(CC) -MMD $(CFLAGS) -DGLEW_EGL -I $(HEADER_DIR) -c $< -o $@
			@mv $(OBJ_DIR)/*.d $(DEP_DIR)

#----------------------------ALL----------------------------

all:		$(NAME)

clean:
			@echo -e "$(BRed)/!\\ $(BYellow)Remove containers obj and dep$(BRed) /!\\ $(nc)"
			@$(RM) $(OBJ) $(DEP)

fclean:		clean
			@echo -e "$(BRed)/!\\ $(BYellow)Remove $(NAME)$(BRed) /!\\ $(nc)"
			@$(RM) $(NAME)

re:			fclean
			@make all --no-print-directory

.PHONY:		all clean fclean re

#------------------------------COLOR------------------------------

nc=\033[0m
Green=\033[0;32m
BRed=\033[1;31m
BYellow=\033[1;33m
UGreen=\033[4;32m
On_Green=\033[42m