close all;
clear all;

N = 1024;
Fs = 48000/4;
fft_res = Fs/N;
freq = fft_res*40 + fft_res;
dt = 1/Fs;
StopTime = 1;
t = (0:dt:StopTime-dt);

w = blackman(N);
W = abs(fft(w'.*sin(2*pi*freq*t(1:N))));
figure(1)
subplot(2,1,1)
plot(real(W));

grid on
subplot(2,1,2)
plot(imag(W));
grid on