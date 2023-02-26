FLAGS = -Wall -Werror -Wextra -Wfloat-equal -Warray-bounds -Wdouble-promotion -std=c++17 -fopenmp

all:t1 t2 t3 t4 t5 t6 t7 t8 t9 t10 t11 t12 t13

t1:src/hello_world_with_8_threads.cpp build_exists
	g++ $(FLAGS) src/hello_world_with_8_threads.cpp -o build/t1.out

t2:src/parallel_if.cpp build_exists
	g++  $(FLAGS) src/parallel_if.cpp -o build/t2.out

t3: src/private_firstprivate.cpp build_exists
	g++  $(FLAGS) src/private_firstprivate.cpp -o build/t3.out

t4: src/max_min_in_array.cpp build_exists
	g++  $(FLAGS) src/max_min_in_array.cpp -o build/t4.out

t5: src/sections.cpp build_exists
	g++  $(FLAGS) src/sections.cpp -o build/t5.out

t6: src/reduction.cpp build_exists
	g++  $(FLAGS) src/reduction.cpp -o build/t6.out

t7: src/schedule.cpp build_exists
	g++  $(FLAGS) src/schedule.cpp -o build/t7.out

t8: src/time_schedule.cpp build_exists
	g++  $(FLAGS) src/time_schedule.cpp -o build/t8.out

t9: src/matrix_mult_vector.cpp build_exists
	g++  $(FLAGS) src/matrix_mult_vector.cpp -o build/t9.out

t10: src/critical.cpp build_exists
	g++  $(FLAGS) src/critical.cpp -o build/t10.out

t11: src/atomic.cpp build_exists
	g++  $(FLAGS) src/atomic.cpp -o build/t11.out

t12: src/lock.cpp build_exists
	g++  $(FLAGS) src/lock.cpp -o build/t12.out

t13: src/modify_hello_world.cpp
	g++  $(FLAGS) src/modify_hello_world.cpp -o build/t13.out

run_all:all
	build/t1.out && build/t2.out && build/t3.out && build/t4.out &&\
	build/t5.out && build/t6.out && build/t7.out && build/t8.out &&\
	build/t9.out && build/t10.out && build/t11.out && build/t12.out && build/t13.out


build_exists:
	@if [ ! -d build ] ; then echo "creating build" ; mkdir build; fi








clean:
	rm -rf build/*.out
	clear