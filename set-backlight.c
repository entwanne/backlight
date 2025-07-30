#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


void assert(int result, const char* message) {
  if (!result) {
    fprintf(stderr, "%s\n", message);
    exit(1);
  }
}


int check_integer(const char *value) {
  if (!value) {
    return 0;
  }

  for (int i = 0; value[i]; i++) {
    if (value[i] < '0' || value[i] > '9') {
      return 0;
    }
  }

  return 1;
}


int check_path_name(const char *name) {
  if (!name) {
    return 0;
  }

  for (int i = 0; name[i]; i++) {
    char c = name[i];
    if (
	(c < '0' || c > '9')
	&& (c < 'A' || c > 'Z')
	&& (c < 'a' || c > 'z')
	&& c != '_'
      ) {
	return 0;
      }
  }

  return 1;
}


int check_dir(const char *path) {
  struct stat stat_buffer;
  return stat(path, &stat_buffer) == 0 && S_ISDIR(stat_buffer.st_mode);
}


int check_file(const char *path) {
  struct stat stat_buffer;
  return stat(path, &stat_buffer) == 0 && S_ISREG(stat_buffer.st_mode);
}


int main(int ac, char *argv[]) {
  const char *base_path = "/sys/class/backlight/";
  const char *end_path = "/brightness";

  // Arguments validation

  assert(ac >= 3, "Usage: set-backlight interface-name value");

  char *name = argv[1];
  assert(check_path_name(name), "interface-name is not a correct directory name");

  char *value = argv[2];
  assert(check_integer(value), "value is not a valid unsigned integer");

  // Path validation

  char *brightness_path = malloc(strlen(base_path) + strlen(name) + strlen(end_path) + 1);
  assert(brightness_path != NULL, "Cannot allocate memory");
  strcpy(brightness_path, base_path);
  assert(check_dir(brightness_path), "No sys directory found for brightness");
  strcat(brightness_path, name);
  assert(check_dir(brightness_path), "Brightness interface was not found");
  strcat(brightness_path, end_path);
  assert(check_file(brightness_path), "Brightness interface is not valid");

  // Run update

  int fd = open(brightness_path, O_WRONLY | O_TRUNC);
  assert(fd >= 0, "Cannot open brightness interface");
  int ret = write(fd, value, strlen(value));
  close(fd);
  assert(ret >= 0, "Cannot write value to brightness interface");

  return 0;
}
