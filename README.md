# Шаблон программы на языке C без тестирования

Заготовка программы находится в файле `main.c`.
Проще всего писать программу в этом файле. При необходимости можно его переименовать.

Программа может состоять из нескольких модулей.
При проверке компилируются все файлы с расширениями `.c` и `.cpp` в этом каталоге.

Поэтому перед отправкой нужно убедиться, что в последнем наборе изменений
записаны только нужные файлы

Программу можно писать на языке C++, если требования к заданию это допускают. Для этого нужно переименовать файл `main.c` в `main.cpp`.

## Проверка

В дополнение к автотестам в составе задания, шаблон содержит следующие общие проверки:

- `build` — собирает программу
    с проверками на утечку памяти и на выход за границы массива. Установлены настройки, при которых предупреждения компилятора считаются ошибками.
    Эта версия программы будет использоваться для  запуска тестов.
    Можно запустить на своём компьютере (локально) командой `make werror`

    В Ubuntu установить нужные программы, включая `git`, можно командой:

```
sudo apt-get install -y build-essential
```

- `lint` — выполняет стандартные проверки:
    - компиляция со всеми предупреждениями
    - проверка кода анализаторами `clang-tidy` и `cppcheck`
    - проверка форматирования кода анализатором `clang-format` (нужна версия 10)
    Если перечисленные средства установлены,
    проверку можно запустить локально командой `.github/lint.sh`.

    В Ubuntu установить нужные программы можно командой:

```
sudo apt-get install -y clang-tidy clang-format cppcheck
```

Некоторые замечания по результатам проверки `clang-tidy` можно исправить автоматически.
Для этого вызовите команду:

```
.github/clang-tidy.sh --fix-errors main.c
```

Файлы в каталоге `.github` студентам редактировать запрещено.

## Требования к форматированию кода

Не все требования к оформлению можно проверить автоматически.
Даже к программе, которая проходит проверку `clang-format` преподаватель может оставить замечания по оформлению, стилю идентификаторов и удобству чтения.
Общий стиль оформления близок к K&R.

Размер отступов — 4 пробела. Внутри каждого блока (внутри фигурных скобок) добавляется новый уровень отступа.

Фигурные скобки, открывающие блоки, пишутся на той же строке, что и операторы `if`, `for`, `while`, `do`, `switch`, через пробел.
На отдельной строке фигурные скобки пишутся в определении функций и пространств имён в C++.
Перед скобками после операторов `if`, `for`, `while`, `switch` ставится пробел.
Перед скобками с аргументами в вызове функции пробел НЕ ставится.

Если `clang-format` есть только более старых версий,
можно автоматически переформатировать код следующей командой.
Внимание: ключ `-i` переписывает файлы. Это может «испортить» форматирование, если в программе есть синтаксические ошибки.
Поэтому на всякий случай, сделайте коммит перед запуском `clang-format`.

```
.github/clang-format.sh -i ./main.cpp
```

Пример правильно отформатированного кода:

```c
#include <stdio.h>

void output(char character, char *line);

void output(char character, char *line)
{
    printf("Argument: %s\nFirst char: %c", line, character);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Not enough arguments: %d!\n", argc);
        return 1;
    }

    output(argv[1], argv[1][0]);
    return 0;
}
```

# Режимы сборки в Makefile

- `make` или `make all` — сборка программы с проверками на утечку памяти и на выход за границы массива.

- `make werror` — сборка программы с проверками на утечку памяти и на выход за границы массива в режиме, в котором предупреждения компилятора считаются ошибками.

- `make debug` — сборка программы в отладочном режиме без проверок на утечку памяти и на выход за границы массива.

- `make coverage` — сборка программы в режиме профилирования, в котором записывается количество выполнения каждой из строк исходного кода во время работы программы.