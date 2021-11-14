NAME = resume
# NAMEW = ../index.html
# FLAGS = -Wall -Wextra -Werror
# FLAGS = -Wall -Wextra -Werror -O2
FLAGS = -Wall -Wextra -Werror -fsanitize=address
INCLUDES = -I includes/ -I includes/SDLX/

LIBRARIES = -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS="['png']"
SKELE_HTML = --shell-file ../skeleton.html

SDL_LIB = -L ~/.brew/lib -l SDL2 -l sdl2_image -l SDL2_ttf

PRELOAD_FILES =	\
	assets/

PRELOAD = --preload-file $(PRELOAD_FILES)

SDLX_DIR = SDLX/
SRC_DIR = srcs/
BIN_DIR = bin/

SDLX_NAMES = 			\
	SDLX_background		\
	SDLX_button_loop	\
	SDLX_button			\
	SDLX_collide		\
	SDLX_collisions		\
	SDLX_init			\
	SDLX_input			\
	SDLX_math			\
	SDLX_render_queue	\
	SDLX_render			\
	SDLX_scenes			\
	SDLX_ticks			\
	SDLX_utils			\
	SDLX_xbox			\
	SDLX_xlogic			\
	SDLX_xutils			\

SPRITE_NAMES = 			\
	sprite_attack		\
	sprite_healthbar	\
	sprite_pickup		\
	sprite_potions		\
	sprite_sword		\
	sprite_tooltip		\

DEBUG_FILES = 			\
	collision_view		\

ENTITY_FILES = 			\
	chest				\
	environment			\
	pickups 			\
	pots				\

SCENE_FILES = 			\
	scene_main_menu		\
	scene_world			\

# List of all the source files.
SRC_NAMES = \
	$(addprefix debug/, $(DEBUG_FILES))		\
	$(addprefix entity/, $(ENTITY_FILES))	\
	$(addprefix scenes/, $(SCENE_FILES))	\
	$(addprefix $(SDLX_DIR), $(SDLX_NAMES))	\
	$(addprefix sprites/, $(SPRITE_NAMES))	\
	attack_ui \
	bar \
	environment \
	input \
	main \
	player \
	potion \
	queue_util \
	tooltips \
	utils \
	viewport \

# List of all the source files, folders are to be added by
# including a $(addprefix, DIR_NAME, $(DIR_FILES))
FILE_NAMES = \
	$(SRC_NAMES) \

SRCS = $(addsuffix .c, $(addprefix $(SRC_DIR), $(FILE_NAMES)))
# Object files will be built to BIN_DIR. They will build the
# structure/ path tree that the SRC_DIR has.
OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all:
	make -j $(NAME)

allw:
	emcc -Wall -Wextra -Werror -O0 $(INCLUDES) -D EMCC $(LIBRARIES) $(PRELOAD) $(SRCS) $(SKELE_HTML) -o $(NAMEW)

$(NAME): $(BIN_DIR) $(OBJS)
	@gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(SDL_LIB)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# These are the target object file names given by path ($(OBJS)).
# We will create the required directories with mkdir -p.
$(BIN_DIR)%.o: %.c
	@mkdir -p $(BIN_DIR)$(dir $<)
	@gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

# Ensure that when git add is done the repo is cleaned out.
save: fclean
	git add .
	git commit -m "$(MSG)"
	git push

re: fclean all

rew:
	rm -f ../index.data
	rm -f ../index.html
	rm -f ../index.js
	rm -f ../index.wasm
	make allw

run:
	rm -f $(NAME)
	make -j all
	clear
	@echo "\033[1m\033[32m$(NAME)\033[0m"
	@./$(NAME)

