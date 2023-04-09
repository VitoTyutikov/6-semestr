clc;clear;
n = 10:10:1000; % порядки матриц

% создаем пустые массивы для времени выполнения операций
time_square = zeros(size(n));
time_upper = zeros(size(n));
time_lower = zeros(size(n));

for i = 1:length(n)
    A = randi([1 10], n(i), n(i)); % создаем матрицу размера n(i) x n(i) со случайными значениями от 1 до 10
    
    % замеряем время выполнения операции возведения матрицы в квадрат
    tic
    A_sq = A^2;
    time_square(i) = toc;
    
    % замеряем время выполнения операции для верхней треугольной матрицы
    tic
    A_upper = triu(A) + triu(A, 1)';
    time_upper(i) = toc;
    
    % замеряем время выполнения операции для нижней треугольной матрицы
    tic
    A_lower = tril(A) + tril(A, -1)';
    time_lower(i) = toc;
end

% строим графики
plot(n, time_square, n, time_upper,n, time_lower)
grid on
legend('A^2', 'Верхняя треуг. матрица', 'Нижняя треуг. матрица')
xlabel('Порядок матрицы')
ylabel('Время выполнения, с')

% Вывод: из графика видно, что время выполнения операции возведения в квадрат
% растет квадратично с увеличением порядка матрицы. Также можно заметить, что 
% время выполнения операции для треугольных матриц занимает меньше времени,
% чем для полных матриц.



