close all
clear
Fs = 44100;
f = 1:2048;
fft_size = 2048;
y = audioread('Samples/flute_A_2.wav');

signal = y(1:fft_size, 1);
hann_coef = hanning(fft_size);
signal = signal;%.*hann_coef;

spectrum = abs(fft(signal));

spect_dens = 20*log10(abs(spectrum));
figure(4);
f = ((f-1)/fft_size)*Fs;
plot(f,spect_dens);

axis([0 10000 -40 40])
title('Flute sound spectral density');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

f = 0:0.1:round(Fs/2);
T = 3;
s = [1 zeros(1,length(0:1/Fs:T-1/Fs))];
insig = randn(length(0:1/Fs:T-1/Fs), 1);
insig = ADSR(insig,3,2,2,2);
% insig = noise(length(0:1/Fs:T-1/Fs), 1, 'white');
Resonances_freq_A = [440 880 1312 1764 2194 2649 3513];
Resonances_mag_A = [33.6 30.58 18.289 22.35 4.53 0.67 -4.06];
Resonances_mag_A = 100.^(Resonances_mag_A/20);
Apoles = zeros(length(Resonances_freq_A)*2,1);
for i=1:2:length(Apoles)
    Apoles(i) = (1 - 0.05/Resonances_mag_A(fix((i+1)/2)))*exp(1i*Resonances_freq_A((i+1)/2)*2*pi/Fs);
    Apoles(i+1) = (1 - 0.05/Resonances_mag_A(fix((i+1)/2)))*exp(-1i*Resonances_freq_A((i+1)/2)*2*pi/Fs);
end
A = poly(Apoles);

Resonances_freq_B = [660 1096 1538 1979 2421 3081];
Resonances_mag_B = [33.6 30.58 18.289 22.35 4.53 0.67];
Resonances_mag_B = 10.^(Resonances_mag_B/20);
Bzeros = zeros(length(Resonances_freq_B)*2,1);
for i=1:2:length(Bzeros)
    Bzeros(i) = (1 - 0.05/Resonances_mag_B(fix((i+1)/2)))*exp(1i*Resonances_freq_B((i+1)/2)*2*pi/Fs);
    Bzeros(i+1) = (1 - 0.05/Resonances_mag_B(fix((i+1)/2)))*exp(-1i*Resonances_freq_B((i+1)/2)*2*pi/Fs);
end

B = [0 0 poly(Bzeros)];
%B = [zeros(1, length(A)-1) 1];

figure(1);
zplane(B, A);

[H,F] = freqz(B,A,f,Fs);
figure(2)
plot(F,20*log10(abs(H)))
grid on
xlabel('Frequency (Hz)')
ylabel('PSD (dB/Hz)')
axis([0 5000 0 100]);

abs(Apoles);
atan(imag(Apoles)./real(Apoles))*Fs/(2*pi);
Y = filter(B, A, insig);

figure(3)
y = impz(1, A);
t = 0:1/Fs:length(y)/Fs - 1/Fs;
plot(Y);
y = y/max(y);
Y = Y/max(Y);
insig = insig/max(insig);
sound(Y, Fs);