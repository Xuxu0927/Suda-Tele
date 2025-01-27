[IR, Fs] = audioread('15083.wav');
IR1 = IR(:,1);
subplot(3,1,1);
plot(IR1);
[talk, Fs] = audioread('45wmv-w9f0v.wav');
subplot(3,1,2);
plot(talk);
mix = conv(talk,IR1);
audiowrite("1.wav", mix, Fs);
subplot(3,1,3);
plot(mix);

