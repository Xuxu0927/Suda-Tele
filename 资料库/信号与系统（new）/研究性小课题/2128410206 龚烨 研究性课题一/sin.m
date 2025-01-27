t = -1 : 0.001 : 1;

A = 2;
f = 3 / 2;
phi = pi / 2;
w0 = 2 * pi * f;
x = A * sin(w0 * t + phi);
subplot(1, 1, 1);
plot(t, x);
axis([-1, 1, -3, 3])
xlabel('t');
ylabel('x');

