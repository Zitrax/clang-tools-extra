// RUN: %check_clang_tidy %s misc-printf-define %t

// FIXME: Add something that triggers the check here.
printf("hello");
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' is insufficiently awesome [misc-printf-define]

// FIXME: Verify the applied fix.
//   * Make the CHECK patterns specific enough and try to make verified lines
//     unique to avoid incorrect matches.
//   * Use {{}} for regular expressions.
// CHECK-FIXES: {{^}}printf("Hello");{{$}}

// FIXME: Add something that doesn't trigger the check here.
printf("Hello");

