// PCTO Challenge
// Original author: @scilla
// Original repo: https://github.com/scilla/PCTO_exercises
// Contributors: @leeoocca

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CROSS 'X'
#define EMPTY '-'

#define MAX_CANVAS 99

#define POS(x, y) (y * canvas.x_size + x)

typedef struct s_canvas
{
	char	*arr;
	int		x_size;
	int		y_size;
} t_canvas;

t_canvas canvas;

void error(char *e)
{
	printf("Error!\n%s\n", e);
	exit(1);
}

void init_canvas(const int new_x_size, const int new_y_size)
{
	if (new_x_size > MAX_CANVAS || new_y_size > MAX_CANVAS)
	{
		error("Canvas size too big.");
	}
	canvas.x_size = new_x_size;
	canvas.y_size = new_y_size;
	canvas.arr = malloc(new_x_size * new_y_size);
	memset(canvas.arr, EMPTY, new_x_size * new_y_size);
}

void print_canvas()
{
	printf("\e[1;1H\e[2J"); // clear screen
	printf("  ");
	for (int n = 0; n < canvas.x_size; n++)
	{
		printf("%2d", n);
	}
	printf("\n");
	for (int y = 0; y < canvas.y_size; y++)
	{
		printf("%2d ", y);
		for (int x = 0; x < canvas.x_size; x++)
		{
			printf("%c ", canvas.arr[POS(x, y)]);
		}
		printf("\n");
	}
}

void check_pixel(int x, int y)
{
	if (x < 0 || y < 0 || x >= canvas.x_size || y >= canvas.y_size)
	{
		error("Pixel out of canvas.");
	}
}

char get_pixel(int from_x, int from_y)
{
	check_pixel(from_x, from_y);
	return canvas.arr[POS(from_x, from_y)];
}

void delete_pixel(int from_x, int from_y)
{
	check_pixel(from_x, from_y);
	canvas.arr[POS(from_x, from_y)] = EMPTY;
}

void put_pixel(int to_x, int to_y)
{
	check_pixel(to_x, to_y);
	canvas.arr[POS(to_x, to_y)] = CROSS;
}

void move_pixel(int from_x, int from_y, int to_x, int to_y)
{
	char t = get_pixel(from_x, from_y);
	delete_pixel(from_x, from_y);
	if (t == CROSS)
	{
		put_pixel(to_x, to_y);
	}
	else
	{
		delete_pixel(to_x, to_y);
	}
}

int main()
{
	const int size_x = 7;
	const int size_y = 8;

	init_canvas(size_x, size_y);

	// modifica da qui
	put_pixel(2, 4);
	// a qui

	print_canvas();
	return 0;
}
