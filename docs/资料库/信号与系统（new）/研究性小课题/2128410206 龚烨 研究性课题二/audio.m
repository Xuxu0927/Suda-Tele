A = audioread('audio.wav');
A = A(:,1);
subplot(3,1,1);
plot(A);
[D, Fs] = audioread('dirac.wav');
D = D(:,1);
subplot(3,1,2);
plot(D);
C = conv(A,D);
C = C * 0.01;
audiowrite("out.wav", C, Fs);
subplot(3,1,3);
plot(C);

