v=10/3.6;t=0:0.001:120/(10/3.6);
fc1=2.4;fc2=3.5;fc3=5;
m=[[10 10];[30 40];[50 70];[80 60];[100 110]];

for i=1:length(m)
    n=m(i,:);
    d=sqrt((v*t-n(1)).^2+n(2)^2);
    PL1=20*log10(d)+46.4+20*log10(fc1/5.0);
    PL2=20*log10(d)+46.4+20*log10(fc2/5.0);
    PL3=20*log10(d)+46.4+20*log10(fc3/5.0);
    subplot(2,3,i);
    plot(t,PL1,'r',t,PL2,'b',t,PL3,'g');
    xlabel('t/s');
    ylabel('PL');
end
legend('2.4GHz','3.5GHz','5.0GHz');