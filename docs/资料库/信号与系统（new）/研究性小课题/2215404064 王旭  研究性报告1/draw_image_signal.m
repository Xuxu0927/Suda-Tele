I = imread('����.jpg');
Ir = I(:,:,1);  % r g b  ���������У�����ѡr����

[H,W] = size(Ir); %ͼ��߶ȺͿ��

% start = 1;  
% ending = W;

start = 1;   % ���źŽϳ���Ҳ��ȡ����һ�λ�ͼ
ending = 213;

row  = 100; %ȡ��100��

f = Ir(row,start:ending);
x = start:ending;
figure(1), imshow(Ir)
hold on, plot(start:ending,row*ones(1,ending-start+1),'r');  %��ͼ�ϻ���һά�ź�����λ��
figure(2), plot(x,f)