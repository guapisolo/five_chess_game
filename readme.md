通过 utf-8 编码
编译 g++ *.cpp -o test.exe -g -O3
运行 ./test.exe

核心算法是迭代加深搜索和minmax搜素，加了alpha-beta剪枝和，zobrist哈希记忆化
详细设计见实验报告

由于课程没有要求，因此ui较丑，见谅

have fun