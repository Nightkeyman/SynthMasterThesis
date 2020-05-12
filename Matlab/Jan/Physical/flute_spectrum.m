close all
fs = 44100;
f = 1:2048;
length = 2048;
y = audioread("Samples/flute_A_2.wav");

signal = y(1:length, 1);
hann_coef = hanning(length);
signal = signal;%.*hann_coef;

spectrum = abs(fft(signal));

spect_dens = 20*log10(abs(spectrum));
figure(2);
f = ((f-1)/length)*fs;
plot(f,spect_dens);
axis([0 2000 -40 40])
title("Flute sound spectral density");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

y2 = audioread("Samples/flute_H_2.wav");

signal2 = y2(1:length, 1);
hann_coef = hanning(length);
signal2 = signal2.*hann_coef;

spectrum2 = fft(signal2);
spect_dens2 = 20*log10(abs(spectrum2));
figure(4);
plot(f,spect_dens2);
axis([0 500 0 40])
title("Signal 1");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

y3 = audioread("Samples/flute_C_2.wav");

signal3 = y3(1:length, 1);
hann_coef = hanning(length);
signal3 = signal3.*hann_coef;
%figure(5);
%plot(signal);

spectrum3 = fft(signal3);
spect_dens3 = 20*log10(abs(spectrum3));
figure(6);
plot(f,spect_dens3);
axis([0 500 0 40])
title("Signal 1");