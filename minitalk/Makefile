# Название исполняемых файлов
CLIENT_NAME = client
SERVER_NAME = server

# Директории для библиотек
LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf

# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR)

# Директория для объектных файлов
OBJ_DIR = obj

# Исходные файлы для client и server
CLIENT_SRC = client.c # client_utils.c (если есть)
SERVER_SRC = server.c # server_utils.c (если есть)

# Преобразуем исходники в объектные файлы
CLIENT_OBJ = $(CLIENT_SRC:%.c=$(OBJ_DIR)/%.o)
SERVER_OBJ = $(SERVER_SRC:%.c=$(OBJ_DIR)/%.o)

# Цель по умолчанию
all: $(CLIENT_NAME) $(SERVER_NAME)

# Правило для создания client
$(CLIENT_NAME): $(CLIENT_OBJ) $(LIBFT_DIR)/libft.a $(FT_PRINTF_DIR)/libftprintf.a
	$(CC) $(CLIENT_OBJ) -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf -o $(CLIENT_NAME)

# Правило для создания server
$(SERVER_NAME): $(SERVER_OBJ) $(LIBFT_DIR)/libft.a $(FT_PRINTF_DIR)/libftprintf.a
	$(CC) $(SERVER_OBJ) -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf -o $(SERVER_NAME)

# Компиляция объектных файлов
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Правила для libft и ft_printf
$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF_DIR)/libftprintf.a:
	$(MAKE) -C $(FT_PRINTF_DIR)

# Очистка
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all