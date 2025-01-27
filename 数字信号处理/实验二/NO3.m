load('x1.mat'); 
fs = 10000; 

% 频率成分
f1 = 1700; 
f2 = 1850; 
f3 = 3550; 
f4 = 3750; 

% 设置截止频率的范围
Fc_start = f2; 
Fc_end = f3;

% 计算归一化截止频率
Fnyq = fs / 2; 

% 尝试不同的截止频率来找到最小的 N
min_N = Inf; % 初始设为无穷大
optimal_N = 0; % 最优阶数
optimal_Fc = Fc_start; % 最优截止频率

for Fc = linspace(Fc_start, Fc_end, 20) % 
    Fc_normalized = Fc / Fnyq;

    N = 2; % 初始滤波器阶数
    while true
        % 使用 Hamming 窗设计 FIR 高通滤波器
        b = fir1(N, Fc_normalized, 'high', hamming(N + 1));
        
        % 应用滤波器到信号上
        y = filter(b, 1, x1);
        
        % 计算滤波器的频率响应（用于验证）
        [h, f_resp] = freqz(b, 1, 1024, fs);
        
        % 检查在 f1, f2, f3, f4 处的增益是否满足要求
        gain_f1 = abs(interp1(f_resp, abs(h), f1, 'linear', 'extrap')); 
        gain_f2 = abs(interp1(f_resp, abs(h), f2, 'linear', 'extrap')); 
        gain_f3 = abs(interp1(f_resp, abs(h), f3, 'linear', 'extrap')); 
        gain_f4 = abs(interp1(f_resp, abs(h), f4, 'linear', 'extrap')); 
        
        % 将增益转换为 dB 并检查是否满足衰减要求
        if (20 * log10(gain_f1) <= -50 && 20 * log10(gain_f2) <= -50 && ...
            20 * log10(gain_f3) > -3 && 20 * log10(gain_f4) > -3)
            % 找到满足要求的滤波器
            if N < min_N
                min_N = N;
                optimal_N = N;
                optimal_Fc = Fc; % 记录当前的截止频率
            end
            break; 
        else
            N = N + 2; 
            if N > 100 
                break; 
            end
        end
    end
end

fprintf('最小满足要求的滤波器阶数 N 为：%d，对应的截止频率 Fc 为：%.2f Hz\n', optimal_N, optimal_Fc);

% 使用找到的最优参数对信号进行最终滤波
Fc_normalized = optimal_Fc / Fnyq;
b = fir1(optimal_N, Fc_normalized, 'high', hamming(optimal_N + 1));
y_optimal = filter(b, 1, x1);

% 计算FFT
nfft = length(x1) * 2;
X = fft(x1, nfft) / length(x1);
Y_optimal = fft(y_optimal, nfft) / length(y_optimal);
f = fs * (0:(nfft/2)) / nfft;

% 绘制原始信号和滤波后信号的频谱
figure;
subplot(2,1,1);
plot(f, 2 * abs(X(1:nfft/2 + 1)));
title('原始信号的频谱');
xlabel('频率 (Hz)');
ylabel('幅度');
grid on;

subplot(2,1,2);
plot(f, 2 * abs(Y_optimal(1:nfft/2 + 1)));
title('滤波后信号的频谱');
xlabel('频率 (Hz)');
ylabel('幅度');
grid on;

% 进行比较
figure;
plot(f, 2 * abs(X(1:nfft/2 + 1)), 'b', 'DisplayName', '原始信号');
hold on;
plot(f, 2 * abs(Y_optimal(1:nfft/2 + 1)), 'r', 'DisplayName', '滤波后信号');
title('原始信号与滤波后信号的频谱比较');
xlabel('频率 (Hz)');
ylabel('幅度');
grid on;
legend;
hold off;
