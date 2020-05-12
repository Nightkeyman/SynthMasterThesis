clear
Fs = 22.05e3;
T = 1.5;
% s = mysawtooth(150, Fs, T, 0.11, 90, 0.06)*12 - 6;
s = [1 zeros(1,length(0:1/Fs:T-1/Fs))];
% Apoles = [
%     0.97*exp(pi*0.1i);
%     0.97*exp(-pi*0.1i);
%     0.97*exp(pi*0.2i);
%     0.97*exp(-pi*0.2i);
% ]';
f = 0:0.1:round(Fs/2);
Resonances_freq = [265 395 430 550 665];
Resonances_mag = [33 26 29 34 37];
Resonances_mag = 10.^(Resonances_mag/20);
Resonances_band = [15 25 20 30 30];
Apoles = zeros(length(Resonances_freq)*2,1);
for i=1:2:length(Apoles)
    Apoles(i) = (1 - 0.05/Resonances_mag(fix((i+1)/2)))*exp(1i*Resonances_freq((i+1)/2)*2*pi/Fs);
    Apoles(i+1) = (1 - 0.05/Resonances_mag(fix((i+1)/2)))*exp(-1i*Resonances_freq((i+1)/2)*2*pi/Fs);
end
A = poly(Apoles);
B = [zeros(1, length(A)-1) 1];
figure(1);
zplane(B, A);
% A = [1 -2.7607 3.8106 -2.6535 0.9238];
[H,F] = freqz(1,A,f,Fs);
figure(2)
plot(F,20*log10(abs(H)))
grid on
xlabel('Frequency (Hz)')
ylabel('PSD (dB/Hz)')
axis([0 800 170 300]);
abs(Apoles)
atan(imag(Apoles)./real(Apoles))*Fs/(2*pi)
Y = filter(B,A, s);
figure(3)
y = impz(1, A);
t = 0:1/Fs:length(y)/Fs - 1/Fs;
plot(Y);
y = y/max(y);
Y = Y/max(Y);

sound(Y*0.05, Fs);