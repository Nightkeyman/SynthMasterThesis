% https://www2.ak.tu-berlin.de/~akgroup/ak_pub/abschlussarbeiten/2018/Wiemann_MasA.pdf --> strona 11

% utworz tablice do fft 1024 przy probkowaniu 96000 --> jaka rozdzielczosc btw?
% chciej 440 Hz rowno --> utworzyc peak tam
close all
fs = 44100;
length = 1024;
f = 1:length;
peaks = zeros(1, length);
yi = zeros(1, length);
f2 = 1:10:length;

peaks(10) = 1;
signal = real(ifft(peaks));
peaks(10) = 1/2;
peaks(9) = 1/3;
peaks(11) = 1;
peaks(12) = 1/3;
signal2 = real(ifft(peaks));

%{
subplot(2,1,1);
plot(signal)
subplot(2,1,2);
plot(signal2)
%}

yi = interp1(1:length, peaks, f2, 'linear')