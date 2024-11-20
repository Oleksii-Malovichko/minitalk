#include "server.h"

static t_server_state *state = {0};

int main(void)
{
	state = malloc(sizeof(t_server_state));
	state->bit_index = 0;
	
	printf("%d\n", state->bit_index);
	free(state);
}