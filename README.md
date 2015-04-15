# xrle - eXtreme Run Length Encoding
xrle is a compression algorithm inspired by RLE64 and lrrle.
Compared to RLE64 and lrrle 64 bit variant,xrle is faster while having
better compression ratio.
## Compile
    gcc -c -O3 xrle.c -o xrle.o
For some reason clang produces unoptimized executable.See
[here](https://llvm.org/bugs/show_bug.cgi?id=23202).
## License
BSD 2-Clause
