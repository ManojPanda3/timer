#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void print_time(unsigned int t) {
  unsigned int h = t / 3600, m = (t % 3600) / 60, s = t % 60;
  static unsigned char frame = 0;
  static unsigned char isStart = 1;
  if (!isStart) {
    for (int i = 0; i < 5; i++) {
      printf("\033[A\033[2K");
    }
  } else {
    isStart = 0;
  }
  printf("\r");

  puts("  ___  ");
  puts((frame == 1 ? " / |/\\ " : (frame == 7 ? " /\\| \\ " : " / | \\ ")));
  printf((frame == 2 ? "|  !__|" : (frame == 6 ? "|__!  |" : "|  !  |")));
  // putchar('\r');
  printf("\t\033[38;2;100;100;255m%02uH\033[0m", h);
  printf(":\033[38;2;10;100;255m%02uM\033[0m", m);
  printf(":\033[38;2;100;0;255m%02uS\033[0m\n", s);
  puts((frame == 3
            ? "|    \\|"
            : (frame == 5 ? "|/    |" : (frame == 4 ? "|  |  |" : "|     |"))));
  puts(" \\___/ ");

  fflush(stdout);
  frame = (frame + 1) % 8;
}
int main(void) {
  clock_t start = time(NULL), current;
  sleep(1);
  unsigned char isRunning = 1;
  while (isRunning) {
    current = time(NULL);
    print_time((unsigned int)difftime(current, start));
    sleep(1);
  }
  current = time(NULL);
  print_time((unsigned int)difftime(current, start));
  return EXIT_SUCCESS;
}
