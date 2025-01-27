cleanAudioFilePath = 'clean.wav'; 
noiseAudioFilePath = 'noise.wav'; 

% 读取未加噪声的音频文件
[cleanAudioSignal, fs] = audioread(cleanAudioFilePath);

% 确保音频信号是单声道
if isvector(cleanAudioSignal)
    cleanAudioSignal = cleanAudioSignal';
else
    cleanAudioSignal = cleanAudioSignal(:, 1); % 选择第一个通道
end

% 读取加噪声的音频文件
[noisyAudioSignal, fs] = audioread(noisyAudioFilePath);


% 设计FIR滤波器参数
n = 31; % 滤波器阶数
cutoff = 3000; % 截止频率，假设我们只保留3kHz以下的频率
b = fir1(n, cutoff/(fs/2)); % 使用窗函数法设计FIR滤波器

% 应用FIR滤波器到加噪声的音频信号
filteredNoisySignal = filter(b, 1, noisyAudioSignal);

% 绘制未加噪声的音频信号、加噪声的音频信号和滤波后的音频信号
timeVector = (0:length(noisyAudioSignal)-1) / fs;

% 创建图形窗口
figure;
subplot(3,1,1); % 第一个子图
plot(timeVector, cleanAudioSignal);
title('Clean Signal');
xlabel('时间（秒）');
ylabel('幅值');

subplot(3,1,2); % 第二个子图
plot(timeVector, noisyAudioSignal);
title('Noise Signal');
xlabel('时间（秒）');
ylabel('幅值');

subplot(3,1,3); % 第三个子图
plot(timeVector(1:length(filteredNoisySignal)), filteredNoisySignal);
title('FFR Signal');
xlabel('时间（秒）');
ylabel('幅值');


% 保存滤波后的音频
outputFilePath = 'FIR clean.wav'; 
audiowrite(outputFilePath, filteredNoisySignal, fs); 