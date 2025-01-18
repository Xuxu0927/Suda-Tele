dt=0.001;
t=-15:dt:15;
f=(t>=-6)-(t>=6);  
k=-600:600;
w1=2*pi*k/600;   %[-2pi:2pi] 范围，可扩大
F=f*exp(-1i*t'*w1)*dt;  % 连续傅里叶变换，用求和近似积分，加法隐含在矩阵乘法中
figure(1)
plot(t,f);   % 时域信号
figure(2)
plot(w1,abs(F)); % 幅度谱
figure(3)
plot(w1,angle(F)); %相位谱