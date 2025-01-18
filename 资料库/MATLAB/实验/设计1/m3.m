d=0:0.1:80;
fc1=2.4;
fc2=3.5;
fc3=5;

PL1=20*log(d)+46.4+20*log(fc1/5.0);
subplot(3,1,1);
plot(d,PL1);
title('载波频率为2.4GHz时，PL随着距离变化的二维图形');
xlabel('d/m');ylabel('信号的路径损耗');

PL2=20*log(d)+46.4+20*log(fc2/5.0);
subplot(3,1,2);
plot(d,PL2);
title('载波频率为3.5GHz时，PL随着距离变化的二维图形');
xlabel('d/m');ylabel('信号的路径损耗');

PL3=20*log(d)+46.4+20*log(fc3/5.0);
subplot(3,1,3);
plot(d,PL3);
title('载波频率为5GHz时，PL随着距离变化的二维图形');
xlabel('d/m');ylabel('信号的路径损耗');
