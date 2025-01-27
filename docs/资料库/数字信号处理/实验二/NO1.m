load('x1.mat');
fs = 10000; 

% ���FIR��ͨ�˲���
N = 33; 
Fc = 2000; 
Fnyq = fs / 2;
Fc_normalized = Fc / Fnyq; % ��һ����ֹƵ��

% ʹ��hamming�����FIR�˲���
b = fir1(N, Fc_normalized, hamming(N+1));

% Ӧ���˲���
y = filter(b, 1, x1);

% Ƶ�׷���
nfft = length(x1); 
f = (0:nfft-1)*(fs/nfft); 

% ����ԭʼ�źŵ�Ƶ��
X1 = fft(x1, nfft); 
X1_mag = abs(X1/nfft); 

% �����˲����źŵ�Ƶ��
Y = fft(y, nfft); 
Y_mag = abs(Y/nfft);

% ����Ƶ��ͼ
figure;
subplot(2,1,1);
plot(f, X1_mag);
title('ԭʼ�źŵ�Ƶ��');
xlabel('Ƶ�� (Hz)');
ylabel('����');
xlim([0 fs/2]);
grid on;

subplot(2,1,2);
plot(f, Y_mag);
title('�˲����źŵ�Ƶ��');
xlabel('Ƶ�� (Hz)');
ylabel('����');
xlim([0 fs/2]);
grid on;

% ��Ƶ��Ӧ����Ƶ��Ӧ����
fvtool(b, 1); 