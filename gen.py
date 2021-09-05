#!/usr/bin/python3

"""
generate '.md' files by '.cpp / .h'
"""

import os

index_root = """
# OI Algorithm

jasonfan 的算法模板。

**[GitHub 仓库](https://github.com/jason-fxz/algorithm)**

## Copyleft

See [CC0 LICENSE](LICENSE)

---

## 目录

"""

index_dirs = """
# {0} | OI Algorithm

---

## 目录

- [**Go Back**](././)
"""

index_files = """
# {0} | {1} | OI Algorithm

[**Go Back**](././)

---

```cpp
{2}
```

---

[**Go Back**](././)
"""

def Writetext(filepath, text):
    f = open(filepath, "w")
    f.write(text)
    f.close()
    

def Readtext(filepath):
    f = open(filepath, "r")
    text = f.read()
    f.close()
    return text
    

if __name__ == "__main__":

    for root, dirs, files in os.walk("./"):
        if root.find("/.") != -1 or root == "./":
            continue
        # print("root =", root)
        category = root[2:]
        index_root += "- [{0}]({1})\n".format(category.upper(), root + "/")
        index_dir = index_dirs.format(category.upper())
        for f in files:
            file_name, file_ext = os.path.splitext(f)
            file_path = os.path.join(root, f)
            if file_ext in [".cpp", ".h"]:
                index_dir += "- [{0}]({1})\n".format(file_name + file_ext, file_name + '.md')
                Writetext(os.path.join(root, file_name + '.md'), index_files.format(
                    file_name + file_ext, category.upper(), Readtext(file_path)
                ))
                pass
        Writetext(os.path.join(root, 'index.md'), index_dir)

    Writetext('./index.md', index_root)