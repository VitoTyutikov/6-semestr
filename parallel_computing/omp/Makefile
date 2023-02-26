FLAGS = -Wall -Werror -Wextra -Wfloat-equal -Warray-bounds -Wdouble-promotion -std=c++17 -fopenmp

all:t1 t2 t3 t4 t5 t6 t7 t8 t9 t10 t11 t12 t13
	mkdir build
t1:src/hello_world_with_8_threads.cpp
	g++ $(FLAGS) src/hello_world_with_8_threads.cpp -o build/t1.out

t2:src/parallel_if.cpp
	g++  $(FLAGS) src/parallel_if.cpp -o build/t2.out

t3: src/private_firstprivate.cpp
	g++  $(FLAGS) src/private_firstprivate.cpp -o build/t3.out

t4: src/max_min_in_array.cpp
	g++  $(FLAGS) src/max_min_in_array.cpp -o build/t4.out

t5: src/sections.cpp
	g++  $(FLAGS) src/sections.cpp -o build/t5.out

t6: src/reduction.cpp
	g++  $(FLAGS) src/reduction.cpp -o build/t6.out

t7: src/schedule.cpp
	g++  $(FLAGS) src/schedule.cpp -o build/t7.out

t8: src/time_schedule.cpp
	g++  $(FLAGS) src/time_schedule.cpp -o build/t8.out

t9: src/matrix_mult_vector.cpp
	g++  $(FLAGS) src/matrix_mult_vector.cpp -o build/t9.out

t10: src/critical.cpp
	g++  $(FLAGS) src/critical.cpp -o build/t10.out

t11: src/atomic.cpp
	g++  $(FLAGS) src/atomic.cpp -o build/t11.out

t12: src/lock.cpp
	g++  $(FLAGS) src/lock.cpp -o build/t12.out

t13: src/modify_hello_world.cpp
	g++  $(FLAGS) src/modify_hello_world.cpp -o build/t13.out

run_all:
	build/t1.out && build/t2.out && build/t3.out && build/t4.out &&\
	build/t5.out && build/t6.out && build/t7.out && build/t8.out &&\
	build/t9.out && build/t10.out && build/t11.out && build/t12.out && build/t13.out









clean:
	rm -rf build/*.out
	clear