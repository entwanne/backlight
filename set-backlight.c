#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int ac, char *argv[]) {
  if (ac < 2) {
    return 1;
  }

  char *value = argv[1];
  for (int i = 0; value[i]; i++) {
    if (value[i] < '0' || value[i] > '9')
      return 1;
  }

  setuid(geteuid());
  int fd = open("/sys/class/backlight/intel_backlight/brightness", O_WRONLY | O_TRUNC);
  write(fd, value, strlen(value));
  close(fd);
  return 0;
}
