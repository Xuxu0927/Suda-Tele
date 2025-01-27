%例2-8

dt = 0.01;
T = 5;
x = -T:dt:T;
f1 = zeros(1,length(x));
f2 = zeros(1,length(x));
f1(x>-1 & x<=1) = 1;
f2(x> 0 & x<2) = 2;
plot(x,f1,'r',x,f2,'g');
f = conv(f1,f2)*dt;
xf = 2*x(1):dt:2*x(end);
figure
plot(xf,f)
