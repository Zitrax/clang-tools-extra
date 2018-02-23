// RUN: %check_clang_tidy %s misc-printf-define %t

int printf(const char*){}

void f(void) {
  printf("hello");
  // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: printf string should start with capital letter [misc-printf-define]
  // CHECK-FIXES: {{^  }}printf("Hello");{{$}}
  #define LC "lc"
  printf(LC);
  // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: printf string should start with capital letter [misc-printf-define]
  // CHECK-FIXES: {{^  }}#define LC "Lc"{{$}}
  printf(0);
  printf("Message");
  // FIXME: The below will currently fail since the FixItHint does not currently apply to defines
  #define UC "UC"
  printf(UC);
}