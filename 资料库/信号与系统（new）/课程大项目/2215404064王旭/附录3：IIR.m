cleanAudioFilePath = 'clean.wav'; 
noisyAudioFilePath = 'noise.wav'; 

% ��ȡδ����������Ƶ�ļ�
[cleanAudioSignal, fs] = audioread(cleanAudioFilePath);

% ȷ����Ƶ�ź��ǵ�����
if isvector(cleanAudioSignal)
    cleanAudioSignal = cleanAudioSignal';
else
    cleanAudioSignal = cleanAudioSignal(:, 1); % ѡ���һ��ͨ��
end

% ��ȡ���ܼ���������Ƶ�ļ�
[noisyAudioSignal, fs] = audioread(noisyAudioFilePath);

% ���IIR�˲�������
n = 2; % �˲������������ڰ�����˹�˲�����nͨ��Ϊż��
Wn = 3000 / (fs / 2); % ��һ����ֹƵ��
Rp = 1; % ͨ������
Rs = 60; % ���˥��

% ʹ�ð�����˹�˲������IIR�˲���
[B, A] = butter(n, Wn, 'low'); 

% Ӧ��IIR�˲���������������Ƶ�ź�
filteredNoisySignal = filter(B, A, noisyAudioSignal);

% ����δ����������Ƶ�źš�����������Ƶ�źź��˲������Ƶ�ź�
timeVector = (0:length(noisyAudioSignal)-1) / fs; % ʱ������

figure;
subplot(3,1,1); % ��һ����ͼ
plot(timeVector, cleanAudioSignal);
title('Clean Signal');
xlabel('ʱ�� (��)');
ylabel('��ֵ');

subplot(3,1,2); % �ڶ�����ͼ
plot(timeVector, noisyAudioSignal);
title('Noise Signal');
xlabel('ʱ�� (��)');
ylabel('��ֵ');

subplot(3,1,3); % ��������ͼ
plot(timeVector(1:length(filteredNoisySignal)), filteredNoisySignal);
title('IIR Signal');
xlabel('ʱ�� (��)');
ylabel('��ֵ');

% �����˲������Ƶ
outputFilePath = 'IIR clean.wav'; 
audiowrite(outputFilePath, filteredNoisySignal, fs); 