% https://blogs.mathworks.com/steve/2014/09/23/sinusoids-and-fft-frequency-bins/
% to remember: main lobe and side lobes

% literatura do additive: https://www.dsprelated.com/freebooks/sasp/Additive_Synthesis.html
% https://www.researchgate.net/publication/2698835_Overlap-Add_Synthesis_Of_Nonstationary_Sinusoids

x = 0:0.1:10;
y = gaussmf(x, [2 5]);
Fs = 96000;
fft_length = 4096;
fft_res = Fs/fft_length;
sigma = fft_res; %variance
freq = fft_res*20 + fft_res/4;
%freq = 2500;

x = 0:(Fs/fft_length):Fs - (Fs/fft_length);
%y = gaussmf(x, [sigma freq]);
y = -exp(-2*pi*(freq/fft_res/2)*1i)*gaussmf(x, [sigma freq]) - exp(2*pi*(freq/fft_res/2)*1i)*gaussmf(x, [sigma Fs-freq]);
y = y + exp(-2*pi*(freq/fft_res/2)*1i)*gaussmf(x, [sigma freq+fft_res]) + exp(2*pi*(freq/fft_res/2)*1i)*gaussmf(x, [sigma Fs-freq+fft_res]);
%sztuczne odwrocenie real i imag zeby sie zgadzalo
y = real(y)*1i + imag(y);

figure(1)
subplot(2,1,1)
plot(real(y))
title('REAL')
subplot(2,1,2)
plot(imag(y))
title('IMAG')

sig = real(ifft(y));
% wypelnic tablice do odtworzenia
seconds = 1;
sig_out = zeros(1, (Fs/fft_length)*seconds*fft_length);
for i = 1:(Fs/fft_length)*seconds
    for j = 1:fft_length
        sig_out(j + i*fft_length) = sig(j);
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

x_fft = fft(x(1:fft_length));
figure(4)
subplot(2,1,1);
plot(real(x_fft)/fft_length)
title('REAL')
subplot(2,1,2);
plot(imag(x_fft)/fft_length)
title('IMAG')

x_time = real(ifft(x_fft));
%figure(5)
%plot(x_time)
% Tu opisano o FFT resolution: https://www.bitweenie.com/listings/fft-zero-padding/
% Opisac w pracy !!!! ze chcielismy 2048 ale procesor sie zacinal wiec trzeba zostac przy 1024 czyli rozdzielczosc jest 93.75Hz

% wypelnic tablice do odtworzenia
seconds = 1;
sig_out = zeros(1, (Fs/fft_length)*seconds*fft_length);
for i = 1:(Fs/fft_length)*seconds
    for j = 1:fft_length
        sig_out(j + i*fft_length) = x_time(j);
    end
end

sig_out = sig_out/max(sig_out);
sound(sig_out*0.8, Fs)

% Porownanie w czasie
figure(3)
subplot(3,1,1)
plot(sig)
subplot(3,1,2)
plot(x(1:fft_length))
subplot(3,1,3)
plot(x_time(1:fft_length))