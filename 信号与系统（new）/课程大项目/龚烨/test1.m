[f,Fs] = audioread('audio.wav'); 
close all
f1 = f(1:11730,1); % ˫������ȡ����֮һ
f1 = f1';
dt = 1/Fs; %��������
L = 11730;  % �ź��ܳ���
start = 1;  
ending = L;
t = (start:ending)*dt;  %ʵ�ʵ�ʱ�䷶Χ


w1=0:1000 * 2 * pi;   
F=f1*exp(-1i*t'*w1)*dt;  % ��������Ҷ�任������ͽ��ƻ��֣��ӷ������ھ���˷���
figure(1)
plot(t,f1);   % ʱ���ź�
figure(2)
plot(w1 / 2 / pi, abs(F)); % ������ %������Ϊf