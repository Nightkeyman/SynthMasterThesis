close all
clear

Fs = 44100;
f = 0:0.1:round(Fs/2);
f_sin = 440;
T = 3;
aflow1 = randn(length(0:1/Fs:T-1/Fs), 1);
aflow1 = aflow1/max(aflow1);
aflow1 = aflow1/5;

wave = zeros(length(0:1/Fs:T-1/Fs), 1);
for i = 1:length(0:1/Fs:T-1/Fs)
  wave(i) = sin(2*pi*i*f_sin/Fs);
end

kenvibr = zeros(length(0:1/Fs:T-1/Fs), 1);
kenvibr((2*length(0:1/Fs:T-1/Fs)/3):length(0:1/Fs:T-1/Fs), 1) = 1;
for i = 1:(length(0:1/Fs:T-1/Fs)/3)
  kenvibr(i+(length(0:1/Fs:T-1/Fs)/3), 1) = i/(length(0:1/Fs:T-1/Fs)/3);
end

kvibr = wave.*kenvibr;

aflow2 = aflow1.*kvibr;
plot(aflow2)
asum1 = aflow2 + kvibr;



Y = asum1;
Y = Y/max(Y);
sound(Y, Fs);
plot(Y)