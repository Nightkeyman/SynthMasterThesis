% https://blogs.mathworks.com/steve/2014/09/23/sinusoids-and-fft-frequency-bins/
% to remember: main lobe and side lobes

% literatura do additive: https://www.dsprelated.com/freebooks/sasp/Additive_Synthesis.html
% https://www.researchgate.net/publication/2698835_Overlap-Add_Synthesis_Of_Nonstationary_Sinusoids
clear all;

Fs = 48000;
N = 1024;
fft_res = Fs/N;
freq = fft_res*20 + fft_res/4;
x = 0:(Fs/N):Fs - (Fs/N);
y = zeros(1, N);
t = 1:1024;
freq = 10000;
dt = 1/Fs;
StopTime = 1;
t = (0:dt:StopTime-dt);

% Utworzenie fragmentu FFT ktory bedzie powielany
w = sin(2*pi*freq*t);
W = fft(w(1:1024));
W = W((214-20):(214+20)); % 214 is the highest peak for freq = 10000

% Utworzenie pe³nego WIDMA
freq = 880; %docelowo tablica
Y = zeros(1, N);


for i = 1:length(W)
  if (i + round(freq*N/Fs) - 20) > 0
    Y(i + round(freq*N/Fs) - 20) = W(i)*exp(2*pi*(freq*N/Fs)*1i);
  endif
  if ((i + round(N - freq*N/Fs) - 21) > 0 && (i + round(N - freq*N/Fs) - 20) < 1026)
    Y(i + round(N - freq*N/Fs) - 21) = W(42 - i)*exp(2*pi*(freq*N/Fs)*1i);
  endif
endfor

figure(1)
subplot(2,1,1)
plot(real(Y))
subplot(2,1,2)
plot(imag(Y))


%y = -exp(-2*pi*(freq/fft_res/2)*1i)*gaussmf(x, [sigma freq]) - exp(2*pi*(freq/fft_res/2)*1i)*gaussmf(x, [sigma Fs-freq]);
y = real(ifft(Y));% + imag(ifft(Y));
figure(2)
plot(y)

%{
figure(1)
subplot(2,1,1)
plot(real(y))
title('REAL')
subplot(2,1,2)
plot(imag(y))
title('IMAG')
%}
sig = y;
% wypelnic tablice do odtworzenia
seconds = 1;
sig_out = zeros(1, (Fs/N)*seconds*N);
for i = 1:(Fs/N)*seconds
    for j = 1:N
        sig_out(j + i*N) = sig(j);
    end
end
sig_out = sig_out/max(sig_out);
sound(sig_out*0.8, Fs)

% Porownanie z sinusem ifft i w czasie
dt = 1/Fs;
StopTime = 1;
t = (0:dt:StopTime-dt);
%%Sine wave:
%freq = 93.75; %93.75
x = sin(2*pi*freq*t);

x_fft = fft(x(1:N));
figure(4)
subplot(2,1,1);
plot(real(x_fft)/N)
title('REAL')
subplot(2,1,2);
plot(imag(x_fft)/N)
title('IMAG')

x_time = real(ifft(x_fft));
%figure(5)
%plot(x_time)
% Tu opisano o FFT resolution: https://www.bitweenie.com/listings/fft-zero-padding/
% Opisac w pracy !!!! ze chcielismy 2048 ale procesor sie zacinal wiec trzeba zostac przy 1024 czyli rozdzielczosc jest 93.75Hz

% wypelnic tablice do odtworzenia
seconds = 1;
sig_out = zeros(1, (Fs/N)*seconds*N);
for i = 1:(Fs/N)*seconds
    for j = 1:N
        sig_out(j + i*N) = x_time(j);
    end
end
sig_out = sig_out/max(sig_out);
sound(sig_out*0.8, Fs)

% Porownanie w czasie
figure(3)
subplot(3,1,1)
plot(sig)
subplot(3,1,2)
plot(x(1:N))
subplot(3,1,3)
plot(x_time(1:N))
%}