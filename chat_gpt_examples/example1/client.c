#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void send_char(int pid, char c) {
    for (int i = 7; i >= 0; i--) {
        if ((c >> i) & 1) {
            kill(pid, SIGUSR2);  // Отправка бита 1
        } else {
            kill(pid, SIGUSR1);  // Отправка бита 0
        }
        usleep(100);  // Задержка, чтобы сервер успел обработать
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);
    char *message = argv[2];

    for (int i = 0; message[i] != '\0'; i++) {
        send_char(pid, message[i]);
    }

    return 0;
}

// Примечания:
// Обработка сигналов: Сервер ожидает сигналы, используя pause(), а клиент отправляет сигналы с помощью kill(). Сервер обрабатывает сигналы с помощью обработчиков sigaction(), и каждый сигнал представляет один бит.
// Синхронизация: Для предотвращения переполнения сигналов, клиент может добавить задержку с помощью usleep(), чтобы дать серверу время для обработки каждого сигнала.
// Обработка ошибок: На каждой стадии (в сервере и клиенте) следует предусмотреть обработку ошибок — например, неправильный PID, недоступный сервер и т.д.
// Этот алгоритм и код — это лишь один из возможных способов реализации, который можно адаптировать или улучшить в зависимости от требований и конкретных условий задачи.