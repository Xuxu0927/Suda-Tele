% 读取音频文件
[audioIn, Fs] = audioread('music.mp3'); 

% 绘制时域波形
t = (0:length(audioIn)-1)/Fs; % 时间向量
figure;
plot(t, audioIn);
title('时域分析');
xlabel('Time (s)');
ylabel('Amplitude');

% 计算频谱
Y = fft(audioIn);
L = length(audioIn); % 信号长度
P2 = abs(Y/L); % 双边频谱
P1 = P2(1:L/2+1); % 单边频谱
P1(2:end-1) = 2*P1(2:end-1); % 由于对称性，只取一半

% 绘制频谱图
f = Fs*(0:(L/2))/L; % 频率向量
figure;
plot(f, P1);
title('频谱分析');
xlabel('Frequency (Hz)');
ylabel('Magnitude');