[f,Fs] = audioread('audio.wav'); 
close all
f1 = f(:,1); % ˫������ȡ����֮һ
f1 = f1';
dt = 1/Fs; %��������
L = length(f);  % �ź��ܳ���
start = 1;  
ending = L;
t = (start:ending)*dt;  %ʵ�ʵ�ʱ�䷶Χ

k=-600:600;
w1=3000*pi*k/600;   %[-3000pi:3000pi] ��Χ
F=f1*exp(-1i*t'*w1)*dt;  % ��������Ҷ�任������ͽ��ƻ��֣��ӷ������ھ���˷���
figure(1)
plot(t,f1);   % ʱ���ź�
figure(2)
plot(w1/2/pi,abs(F)); % ������ %������Ϊf
figure(3)
plot(w1/2/pi,angle(F)); %��λ��