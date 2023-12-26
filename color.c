#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <mlx.h>

# define WIDTH 400
# define HEIGHT 400
# define EPSILON 0.0001

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;	
}	t_color;

typedef struct screen
{
    void *mlx;
    void *window;
}   t_screen;


t_color adding_colors(t_color a, t_color b)
{
	t_color new_color;

	new_color.red = a.red + b.red;
    if (new_color.red > 255)
        new_color.red = 255;
	new_color.green = a.green + b.green;
    if (new_color.green > 255)
        new_color.green = 255;
	new_color.blue = a.blue + b.blue;
    if (new_color.blue > 255)
        new_color.blue = 255;
	return (new_color);
}

t_color subtract_colors(t_color a, t_color b)
{
	t_color new_color;

	new_color.red = a.red - b.red;
    if (new_color.red < 0)
        new_color.red = 0;
	new_color.green = a.green - b.green;
    if (new_color.green < 0)
        new_color.green = 0;
	new_color.blue = a.blue - b.blue;
    if (new_color.blue < 0)
        new_color.blue = 0;
	return (new_color);
}

t_color multiply_scalar_color(double scalar, t_color a)
{
    t_color new_color;
    new_color.red = scalar * a.red;
    if (new_color.red > 255)
        new_color.red = 255;
    new_color.green = scalar * a.green;
    if (new_color.green > 255)
        new_color.green = 255;
    new_color.blue = scalar * a.blue;
    if (new_color.blue > 255)
        new_color.blue = 255;
    return (new_color);
}

t_color multiply_colors(t_color a, t_color b)
{
    t_color new_color;
    new_color.red = b.red * a.red;
    if (new_color.red > 255)
        new_color.red = 255;
    new_color.green = b.green * a.green;
    if (new_color.green > 255)
        new_color.green = 255;
    new_color.blue = b.blue * a.blue;
    if (new_color.blue > 255)
        new_color.blue = 255;
    return (new_color);
}

int	x_press(t_screen *screen)
{
	printf("You closed the window =/\n");
    mlx_destroy_window(screen->mlx, screen->window);
	mlx_destroy_display(screen->mlx);
	free(screen->mlx);
	return (1);
}

int main(void)
{
    int r = 1;
    int g = 2;
    int b = 3;
    int rr = 1;
    int gg = 2;
    int bb = 3;

    // t_color color = adding_colors((t_color){r, g, b}, (t_color){rr, gg, bb});
    // printf("add: r: %d   g: %d   b: %d\n", color.red, color.green, color.blue);
    // color = subtract_colors((t_color){r, g, b}, (t_color){rr, gg, bb});
    // printf("add: r: %d   g: %d   b: %d\n", color.red, color.green, color.blue);
    // color = multiply_colors((t_color){r, g, b}, (t_color){rr, gg, bb});
    // printf("add: r: %d   g: %d   b: %d\n", color.red, color.green, color.blue);
    // color = multiply_scalar_color(2.0, (t_color){rr, gg, bb});
    // printf("add: r: %d   g: %d   b: %d\n", color.red, color.green, color.blue);

    t_screen screen;
    screen.mlx = mlx_init();
    screen.mlx = mlx_new_window(screen.mlx, WIDTH, HEIGHT, "O Inicio de Tudo");

    mlx_hook(screen.window, DestroyNotify, NoEventMask, x_press, &screen);
    mlx_loop(screen.mlx);
}
