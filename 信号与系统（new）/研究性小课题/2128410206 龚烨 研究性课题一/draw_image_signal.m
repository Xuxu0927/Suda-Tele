I = imread('image.png');
Ir = I(:,:,1);  % r g b  ���������У�����ѡr����

[H,W] = size(Ir); %ͼ��߶ȺͿ��

% start = 1;  
% ending = W;

start = 200;   % ���źŽϳ���Ҳ��ȡ����һ�λ�ͼ
ending = 500;

row  = 500; %ȡ��500��

f = Ir(row,start:ending);
x = start:ending;
figure(1), imshow(Ir)
hold on, plot(start:ending,row*ones(1,ending-start+1),'r');  %��ͼ�ϻ���һά�ź�����λ��
figure(2), plot(x,f)