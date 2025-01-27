% 加载数据文件
load('x3.mat'); 
signal = x3;
Fs = 10000; 
N = 4000;   

% 时间向量
t = (0:N-1)/Fs;

% 画出信号时域波形
figure;
plot(t, signal);
title('信号时域波形');
xlabel('时间 (s)');
ylabel('幅度');

% 计算信号的FFT
Y = fft(signal);
P2 = abs(Y/N);
P1 = P2(1:N/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f = Fs*(0:(N/2))/N; % 频率向量

% 画出信号幅度谱
figure;
plot(f, P1);
title('信号幅度谱');
xlabel('频率 (Hz)');
ylabel('幅度');

% 绘制宽带谱图
window = 256; % 窗口大小
noverlap = window - 128; % 重叠大小
figure;
spectrogram(signal, window, noverlap, 256, Fs, 'yaxis');
title('宽带时频谱图');
xlabel('时间 (s)');
ylabel('频率 (Hz)');

% 绘制窄带谱图
window = 128; % 窗口大小
noverlap = window - 64; % 重叠大小
figure;
spectrogram(signal, window, noverlap, 256, Fs, 'yaxis');
title('窄带时频谱图');
xlabel('时间 (s)');
ylabel('频率 (Hz)');