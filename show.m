clear ; close all; clc
axis([0,1,0,1]);

% Load Data
points = load('Training.dat');
vals = load('Predicted_values.dat');

X = points(:, [1, 2]); y = vals(:, 1);
fprintf(['Plotting data with + indicating (y = 1) examples and o ' ...
         'indicating (y = 0) examples.\n']);

pos = find(y==1); neg = find(y == 0);
% Plot provided data
hold on;
plot(X(pos, 1), X(pos, 2), 'k+','LineWidth', 2, 'MarkerSize', 4);
plot(X(neg, 1), X(neg, 2), 'ko', 'MarkerFaceColor', 'y', 'MarkerSize', 4);
xlabel('X-axis');
ylabel('Y-axis');


system('g++ svm.cpp Matrix.cpp Math.cpp');
system('./a.out');
test = load('test.dat');
sol = load('sol.dat');

test
sol
pos = find(sol==1); neg = find(sol == 0);
plot(test(pos, 1), test(pos, 2), 'k+','LineWidth', 2, 'MarkerSize', 9);
plot(test(neg, 1), test(neg, 2), 'ko', 'MarkerFaceColor', 'y', 'MarkerSize', 9);

hold off;
