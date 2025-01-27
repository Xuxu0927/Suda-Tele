% ��ȡ��Ƶ�ļ�
[audioIn, Fs] = audioread('music.mp3'); 

% ����ʱ����
t = (0:length(audioIn)-1)/Fs; % ʱ������
figure;
plot(t, audioIn);
title('ʱ�����');
xlabel('Time (s)');
ylabel('Amplitude');

% ����Ƶ��
Y = fft(audioIn);
L = length(audioIn); % �źų���
P2 = abs(Y/L); % ˫��Ƶ��
P1 = P2(1:L/2+1); % ����Ƶ��
P1(2:end-1) = 2*P1(2:end-1); % ���ڶԳ��ԣ�ֻȡһ��

% ����Ƶ��ͼ
f = Fs*(0:(L/2))/L; % Ƶ������
figure;
plot(f, P1);
title('Ƶ�׷���');
xlabel('Frequency (Hz)');
ylabel('Magnitude');