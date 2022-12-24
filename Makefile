NAME		= test
SSRCSDIR	= ./test_files/Vector/
OBJSDIR		= objs
INCLUDES	= ./


SRCS		= main.cpp
# SRCS		+= test_files/Vector/vec_example42.cpp
OBJS		= $(SRCS:.cpp=.o)

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -I$(INCLUDES)

#Colors
DEF_COLOR	= \033[0;39m
GRAY		= \033[0;90m
RED			= \033[0;91m
GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

defines_ft="-D NS=ft";
defines_std="-D NS=std";

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling $@$(DEF_COLOR)"
	@$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	@rm -rf $(OBJS)
	@echo "$(RED)Object cleaned.$(DEF_COLOR)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Name cleaned.$(DEF_COLOR)"

re: fclean all

run : re
	@./$(NAME)
	
	@rm -rf $(OBJS)
	@rm -rf $(NAME)

.PHONY: all clean fclean re run