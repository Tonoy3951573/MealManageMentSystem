CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

# All C files in this folder
SRCS = main.c auth.c student.c file_handeler.c helper.c meal.c billing.c

# Convert .c → .o
OBJS = $(SRCS:.c=.o)

TARGET = MealManagement

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
