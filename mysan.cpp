#include <cstdio>

extern "C" void __asan_init() {
  //
}

extern "C" void __asan_version_mismatch_check_v8() {
  //
}

extern "C" void __asan_register_globals() {
  //
}

extern "C" void __asan_unregister_globals() {
  //
}

extern "C" void __asan_load8(void* p) {
  printf("__asan_load8(%p)\n", p);
}

extern "C" void __asan_store8(void* p) {
  printf("__asan_store8(%p)\n", p);
}
