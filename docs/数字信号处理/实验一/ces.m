% ���������ļ�
load('x3.mat'); 
signal = x3;
Fs = 10000; 
N = 4000;   

% ʱ������
t = (0:N-1)/Fs;

% �����ź�ʱ����
figure;
plot(t, signal);
title('�ź�ʱ����');
xlabel('ʱ�� (s)');
ylabel('����');

% �����źŵ�FFT
Y = fft(signal);
P2 = abs(Y/N);
P1 = P2(1:N/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f = Fs*(0:(N/2))/N; % Ƶ������

% �����źŷ�����
figure;
plot(f, P1);
title('�źŷ�����');
xlabel('Ƶ�� (Hz)');
ylabel('����');

% ���ƿ����ͼ
window = 256; % ���ڴ�С
noverlap = window - 128; % �ص���С
figure;
spectrogram(signal, window, noverlap, 256, Fs, 'yaxis');
title('���ʱƵ��ͼ');
xlabel('ʱ�� (s)');
ylabel('Ƶ�� (Hz)');

% ����խ����ͼ
window = 128; % ���ڴ�С
noverlap = window - 64; % �ص���С
figure;
spectrogram(signal, window, noverlap, 256, Fs, 'yaxis');
title('խ��ʱƵ��ͼ');
xlabel('ʱ�� (s)');
ylabel('Ƶ�� (Hz)');