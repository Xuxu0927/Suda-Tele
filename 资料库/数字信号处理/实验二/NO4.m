% 读取图像
image = imread('image.jpg'); 
if size(image, 3) == 3
    image = rgb2gray(image); % 转换为灰度图像
end

% 1. 高斯滤波器
sigma = 1; % 设置标准差
hsize = 5; % 设置滤波器大小
gaussianFilter = fspecial('gaussian', hsize, sigma);
gaussianFiltered = imfilter(double(image), gaussianFilter, 'replicate');

% 2. 中值滤波器
medianFiltered = medfilt2(image, [5 5]); % 5x5的邻域

% 结果展示
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
