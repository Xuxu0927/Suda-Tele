d=0:0.1:80;
fc1=2.4;
fc2=3.5;
fc3=5;

PL1=20*log(d)+46.4+20*log(fc1/5.0);
subplot(3,1,1);
plot(d,PL1);
title('�ز�Ƶ��Ϊ2.4GHzʱ��PL���ž���仯�Ķ�άͼ��');
xlabel('d/m');ylabel('�źŵ�·�����');

PL2=20*log(d)+46.4+20*log(fc2/5.0);
subplot(3,1,2);
plot(d,PL2);
title('�ز�Ƶ��Ϊ3.5GHzʱ��PL���ž���仯�Ķ�άͼ��');
xlabel('d/m');ylabel('�źŵ�·�����');

PL3=20*log(d)+46.4+20*log(fc3/5.0);
subplot(3,1,3);
plot(d,PL3);
title('�ز�Ƶ��Ϊ5GHzʱ��PL���ž���仯�Ķ�άͼ��');
xlabel('d/m');ylabel('�źŵ�·�����');
