v=10/3.6;x0=0;y0=0;%统一单位
t=0:0.001:120/(10/3.6);
x=x0+v*t;
y=y0+0*t;
plot(x,y,'r','linewidth',4);%画节点的移动路径
xlabel('x/m');
ylabel('y/m');
xlim([0 120]);
ylim([0 120]);
hold on;
plot(10,10,'o',30,40,'o',50,70,'o',80,60,'o',100,110,'o');%画五个定位设备
box off