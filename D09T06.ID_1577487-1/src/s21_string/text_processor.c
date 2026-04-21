#include <stdio.h>
#include <stdlib.h>

int s21_strlen(const char *str) {
  int len = 0;
  while (str[len] != '\0')
    len++;
  return len;
}

int s21_strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int main(int argc, char *argv[]) {

  if (argc != 3 || s21_strcmp(argv[1], "-w") != 0) {
    printf("n/a");
    return 0;
  }

  int width = atoi(argv[2]);
  if (width <= 0) {
    printf("n/a");
    return 0;
  }

  char text[101];
  if (fgets(text, 101, stdin) == NULL) {
    return 0;
  }

  int len = s21_strlen(text);
  if (len > 0 && text[len - 1] == '\n') {
    text[len - 1] = '\0';
    len--;
  }

  int current = 0;
  int first_line = 1;

  while (current < len) {

    while (current < len && text[current] == ' ') {
      current++;
    }
    if (current >= len)
      break;

    if (!first_line)
      printf("\n");

    int remaining = len - current;

    if (remaining <= width) {
      printf("%s", &text[current]);
      current += remaining;
      continue;
    }

    int split_point = current + width;
    int space_idx = -1;

    for (int i = current; i < split_point; i++) {
      if (text[i] == ' ') {
        space_idx = i;
      }
    }

    if (text[split_point] == ' ' || text[split_point] == '\0') {

      for (int i = current; i < split_point; i++)
        putchar(text[i]);
      current = split_point;
    } else if (space_idx != -1) {

      for (int i = current; i < space_idx; i++)
        putchar(text[i]);
      current = space_idx;
    } else {

      for (int i = current; i < split_point - 1; i++)
        putchar(text[i]);
      putchar('-');
      current = split_point - 1;
    }
    first_line = 0;
  }

  return 0;
}
