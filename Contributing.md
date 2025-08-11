# Tools needed

| Tool | |
|-|-|
|clang-format| |


## useful commands

Format the project:

```bash
find src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i  
```