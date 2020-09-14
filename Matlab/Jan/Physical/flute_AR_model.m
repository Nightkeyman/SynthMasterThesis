close all
clear
Fs = 44100;
f = 1:2048;
fft_size = 2048;
y = audioread('Samples/flute_A_2.wav');

signal = y(1:fft_size, 1);
figure(5)
plot(signal)
title('Sygnal nagranego fletu')
xlabel('czas [s]')
ylabel('Amplituda')
hann_coef = hanning(fft_size);
signal = signal;%.*hann_coef;

spectrum = abs(fft(signal));

spect_dens = 20*log10(abs(spectrum));
figure(4);
f = ((f-1)/fft_size)*Fs;
plot(f,spect_dens);
grid on
axis([0 4000 -40 40])
title('Widmo czêstotliwoœciowe dŸwiêku fletu (A razkreœlne)');
xlabel("Czestotliwosc [Hz]")
ylabel("Amplituda [dB]")

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

f = 0:0.1:round(Fs/2);
T = 10;
s = [1 zeros(1,length(0:1/Fs:T-1/Fs))];
insig = randn(length(0:1/Fs:T-1/Fs), 1);
insig = ADSR(insig,1,1,2,2);
% insig = noise(length(0:1/Fs:T-1/Fs), 1, 'white');
note = 68
Resonances_freq_A = [440*1.059463^(note - 69) 440*1.059463^(note - 57) 440*1.059463^(note - 50) 440*1.059463^(note - 45) 440*1.059463^(note - 42) 440*1.059463^(note - 38)];
# Resonances_freq_A = [440 880 1312 1764 2194 2649 3513];
Resonances_mag_A = [33.6 30.58 18.289 22.35 4.53 0.67]*3;
Resonances_mag_A = 200.^(Resonances_mag_A/20);
Apoles = zeros(length(Resonances_freq_A)*2,1);
for i=1:2:length(Apoles)
    Apoles(i) = (1 - 0.05/Resonances_mag_A(fix((i+1)/2)))*exp(1i*Resonances_freq_A((i+1)/2)*2*pi/Fs);
    Apoles(i+1) = (1 - 0.05/Resonances_mag_A(fix((i+1)/2)))*exp(-1i*Resonances_freq_A((i+1)/2)*2*pi/Fs);
end
A = poly(Apoles);

Resonances_freq_B = [440*1.059463^(note - 62) 440*1.059463^(note - 53) 440*1.059463^(note - 48) 440*1.059463^(note - 43) 440*1.059463^(note - 40) 440*1.059463^(note - 36)];
# Resonances_freq_B = [660 1096 1538 1979 2421 3081];
Resonances_mag_B = [33.6 30.58 18.289 22.35 4.53 0.67];
Resonances_mag_B = 50.^(Resonances_mag_B/20);
Bzeros = zeros(length(Resonances_freq_B)*2,1);
for i=1:2:length(Bzeros)
    Bzeros(i) = (1 - 0.05/Resonances_mag_B(fix((i+1)/2)))*exp(1i*Resonances_freq_B((i+1)/2)*2*pi/Fs);
    Bzeros(i+1) = (1 - 0.05/Resonances_mag_B(fix((i+1)/2)))*exp(-1i*Resonances_freq_B((i+1)/2)*2*pi/Fs);
end

B = [poly(Bzeros)];
%B = [zeros(1, length(A)-1) 1];

figure(1);
zplane(B, A);
title('Zplane of flute model')

[H,F] = freqz(B,A,f,Fs);
figure(2)
plot(F,20*log10(abs(H)))
grid on
xlabel("Czestotliwosc [Hz]")
ylabel("Amplituda [dB]")
axis([0 5000 0 100]);

abs(Apoles);
atan(imag(Apoles)./real(Apoles))*Fs/(2*pi);
Y = filter(B, A, insig);

[numer, denom] = zp2tf(Bzeros, Apoles, 1)

figure(3)
y = impz(1, A);
t = 0:1/Fs:length(y)/Fs - 1/Fs;
plot(Y);
title('Sygnal utworzony przez pobudzony model')
xlabel('Czas [s]')
ylabel('Amplituda')
y = y/max(y);

Y = Y/max(Y);
insig = insig/max(insig);
sound(Y, Fs);