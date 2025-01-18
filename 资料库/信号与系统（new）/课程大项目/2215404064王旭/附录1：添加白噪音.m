[audioSignal, fs] = audioread('clean.wav'); 

% 生成白噪音
noise = randn(size(audioSignal));

% 调整白噪音幅度
noise = noise * 0.1;

% 添加白噪音到音频信号
noisySignal = audioSignal + noise;

% 确保信号不会超出有符号整数的范围
noisySignal = min(max(noisySignal, -1), 1);

% 保存新的音频文件
audiowrite('noise.wav', noisySignal, fs); 