[audioSignal, fs] = audioread('clean.wav'); 

% ���ɰ�����
noise = randn(size(audioSignal));

% ��������������
noise = noise * 0.1;

% ��Ӱ���������Ƶ�ź�
noisySignal = audioSignal + noise;

% ȷ���źŲ��ᳬ���з��������ķ�Χ
noisySignal = min(max(noisySignal, -1), 1);

% �����µ���Ƶ�ļ�
audiowrite('noise.wav', noisySignal, fs); 