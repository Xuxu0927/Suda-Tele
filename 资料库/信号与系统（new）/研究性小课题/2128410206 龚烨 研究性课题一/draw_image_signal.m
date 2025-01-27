I = imread('image.png');
Ir = I(:,:,1);  % r g b  三个分量中，这里选r分量

[H,W] = size(Ir); %图像高度和宽度

% start = 1;  
% ending = W;

start = 200;   % 因信号较长，也可取其中一段画图
ending = 500;

row  = 500; %取第500行

f = Ir(row,start:ending);
x = start:ending;
figure(1), imshow(Ir)
hold on, plot(start:ending,row*ones(1,ending-start+1),'r');  %在图上画出一维信号所在位置
figure(2), plot(x,f)