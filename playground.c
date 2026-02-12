#include "main.h"

int init_playground(playground_t *playground)
{
	if (init_snake(&playground->snake))
		return (1);

	random_food(&playground->food);

	return (0);
}

void clear_playground(playground_t *playground)
{
	for (int row = 0; row < ROWS; row++)
	{
		if (row == 0 || row == ROWS - 1)
		{
			for (int column = 0; column < COLUMNS; column++)
				(playground->grid)[row][column] = BLOCK;

			continue;
		}

		(playground->grid)[row][0] = BLOCK;

		for (int column = 1; column < COLUMNS - 1; column++)
			(playground->grid)[row][column] = '\0';

		(playground->grid)[row][COLUMNS - 1] = BLOCK;
	}

}

void refresh_playground(playground_t *playground)
{
	snake_t *snake = &playground->snake;
	pointnode_t *tail = snake->tail;
	point_t *food = &playground->food;

	clear_playground(playground);

	while (tail)
	{
		point_t *point = &(tail->point);

		if (tail->prev)
			(playground->grid)[point->y][point->x] = SNAKE_BODY;
		else
		{
			switch ((playground->grid)[point->y][point->x])
			{
				case SNAKE_BODY:
				case BLOCK:
					status.game_over = true;
					return;
				default:
					(playground->grid)[point->y][point->x] = SNAKE_HEAD;
			}
		}

		tail = tail->prev;
	}

	while ((playground->grid)[food->y][food->x])
	{
		if ((playground->grid)[food->y][food->x] == SNAKE_HEAD)
		{ 
			status.score++;
			increase_snake(snake);
		}

		random_food(food);
	}

	
	(playground->grid)[food->y][food->x] = FOOD;
}

void render_playground(playground_t *playground)
{
	refresh_playground(playground);

	if (!status.game_over)
	{
		printf("\033[H");

		print_number(status.score);

		for (int row = 0; row < ROWS; row++)
		{
			for (int column = 0; column < COLUMNS; column++)
			{

				switch ((playground->grid)[row][column])
				{
					case SNAKE_HEAD:
						printf(BOX_LIGHT_3);
						break;
					case SNAKE_BODY:
						printf(BOX_LIGHT_2);
						break;
					case BLOCK:
						printf(BOX);
						break;
					case FOOD:
						printf(GRN BOX_LIGHT_3 RESET);
						break;
					default:
						printf(BOX_LIGHT_1);
				}
			}

			printf("\n");
		}
	}
}
