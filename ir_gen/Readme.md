# LLVM IR Generation

## Usage:
```
clang++ `llvm-config --cppflags --ldflags --libs` irgen.cpp -lSDL2
```

## Now run:
```
./a.out
```

## Dump generated IR:
```
./a.out > irgen.ll
```

## You can `diff` with compiler created file:
```
diff -I -W --width=200 --minimal --color -y irgen.ll ../src/app.ll
``` 