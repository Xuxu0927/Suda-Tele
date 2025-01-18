% ��ȡͼ��
image = imread('image.jpg'); 
if size(image, 3) == 3
    image = rgb2gray(image); % ת��Ϊ�Ҷ�ͼ��
end

% 1. ��˹�˲���
sigma = 1; % ���ñ�׼��
hsize = 5; % �����˲�����С
gaussianFilter = fspecial('gaussian', hsize, sigma);
gaussianFiltered = imfilter(double(image), gaussianFilter, 'replicate');

% 2. ��ֵ�˲���
medianFiltered = medfilt2(image, [5 5]); % 5x5������

% ���չʾ
figure;
subplot(1, 3, 1);
imshow(image);
title('Original Image');

subplot(1, 3, 2);
imshow(gaussianFiltered, []);
title('Gaussian Filtered Image');

subplot(1, 3, 3);
imshow(medianFiltered);
title('Median Filtered Image');
