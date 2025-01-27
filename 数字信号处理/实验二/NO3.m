load('x1.mat'); 
fs = 10000; 

% Ƶ�ʳɷ�
f1 = 1700; 
f2 = 1850; 
f3 = 3550; 
f4 = 3750; 

% ���ý�ֹƵ�ʵķ�Χ
Fc_start = f2; 
Fc_end = f3;

% �����һ����ֹƵ��
Fnyq = fs / 2; 

% ���Բ�ͬ�Ľ�ֹƵ�����ҵ���С�� N
min_N = Inf; % ��ʼ��Ϊ�����
optimal_N = 0; % ���Ž���
optimal_Fc = Fc_start; % ���Ž�ֹƵ��

for Fc = linspace(Fc_start, Fc_end, 20) % 
    Fc_normalized = Fc / Fnyq;

    N = 2; % ��ʼ�˲�������
    while true
        % ʹ�� Hamming ����� FIR ��ͨ�˲���
        b = fir1(N, Fc_normalized, 'high', hamming(N + 1));
        
        % Ӧ���˲������ź���
        y = filter(b, 1, x1);
        
        % �����˲�����Ƶ����Ӧ��������֤��
        [h, f_resp] = freqz(b, 1, 1024, fs);
        
        % ����� f1, f2, f3, f4 ���������Ƿ�����Ҫ��
        gain_f1 = abs(interp1(f_resp, abs(h), f1, 'linear', 'extrap')); 
        gain_f2 = abs(interp1(f_resp, abs(h), f2, 'linear', 'extrap')); 
        gain_f3 = abs(interp1(f_resp, abs(h), f3, 'linear', 'extrap')); 
        gain_f4 = abs(interp1(f_resp, abs(h), f4, 'linear', 'extrap')); 
        
        % ������ת��Ϊ dB ������Ƿ�����˥��Ҫ��
        if (20 * log10(gain_f1) <= -50 && 20 * log10(gain_f2) <= -50 && ...
            20 * log10(gain_f3) > -3 && 20 * log10(gain_f4) > -3)
            % �ҵ�����Ҫ����˲���
            if N < min_N
                min_N = N;
                optimal_N = N;
                optimal_Fc = Fc; % ��¼��ǰ�Ľ�ֹƵ��
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

fprintf('��С����Ҫ����˲������� N Ϊ��%d����Ӧ�Ľ�ֹƵ�� Fc Ϊ��%.2f Hz\n', optimal_N, optimal_Fc);

% ʹ���ҵ������Ų������źŽ��������˲�
Fc_normalized = optimal_Fc / Fnyq;
b = fir1(optimal_N, Fc_normalized, 'high', hamming(optimal_N + 1));
y_optimal = filter(b, 1, x1);

% ����FFT
nfft = length(x1) * 2;
X = fft(x1, nfft) / length(x1);
Y_optimal = fft(y_optimal, nfft) / length(y_optimal);
f = fs * (0:(nfft/2)) / nfft;

% ����ԭʼ�źź��˲����źŵ�Ƶ��
figure;
subplot(2,1,1);
plot(f, 2 * abs(X(1:nfft/2 + 1)));
title('ԭʼ�źŵ�Ƶ��');
xlabel('Ƶ�� (Hz)');
ylabel('����');
grid on;

subplot(2,1,2);
plot(f, 2 * abs(Y_optimal(1:nfft/2 + 1)));
title('�˲����źŵ�Ƶ��');
xlabel('Ƶ�� (Hz)');
ylabel('����');
grid on;

% ���бȽ�
figure;
plot(f, 2 * abs(X(1:nfft/2 + 1)), 'b', 'DisplayName', 'ԭʼ�ź�');
hold on;
plot(f, 2 * abs(Y_optimal(1:nfft/2 + 1)), 'r', 'DisplayName', '�˲����ź�');
title('ԭʼ�ź����˲����źŵ�Ƶ�ױȽ�');
xlabel('Ƶ�� (Hz)');
ylabel('����');
grid on;
legend;
hold off;
