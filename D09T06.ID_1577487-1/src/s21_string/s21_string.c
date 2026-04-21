#include "s21_string.h"

size_t s21_strlen(const char *str) {
  size_t length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}
char *s21_strcat(char *dest, const char *src) {
  char *ptr = dest;

  while (*ptr != '\0') {
    ptr++;
  }

  while (*src != '\0') {
    *ptr = *src;
    ptr++;
    src++;
  }

  *ptr = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  while (*str != '\0') {
    if (*str == (char)c) {
      return (char *)str;
    }
    str++;
  }

  if ((char)c == '\0') {
    return (char *)str;
  }
  return NULL;
}
char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') {
    return (char *)haystack;
  }

  while (*haystack != '\0') {
    const char *h = haystack;
    const char *n = needle;

    while (*h != '\0' && *n != '\0' && *h == *n) {
      h++;
      n++;
    }

    if (*n == '\0') {
      return (char *)haystack;
    }
    haystack++;
  }
  return NULL;
}
int s21_strcmp(const char *str1, const char *str2) {
  int i = 0;
  while (str1[i] != '\0' && str1[i] == str2[i]) {
    i++;
  }
  return (int)((unsigned char)str1[i] - (unsigned char)str2[i]);
}
char *s21_strcpy(char *dest, const char *src) {
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}
