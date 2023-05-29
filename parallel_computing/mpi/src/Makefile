

all:build run


run:
	@echo TASK1
	@echo
	@mpiexec -n 16 ../build/task1
	@echo
	@echo
	@echo TASK2
	@echo
	@mpiexec -n 16 ../build/task2
	@echo
	@echo
	@echo TASK3
	@echo
	@mpiexec -n 16 ../build/task3
	@echo
	@echo
	@echo TASK4
	@echo
	@mpiexec -n 16 ../build/task4
	@echo
	@echo
	@echo TASK5
	@echo
	@mpiexec -n 16 ../build/task5
	@echo
	@echo
	@echo TASK6
	@echo
	@mpiexec -n 16 ../build/task6
	@echo
	@echo
	@echo TASK7
	@echo
	@mpiexec -n 16 ../build/task7
	@echo
	@echo
	@echo TASK8
	@echo
	@mpiexec -n 16 ../build/task8
	@echo
	@echo
	@echo TASK9
	@echo
	@mpiexec -n 2 ../build/task9
	@echo
	@echo
	@echo TASK10
	@echo
	@mpiexec -n 2 ../build/task10
	@echo
	@echo
	@echo TASK11
	@echo
	@mpiexec -n 16 ../build/task11
	@echo
	@echo
	@echo FLOYD
	@echo
	@mpiexec -n 16 ../build/floyd

build:task1.c task2.c task3.c task4.c task5.c task6.c task7.c task8.c task9.c task10.c task11.c
	@mpicc task1.c -o ../build/task1
	@mpicc task2.c -o ../build/task2
	@mpicc task3.c -o ../build/task3
	@mpicc task4.c -o ../build/task4
	@mpicc task5.c -o ../build/task5
	@mpicc task6.c -o ../build/task6
	@mpicc task7.c -o ../build/task7
	@mpicc task8.c -o ../build/task8
	@mpicc task9.c -o ../build/task9
	@mpicc task10.c -o ../build/task10
	@mpicc task11.c -o ../build/task11
	@mpicc floyd.c -o ../build/floyd

clean:
	rm -rf ../build/*