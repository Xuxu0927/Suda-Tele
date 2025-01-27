[f,Fs] = audioread('慢热 (clip).mp3');
%close all

f1 = f(:,1); % 双声道，取其中之一

T = 1/Fs; %采样点间隔

L = length(f);  % 信号总长度

start = 1;  
ending = L;

t = [start:ending]*T;  %实际的时间范围
figure
plot(t,f1(start:ending));

