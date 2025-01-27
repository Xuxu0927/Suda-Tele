cleanAudioFilePath = 'clean.wav'; 
noisyAudioFilePath = 'noise.wav'; 

% 读取未加噪声的音频文件
[cleanAudioSignal, fs] = audioread(cleanAudioFilePath);

% 确保音频信号是单声道
if isvector(cleanAudioSignal)
    cleanAudioSignal = cleanAudioSignal';
else
    cleanAudioSignal = cleanAudioSignal(:, 1); % 选择第一个通道
end

% 读取可能加噪声的音频文件
[noisyAudioSignal, fs] = audioread(noisyAudioFilePath);

% 设计IIR滤波器参数
n = 2; % 滤波器阶数，对于巴特沃斯滤波器，n通常为偶数
Wn = 3000 / (fs / 2); % 归一化截止频率
Rp = 1; % 通带波动
Rs = 60; % 阻带衰减

% 使用巴特沃斯滤波器设计IIR滤波器
[B, A] = butter(n, Wn, 'low'); 

% 应用IIR滤波器到加噪声的音频信号
filteredNoisySignal = filter(B, A, noisyAudioSignal);

% 绘制未加噪声的音频信号、加噪声的音频信号和滤波后的音频信号
timeVector = (0:length(noisyAudioSignal)-1) / fs; % 时间向量

figure;
subplot(3,1,1); % 第一个子图
plot(timeVector, cleanAudioSignal);
title('Clean Signal');
xlabel('时间 (秒)');
ylabel('幅值');

subplot(3,1,2); % 第二个子图
plot(timeVector, noisyAudioSignal);
title('Noise Signal');
xlabel('时间 (秒)');
ylabel('幅值');

subplot(3,1,3); % 第三个子图
plot(timeVector(1:length(filteredNoisySignal)), filteredNoisySignal);
title('IIR Signal');
xlabel('时间 (秒)');
ylabel('幅值');

% 保存滤波后的音频
outputFilePath = 'IIR clean.wav'; 
audiowrite(outputFilePath, filteredNoisySignal, fs); 