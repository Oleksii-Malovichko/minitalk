#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// перехват сигнала ctrl+c
volatile sig_atomic_t stop = 0; // используем этот тип, так как при отправлениии сигналов, этот тип гарантирует, что будет изменен от начала до конца за раз

void	handle_sigint(int sig)
{
	write(STDOUT_FILENO, "SIGINT caught!\n", 15);
	stop = 1;
}

void	handle_sigusr1(int sig)
{
	write(STDOUT_FILENO, "SIGUSR1 received!\n", 18);
}

void	handle_sigusr2(int sig)
{
	write(STDOUT_FILENO, "SIGUSR2 received!\n", 18);
}

int main()
{
	signal(SIGUSR1, handle_sigusr1); // только эти сигналы разрешены, зато их можно настраивать полностью с нуля
	signal(SIGUSR2, handle_sigusr2);

	printf("Process PID: %d\n", getpid());
	while (1)
	{
		sleep(1);
	}
	return (0);
}