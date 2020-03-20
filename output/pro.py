import pstats

# 创建Stats对象
p = pstats.Stats("single.out")

# strip_dirs(): 去掉无关的路径信息
# sort_stats(): 排序，支持的方式和上述的一致
# print_stats(): 打印分析结果，可以指定打印前几行

# 和直接运行cProfile.run("test()")的结果是一样的
#p.strip_dirs().sort_stats(-1).print_stats()

# 按照函数名排序，只打印前3行函数的信息, 参数还可为小数,表示前百分之几的函数信息 
#p.strip_dirs().sort_stats("name").print_stats(10.0)

# 按照运行时间和函数名进行排序
p.strip_dirs().sort_stats("cumulative").print_stats(20)
#p.print_callees("slice_gradient")
p.print_callees("pull_parameter")
# 如果想知道有哪些函数调用了sum_num
#p.print_callers(0.5, "sum_num")

# 查看test()函数中调用了哪些函数
#p.print_callees("test")

# 创建Stats对象
#p = pstats.Stats("local.out")

#p.strip_dirs().sort_stats("cumulative").print_stats(20)
#p.print_callees("train")
