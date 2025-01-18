% ���������ļ�
load('x1.mat'); 
signal = x1; 

N = 1000; % ���ڳ���
if length(signal) > N
    signal = signal(1:N); % ����źų��ȳ������ڳ��ȣ���ȡǰN������
elseif length(signal) < N
    signal = [signal; zeros(1, N - length(signal))]; % ����źų��Ȳ��㴰�ڳ��ȣ�����
end

% �����ź�ʱ����
Fs = 10000;
t = (0:length(signal)-1)/Fs; 
figure;
plot(t, signal);
title('�ź�ʱ����');
xlabel('ʱ�� (s)');
ylabel('����');

% �����źŵķ�����
Y = fft(signal); % ���ٸ���Ҷ�任
P2 = abs(Y/length(signal)); % ˫����
P1 = P2(1:N/2+1); % ������
P1(2:end-1) = 2*P1(2:end-1); % ���ڶԳ��ԣ�ֻȡһ��
f = Fs*(0:(N/2))/N; % Ƶ������

% �����źŷ�����
figure;
plot(f, P1);
title('�źŷ�����');
xlabel('Ƶ�� (Hz)');
ylabel('����');

% ʶ���ĸ���Ϊ��Ҫ��Ƶ�ʳɷ�
[~, idx] = sort(P1, 'descend');
main_freqs = f(idx(1:4)); % �����ĸ�����Ƶ��ֵ

% ����ĸ���Ϊ��Ҫ��Ƶ�ʳɷ�
disp('�ĸ���Ϊ��Ҫ��Ƶ�ʳɷ֣�Hz��:');
disp(main_freqs);