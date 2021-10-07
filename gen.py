#!/usr/bin/python3

"""
generate '.md' files by '.cpp / .h' to public/
"""

import os
import shutil

include_exts = [".cpp", ".h", ".hpp", ".c", ".py"]

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

- [**Go Back**](./../)
"""

index_files = """
# {0} | {1} | OI Algorithm

[**Go Back**](./)

---

```cpp
{2}
```

---

[**Go Back**](./)
"""


def LogINFO(info):
    print("\033[1m\033[32mINFO \033[0m", info)

def topublic(path):
    return './public' + path[1:]

def Writetext(filepath, text):
    f = open(filepath, "w")
    f.write(text)
    f.close()
    LogINFO("generated: \033[35m" + filepath + "\033[0m")

def Readtext(filepath):
    f = open(filepath, "r")
    text = f.read()
    f.close()
    # LogINFO("loaded\t" + filepath)
    return text


count_files = dict()


def PrintStatistics():
    info = "Show statistics\n\n\033[1mCategory    Count\033[0m\n"
    tot_file = 0

    for cate in count_files:
        info += "{0:<12}{1}\n".format(cate, count_files[cate])
        tot_file += count_files[cate]

    info += "{0:<12}{1}\n".format("TOTAL", tot_file)
    LogINFO(info)


if __name__ == "__main__":
    LogINFO("Start processing")
    shutil.rmtree('public', ignore_errors=True)
    os.mkdir('public')
    for root, dirs, files in os.walk("./"):
        if root.find("/.") != -1 or root == "./" or root.find('public') != -1:
            continue

        os.mkdir(topublic(root))

        category = root[2:]
        count_files[category] = 0
        index_root += "- [{0}]({1})\n".format(category.upper(), root + "/")
        index_dir = index_dirs.format(category.upper())

        for f in files:
            file_name, file_ext = os.path.splitext(f)
            file_path = os.path.join(root, f)
            if file_ext in include_exts:
                count_files[category] += 1
                index_dir += "- [{0}]({1})\n".format(
                    file_name + file_ext, file_name + ".md"
                )
                Writetext(
                    topublic(os.path.join(root, file_name + ".md")),
                    index_files.format(
                        file_name + file_ext, category.upper(), Readtext(file_path)
                    ),
                )
        Writetext(topublic(os.path.join(root, "index.md")), index_dir)

    Writetext(topublic("./index.md"), index_root)
    PrintStatistics()
