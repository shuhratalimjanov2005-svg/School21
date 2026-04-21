#include "s21_string.h"
#include <stdio.h>
#include <stdlib.h>

static void s21_strlen_test();
static void s21_strcmp_test();
static void s21_strcpy_test();
static void s21_strcat_test();
static void s21_strchr_test();
static void s21_strstr_test();

int main() {
  s21_strlen_test();
  s21_strcmp_test();
  s21_strcpy_test();
  s21_strcat_test();
  s21_strchr_test();
  s21_strstr_test();
  return 0;
}

void s21_strcpy_test() {
  printf("--- STRCPY TESTS ---\n");
  char dest[20];

  printf("Input: \"Hello\", Result: %s, SUCCESS\n", s21_strcpy(dest, "Hello"));

  printf("Input: \"\", Result: %s, SUCCESS\n", s21_strcpy(dest, ""));

  printf("Input: \"World 21\", Result: %s, SUCCESS\n",
         s21_strcpy(dest, "World 21"));
  printf("---------------------------\n");
}

void s21_strcat_test() {
  printf("--- STRCAT TESTS ---\n");
  char d1[30] = "Hi ";
  printf("Input: \"Hi \", \"World\", Result: %s, SUCCESS\n",
         s21_strcat(d1, "World"));
  char d2[30] = "";
  printf("Input: \"\", \"Start\", Result: %s, SUCCESS\n",
         s21_strcat(d2, "Start"));
  char d3[30] = "End";
  printf("Input: \"End\", \"\", Result: %s, SUCCESS\n", s21_strcat(d3, ""));
  printf("---------------------------\n");
}

void s21_strchr_test() {
  printf("--- STRCHR TESTS ---\n");
  const char *s = "School";
  printf("Input: \"School\", 'c', Result: %s, SUCCESS\n", s21_strchr(s, 'c'));
  printf("Input: \"School\", 'z', Result: %s, SUCCESS\n",
         s21_strchr(s, 'z') == NULL ? "NULL" : "FAIL");
  printf("Input: \"School\", '\\0', Result: %s, SUCCESS\n",
         *s21_strchr(s, '\0') == '\0' ? "End" : "FAIL");
  printf("---------------------------\n");
}

void s21_strstr_test() {
  printf("--- STRSTR TESTS ---\n");
  const char *h = "Hello World";
  printf("Input: \"Hello World\", \"World\", Result: %s, SUCCESS\n",
         s21_strstr(h, "World"));
  printf("Input: \"Hello World\", \"Bye\", Result: %s, SUCCESS\n",
         s21_strstr(h, "Bye") == NULL ? "NULL" : "FAIL");
  printf("Input: \"Hello World\", \"\", Result: %s, SUCCESS\n",
         s21_strstr(h, "") == h ? "Full" : "FAIL");
  printf("---------------------------\n");
}

void s21_strlen_test() {
  printf("--- STRLEN TESTS ---\n");
  printf("Input: \"Hello\", Output: %zu, SUCCESS\n", s21_strlen("Hello"));
  printf("Input: \"\", Output: %zu, SUCCESS\n", s21_strlen(""));
  printf("Input: \"School 21\", Output: %zu, SUCCESS\n",
         s21_strlen("School 21"));
  printf("---------------------------\n");
}

void s21_strcmp_test() {
  printf("--- STRCMP TESTS ---\n");
  printf("Input: \"abc\", \"abc\", Result: %d, SUCCESS\n",
         s21_strcmp("abc", "abc"));
  printf("Input: \"abc\", \"abd\", Result: %d, SUCCESS\n",
         s21_strcmp("abc", "abd"));
  printf("Input: \"world\", \"apple\", Result: %d, SUCCESS\n",
         s21_strcmp("world", "apple"));
  printf("---------------------------\n");
}
