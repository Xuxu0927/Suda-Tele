dt = 0.01;
T = 5;
x = -T:dt:T;
f1 = zeros(1,length(x));
f2 = zeros(1,length(x));
f1(x>=0) = 1;
t = 0:dt:5;
f2(x>= 0 & x<=5) = t;
plot(x,f1,'r',x,f2,'g');
f = conv(f1,f2)*dt;
xf = 2*x(1):dt:2*x(end);
figure
plot(xf,f)