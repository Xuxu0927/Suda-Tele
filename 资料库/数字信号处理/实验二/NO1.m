load('x1.mat');
fs = 10000; 

% 设计FIR低通滤波器
N = 33; 
Fc = 2000; 
Fnyq = fs / 2;
Fc_normalized = Fc / Fnyq; % 归一化截止频率

% 使用hamming窗设计FIR滤波器
b = fir1(N, Fc_normalized, hamming(N+1));

% 应用滤波器
y = filter(b, 1, x1);

% 频谱分析
nfft = length(x1); 
f = (0:nfft-1)*(fs/nfft); 

% 计算原始信号的频谱
X1 = fft(x1, nfft); 
X1_mag = abs(X1/nfft); 

% 计算滤波后信号的频谱
Y = fft(y, nfft); 
Y_mag = abs(Y/nfft);

% 绘制频谱图
figure;
subplot(2,1,1);
plot(f, X1_mag);
title('原始信号的频谱');
xlabel('频率 (Hz)');
ylabel('幅度');
xlim([0 fs/2]);
grid on;

subplot(2,1,2);
plot(f, Y_mag);
title('滤波后信号的频谱');
xlabel('频率 (Hz)');
ylabel('幅度');
xlim([0 fs/2]);
grid on;

% 幅频响应和相频响应分析
fvtool(b, 1); 