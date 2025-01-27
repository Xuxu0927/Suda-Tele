cleanAudioFilePath = 'clean.wav'; 
noiseAudioFilePath = 'noise.wav'; 

% ��ȡδ����������Ƶ�ļ�
[cleanAudioSignal, fs] = audioread(cleanAudioFilePath);

% ȷ����Ƶ�ź��ǵ�����
if isvector(cleanAudioSignal)
    cleanAudioSignal = cleanAudioSignal';
else
    cleanAudioSignal = cleanAudioSignal(:, 1); % ѡ���һ��ͨ��
end

% ��ȡ����������Ƶ�ļ�
[noisyAudioSignal, fs] = audioread(noisyAudioFilePath);


% ���FIR�˲�������
n = 31; % �˲�������
cutoff = 3000; % ��ֹƵ�ʣ���������ֻ����3kHz���µ�Ƶ��
b = fir1(n, cutoff/(fs/2)); % ʹ�ô����������FIR�˲���

% Ӧ��FIR�˲���������������Ƶ�ź�
filteredNoisySignal = filter(b, 1, noisyAudioSignal);

% ����δ����������Ƶ�źš�����������Ƶ�źź��˲������Ƶ�ź�
timeVector = (0:length(noisyAudioSignal)-1) / fs;

% ����ͼ�δ���
figure;
subplot(3,1,1); % ��һ����ͼ
plot(timeVector, cleanAudioSignal);
title('Clean Signal');
xlabel('ʱ�䣨�룩');
ylabel('��ֵ');

subplot(3,1,2); % �ڶ�����ͼ
plot(timeVector, noisyAudioSignal);
title('Noise Signal');
xlabel('ʱ�䣨�룩');
ylabel('��ֵ');

subplot(3,1,3); % ��������ͼ
plot(timeVector(1:length(filteredNoisySignal)), filteredNoisySignal);
title('FFR Signal');
xlabel('ʱ�䣨�룩');
ylabel('��ֵ');


% �����˲������Ƶ
outputFilePath = 'FIR clean.wav'; 
audiowrite(outputFilePath, filteredNoisySignal, fs); 