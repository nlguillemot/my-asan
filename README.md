# My ASan

Proof of concept for customizing ASAN.

The idea is to reuse ASAN to hook onto loads and stores.

# Demo

Here's a command-line demo of this code.

```
$ cat mv.cpp
void mv(const long long* src, long long* dst) {
  *dst = *src;
}
$ 
$ clang++ --target=aarch64-linux-gnu -fsanitize=address -fsanitize-address-outline-instrumentation -O1 -c mv.cpp -o mv.o
$ llvm-objdump -d -r mv.o --no-show-raw-insn

mv.o:   file format elf64-littleaarch64

Disassembly of section .text:

0000000000000000 <_Z2mvPKxPx>:
       0:       stp     x29, x30, [sp, #-32]!
       4:       stp     x20, x19, [sp, #16]
       8:       mov     x29, sp
       c:       mov     x19, x1
      10:       mov     x20, x0
      14:       bl      0x14 <_Z2mvPKxPx+0x14>
                0000000000000014:  R_AARCH64_CALL26     __asan_load8
      18:       mov     x0, x19
      1c:       ldr     x20, [x20]
      20:       bl      0x20 <_Z2mvPKxPx+0x20>
                0000000000000020:  R_AARCH64_CALL26     __asan_store8
      24:       str     x20, [x19]
      28:       ldp     x20, x19, [sp, #16]
      2c:       ldp     x29, x30, [sp], #32
      30:       ret

Disassembly of section .text.asan.module_ctor:

0000000000000000 <asan.module_ctor>:
       0:       stp     x29, x30, [sp, #-16]!
       4:       mov     x29, sp
       8:       bl      0x8 <asan.module_ctor+0x8>
                0000000000000008:  R_AARCH64_CALL26     __asan_init
       c:       bl      0xc <asan.module_ctor+0xc>
                000000000000000c:  R_AARCH64_CALL26     __asan_version_mismatch_check_v8
      10:       ldp     x29, x30, [sp], #16
      14:       ret
$
$ clang++ --target=aarch64-linux-gnu -O1 -c mysan.cpp -o mysan.o
$ clang++ --target=aarch64-linux-gnu -stdlib=libc++ -O1 main.cpp mysan.o mv.o -o mysan
$ qemu-aarch64 ./mysan
__asan_load8(0x55000110c8)
__asan_store8(0x55000110d0)
```
