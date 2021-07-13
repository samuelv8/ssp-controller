T = readtable('dados.csv');
N = size(T);
N = N(1);
T0 = T.(1);
Tp = T.(2);

a0 = sum(T0) / N;
ap = sum(Tp) / N;

b = 20;
hold on;
h0 = histogram(T0, b, 'Normalization', 'pdf');
hp = histogram(Tp, b, 'Normalization', 'pdf');
xline(a0, 'b--');
xline(ap, 'r--');
xlim([0, 120])
legend({'malha fechada','presciente','', ''}, 'Location', 'northwest')