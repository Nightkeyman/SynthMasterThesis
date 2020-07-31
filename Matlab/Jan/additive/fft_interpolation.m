% https://www2.ak.tu-berlin.de/~akgroup/ak_pub/abschlussarbeiten/2018/Wiemann_MasA.pdf --> strona 11

% https://ccrma.stanford.edu/~jos/sasp/Sinusoidal_Modeling_Sound.html

% https://dspguru.com/dsp/howtos/how-to-interpolate-fft-peak/ <-- rozne metody

% utworz tablice do fft 1024 przy probkowaniu 96000 --> jaka rozdzielczosc btw?
% chciej 440 Hz rowno --> utworzyc peak tam
close all
fs = 44100;
length = 1024;
f = 1:length;
peaks = zeros(1, length);
yi = zeros(1, length);
f2 = 1:10:length;

for k = 1:length
  for m = 1:length
    suma = suma + X
  endfor
  X(k) = suma;
endfor
