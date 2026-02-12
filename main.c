#include "main.h"

status_t status;

int main(void)
{
	playground_t playground;
	pthread_t keys_thread;

	status.score = 0;
	status.game_over = false;

	srand(time(NULL));

	if (init_playground(&playground))
		exit(EXIT_FAILURE);

	printf("\033[?25l"); /* hide cursor */

	terminal_row_mode();

	if (pthread_create(&keys_thread, NULL, &keys_handler, (void *) &playground) != 0)
		exit(EXIT_FAILURE);

	render_handler(&playground);	

	if (pthread_join(keys_thread, NULL) != 0)
		exit(EXIT_FAILURE);

	terminal_normal_mode();

	free_points(playground.snake.head);

	system("clear");

	printf("\033[?25h"); /* show cursor */

	return (EXIT_SUCCESS);
}
