% 加载数据文件
load('x1.mat'); 
signal = x1; 

N = 1000; % 窗口长度
if length(signal) > N
    signal = signal(1:N); % 如果信号长度超过窗口长度，截取前N个样本
elseif length(signal) < N
    signal = [signal; zeros(1, N - length(signal))]; % 如果信号长度不足窗口长度，补零
end

% 画出信号时域波形
Fs = 10000;
t = (0:length(signal)-1)/Fs; 
figure;
plot(t, signal);
title('信号时域波形');
xlabel('时间 (s)');
ylabel('幅度');

% 计算信号的幅度谱
Y = fft(signal); % 快速傅里叶变换
P2 = abs(Y/length(signal)); % 双边谱
P1 = P2(1:N/2+1); % 单边谱
P1(2:end-1) = 2*P1(2:end-1); % 由于对称性，只取一半
f = Fs*(0:(N/2))/N; % 频率向量

% 画出信号幅度谱
figure;
plot(f, P1);
title('信号幅度谱');
xlabel('频率 (Hz)');
ylabel('幅度');

% 识别四个最为主要的频率成分
[~, idx] = sort(P1, 'descend');
main_freqs = f(idx(1:4)); % 返回四个最大的频率值

% 输出四个最为主要的频率成分
disp('四个最为主要的频率成分（Hz）:');
disp(main_freqs);