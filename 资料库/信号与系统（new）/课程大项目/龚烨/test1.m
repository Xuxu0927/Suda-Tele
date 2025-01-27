[f,Fs] = audioread('audio.wav'); 
close all
f1 = f(1:11730,1); % 双声道，取其中之一
f1 = f1';
dt = 1/Fs; %采样点间隔
L = 11730;  % 信号总长度
start = 1;  
ending = L;
t = (start:ending)*dt;  %实际的时间范围


w1=0:1000 * 2 * pi;   
F=f1*exp(-1i*t'*w1)*dt;  % 连续傅里叶变换，用求和近似积分，加法隐含在矩阵乘法中
figure(1)
plot(t,f1);   % 时域信号
figure(2)
plot(w1 / 2 / pi, abs(F)); % 幅度谱 %横坐标为f