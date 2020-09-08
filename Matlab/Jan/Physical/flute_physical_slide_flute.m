%https://courses.cs.washington.edu/courses/cse467/05wi/pdfs/lectures/15-waveguideInstruments.pdf
close all
clear

Fs = 44100;
f = 0:0.1:round(Fs/2);
f_sin = 440;
T = 3;

% Parameters (changable)
att_time = 1/2;
amp_noise = 0.05;

% AFLOW1 creation
kenv1 = zeros(length(0:1/Fs:T-1/Fs), 1);
kenv1((att_time*length(0:1/Fs:T-1/Fs)/3):length(0:1/Fs:T-1/Fs), 1) = 1;
for i = 1:(length(0:1/Fs:T-1/Fs)/6)
  kenv1(i, 1) = i/(length(0:1/Fs:T-1/Fs)/6);
end
plot(kenv1)

aflow1 = kenv1.*randn(length(0:1/Fs:T-1/Fs), 1);
aflow1 = aflow1/max(aflow1);
aflow1 = aflow1/5;


% KVIBR creation
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
%aflow2 = conv(aflow1, kvibr);
plot(aflow2)
asum1 = amp_noise*aflow2 + kvibr;

Y = asum1;
Y = Y/max(Y);
sound(Y, Fs);
plot(Y)
