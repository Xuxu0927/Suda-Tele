[f,Fs] = audioread('2023a.mp3');  % ��Ƶ�ļ�
%close all

f1 = f(:,1); % ˫������ȡ����֮һ

T = 1/Fs; % ��������

L = length(f);  % �ź��ܳ���

start = 1;  
ending = L;

t = [start:ending]*T;  % ʵ�ʵ�ʱ�䷶Χ
figure
plot(t,f1(start:ending));
