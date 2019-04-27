# README #

@Data   : 2019/03/12

@Author : lwp

## 简介

`mytrace` 是一款 `C` 语言的函数动态调用关系追踪程序.（程序运行时未执行到的函数不会被追踪）

## 安装

``` sh
make
make install
```

## 使用

1. 使用 gcc 的 `-g -finstrument-functions` 选项将 `instrument.c` 文件与要追踪分析的程序(例如：`test1.c`, `test2.c`, `test3.c`)编译成可执行程序 `test`.

``` sh
gcc -g -finstrument-functions instrument.c test1.c test2.c test3.c -o test
```

2.执行 `test` 可执行文件, 会在 `test` 执行目录下生成追踪文件 `trace.txt` 文件.

``` sh
./test
```

`trace.txt` 文件内容形式如下：

    E0x40b5b4
    E0x44affc
    X0x44affc
    E0x40c747
    E0x427881
    X0x427881
    X0x40c747
    X0x40b5b4

`E0x40b5b4` 代表的是进入函数 `0x40b5b4`;
`X0x40b5b4` 代表的是退出函数 `0x40b5b4`;
`0x40b5b4` 则代表的是函数的地址.

3.使用 `mytrace` 程序分析 `trace.txt` 文件, 将函数地址转换成函数名.

``` sh
mytrace test trace.txt
```

会在终端输出类似下列形式的函数调用关系:

    --> main()
        --> test1()
        <-- test1()
        --> test2()
            --> test3()
            <-- test3()
        <-- test2()
    <-- main()

## 参考资料

[用Graphviz可视化函数调用](https://www.ibm.com/developerworks/cn/linux/l-graphvis/)

说明：`mytrace` 是根据 `pvtrace` 改造而成的. 之所以没有使用文章中提供的 `pvtrace` 程序, 主要是分析大型代码(例如：nginx)时, 函数调用关系复杂, 一张图片难以明了, 故改造成了 `mytrace` 程序将调用关系输出到文本中, 使用 vim 查看函数调用关系还是比较方便的.
