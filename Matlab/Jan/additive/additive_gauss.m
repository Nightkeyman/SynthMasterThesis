% https://blogs.mathworks.com/steve/2014/09/23/sinusoids-and-fft-frequency-bins/
% to remember: main lobe and side lobes

% literatura do additive: https://www.dsprelated.com/freebooks/sasp/Additive_Synthesis.html
% https://www.researchgate.net/publication/2698835_Overlap-Add_Synthesis_Of_Nonstationary_Sinusoids

x = 0:0.1:10;
y = gaussmf(x, [2 5]);
Fs = 96000;
fft_length = 2048;
sigma = 50; %variance
freq = 440;

x = 0:(Fs/fft_length):Fs - (Fs/fft_length);
y = exp(freq/Fs)*gaussmf(x, [sigma freq]) + exp(freq*2/Fs)*gaussmf(x, [sigma freq*2]) + exp(freq*3/Fs)*gaussmf(x, [sigma freq*3]) + exp(freq*4/Fs)*gaussmf(x, [sigma freq*4]);
y = y + (gaussmf(x, [sigma Fs-freq]) + gaussmf(x, [sigma Fs-freq*2]) + gaussmf(x, [sigma Fs-freq*3]) + gaussmf(x, [sigma Fs-freq*4]) + gaussmf(x, [sigma Fs-freq*6]));
figure(1)
plot(x,y)

sig = real(ifft(y)) + imag(ifft(y));
sig = sig/max(sig);
figure(2)
plot(sig)

% wypelnic tablice do odtworzenia
seconds = 1;
sig_out = zeros(1, (Fs/fft_length)*seconds*fft_length);
for i = 1:(Fs/fft_length)*seconds
    for j = 1:fft_length
        sig_out(j + i*fft_length) = sig(j);
    end
end

sound(sig_out, Fs)

% Porownanie z sinusem ifft i w czasie
dt = 1/Fs;
StopTime = 1;
t = (0:dt:StopTime-dt);
%%Sine wave:
freq = 93.75*2 + 93.75/4;
x = sin(2*pi*freq*t);

figure(3)
plot(t(1:1024), x(1:1024))

sig_sin = fft(x(1:1024));
figure(4)
subplot(2,1,1);
plot(real(sig_sin))
subplot(2,1,2);
plot(imag(sig_sin))

% Tu opisano o FFT resolution: https://www.bitweenie.com/listings/fft-zero-padding/
% Opisac w pracy !!!! ze chcielismy 2048 ale procesor sie zacinal wiec trzeba zostac przy 1024 czyli rozdzielczosc jest 93Hz