Fs = 44100;
t = 0:(1/Fs):1 - 1/Fs;
sinn = sin(2*pi*440*t);
sinn = sinn(1:2048);

sin_fft = abs(fft(sinn));
plot(sin_fft);
axis[0 100