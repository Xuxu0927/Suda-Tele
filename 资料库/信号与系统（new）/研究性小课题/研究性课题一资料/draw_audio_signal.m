[f,Fs] = audioread('20220223_111950.m4a');
%close all

f1 = f(:,1); % ˫������ȡ����֮һ

T = 1/Fs; %��������

L = length(f);  % �ź��ܳ���

start = 1;  
ending = L;

t = [start:ending]*T;  %ʵ�ʵ�ʱ�䷶Χ
figure
plot(t,f1(start:ending));

