#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#define DEFAULT_LOG_FILE "timer.log"

void print_time(unsigned int t) {
  unsigned int h = t / 3600, m = (t % 3600) / 60, s = t % 60;
  unsigned char frame = s % 8;
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
}
struct argSetup {
  char *title;
  char *filename;
  char *error;
  char help;
};
struct argSetup *processArgs(int argc, char *argv[]) {
  struct argSetup *data = (struct argSetup *)malloc(sizeof(struct argSetup));
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--title") == 0) {
      if (argc <= i + 1) {
        char *error = "unable to find description in arguments";
        data->error = (char *)malloc((strlen(error) + 1) * sizeof(char));
        strcpy(data->error, error);
        return data;
      }
      i += 1;
      data->title = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
      strcpy(data->title, argv[i]);
    } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
      if (argc <= i + 1) {
        char *error = "unable to find filename in arguments";
        data->error = (char *)malloc((strlen(error) + 1) * sizeof(char));
        strcpy(data->error, error);
        return data;
      }
      i += 1;
      data->filename = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
      strcpy(data->filename, argv[i]);
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      data->help = 1;
    }
  }
  return data;
}
int writeLog(char *filename, char *title, time_t *start_time,
             unsigned int time_to_complete) {

  FILE *file;
  const char *mode = "a+";
  file = fopen((filename == NULL ? DEFAULT_LOG_FILE : filename), mode);
  if (file == NULL) {
    perror("Error opening log file: ");
    perror((filename == NULL ? DEFAULT_LOG_FILE : filename));
    return 0;
  }
  char *start_time_str = ctime(start_time);
  start_time_str[strlen(start_time_str) - 1] = '\0';

  unsigned int t = time_to_complete, h = t / 3600, m = (t % 3600) / 60,
               s = t % 60;
  char time_to_complete_str[13];

  snprintf(time_to_complete_str, 13, "%02uH:%02uM:%02uS", h, m, s);
  fprintf(file, "[%s] \'%s\' completed in [%s]\n", start_time_str, title,
          time_to_complete_str);

  return 1;
}
void freeArgs(struct argSetup **arg) {
  struct argSetup *processedArg = *arg;
  if (processedArg->title != NULL)
    free(processedArg->title);
  if (processedArg->filename != NULL)
    free(processedArg->filename);
  if (processedArg->error != NULL)
    free(processedArg->error);
  free(processedArg);
}
int clean_buffer(fd_set *fds) {
  struct timeval tv_nonblock = {0, 0};
  while (1) {
    FD_ZERO(fds);
    FD_SET(STDIN_FILENO, fds);
    int retval = select(STDIN_FILENO + 1, fds, NULL, NULL, &tv_nonblock);
    if (retval > 0) {
      getchar();
    } else {
      return 1;
    }
  }
  return 0;
}
void set_stdin_raw(struct termios *old_settings) {
  struct termios new_settings;
  tcgetattr(STDIN_FILENO, old_settings);
  new_settings = *old_settings;
  new_settings.c_lflag &= ~(ICANON | ECHO);
  new_settings.c_cc[VMIN] = 1;
  new_settings.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}
char check_quit() {
  fd_set fds;
  struct timeval tv = {0, 500000};
  int retval;

  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);

  retval = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

  if (retval == -1) {
    perror("Error while geting data using select() in check_quit\n");
    return 0;
  } else if (retval > 0) {
    char ch = getchar();
    if (ch == 'q' || ch == 'Q') {
      clean_buffer(&fds);
      return 0;
    } else if (ch == 'c' || ch == 'C') {
      clean_buffer(&fds);
      return -1;
    }
  }

  clean_buffer(&fds);
  return 1;
}
int main(int argc, char *argv[]) {
  struct argSetup *processedArg = processArgs(argc, argv);
  const char *help =
      "Usage: timer [OPTIONS]\n"
      "A simple CLI timer with an animated ASCII art display.\n\n"
      "Options:\n"
      "  -t, --title <TEXT>  Set a title for the task. This "
      "will be\n"
      "                            logged upon completion. (e.g., \"-t "
      "'Morning Coding'\")\n"
      "  -f, --file <FILENAME>     Specify a log file for completed tasks. "
      "Defaults to\n"
      "                            'timer.log' if not provided.\n"
      "  -h, --help                Display this help message and exit.\n\n"
      "Controls during runtime:\n"
      "  Press 'q' or 'Q' then Enter          To quit the timer without "
      "logging it as "
      "completed.\n"
      "  Press 'c' or 'C' then Enter          To mark the task as completed "
      "and log its "
      "duration\n"
      "                            before quitting.\n\n"
      "Examples:\n"
      "  timer\n"
      "    Starts a basic timer.\n\n"
      "  timer -t 'My Focus Session'\n"
      "    Starts a timer for 'My Focus Session'. If you press 'c', it logs to "
      "timer.log.\n\n"
      "  timer -t 'Reading Chapter 3' -f 'study_log.txt'\n"
      "    Starts a timer for 'Reading Chapter 3' and logs its duration to "
      "'study_log.txt'\n"
      "    when 'c' is pressed.\n";
  if (processedArg->error != NULL) {
    fprintf(stderr, "Error: %s\n", processedArg->error);
    freeArgs(&processedArg);
    return EXIT_FAILURE;
  }
  if (processedArg->help == 1) {
    printf("%s\n", help);
    return EXIT_SUCCESS;
  }

  time_t start = time(NULL), current = start;

  struct termios old_stdin_settings;
  set_stdin_raw(&old_stdin_settings);

  unsigned char isComplete = 0;
  unsigned char isRunning = 1;
  printf("Enter q to quit and c to mark as completed+quit.\n\n");
  while (isRunning) {
    current = time(NULL);
    print_time((unsigned int)difftime(current, start));
    const char cq = check_quit();
    if (cq <= 0) {
      isRunning = 0;
      puts("");
    }
    if (cq == -1) {
      isComplete = 1;
    }
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &old_stdin_settings);
  if (isComplete == 1) {
    writeLog(
        processedArg->filename,
        (processedArg->title == NULL ? "Untitled Task" : processedArg->title),
        &start, (unsigned int)difftime(current, start));
  }
  freeArgs(&processedArg);
  return EXIT_SUCCESS;
}
