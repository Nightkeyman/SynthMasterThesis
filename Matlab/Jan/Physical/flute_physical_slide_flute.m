%https://courses.cs.washington.edu/courses/cse467/05wi/pdfs/lectures/15-waveguideInstruments.pdf
close all
%clear

f_sin = 440;
% UNCHANGABLE PARAMS
Fs = 44100;
f = 0:0.1:round(Fs/2);
dt = 1/Fs;
time = 1/f_sin;
wave_period = floor(Fs/f_sin);

% CHANGABLE PARAMS
T = 1;
att_time = 1/2;
amp_noise = 0.03; %0.035
emb_delay = floor(wave_period/6); % wave_period/2
bore_delay = floor(wave_period/3); % wave_period/1
fbk_scl1 = 0.2; %0.5
fbk_scl2 = 0.33; %0.55
filt_b = -0.1; %-0.3
filt_a = 0.7; %0.7

% AFLOW1 creation
kenv1 = zeros(length(0:dt:T-dt), 1);  % calosc zerowana
kenv1((att_time*length(0:dt:T-dt)/3):length(0:dt:T-dt), 1) = 1; % jedynka na ostatnie 1/3
for i = 1:(length(0:dt:T-dt)/6)
  kenv1(i, 1) = i/(length(0:dt:T-dt)/6);
end

aflow1 = kenv1.*randn(length(0:dt:T-dt), 1);
aflow1 = aflow1/max(aflow1);
aflow1 = aflow1/5;


% KVIBR creation
wave = zeros(length(0:dt:T-dt), 1);
for i = 1:length(0:dt:T-dt)
  wave(i) = sin(2*pi*i*f_sin/Fs);
end

kenvibr = zeros(length(0:dt:T-dt), 1);
kenvibr((2*length(0:dt:T-dt)/3):length(0:dt:T-dt), 1) = 1;
for i = 1:(length(0:dt:T-dt)/3)
  kenvibr(i+(length(0:dt:T-dt)/3), 1) = i/(length(0:dt:T-dt)/3);
end

kvibr = wave.*kenvibr;

% AFLOW2 & ASUM1
aflow2 = aflow1.*kvibr;
asum1 = amp_noise*aflow2 + kvibr;
figure(2)
plot(asum1)

% prepare signals for feedback loop
asum2 = zeros(length(0:dt:T-dt), 1);
ax = zeros(length(0:dt:T-dt), 1);
apoly = zeros(length(0:dt:T-dt), 1);
asum3 = zeros(length(0:dt:T-dt), 1);
avalue = zeros(length(0:dt:T-dt), 1);
aflute1 = zeros(length(0:dt:T-dt), 1);

% FEEDBACK LOOP
for i = (1+bore_delay):length(0:dt:T-dt)
  asum2(i+1) = asum1(i) + aflute1(i);
  ax(i+1) = asum2(i+1-emb_delay);
  apoly(i+1) = ax(i+1) - ax(i+1)^3;
  asum3(i+1) = aflute1(i) + apoly(i+1);
  %filter step
  %avalue(i+1) = filter(filt_b, filt_a, asum3(i+1));
  avalue(i+1) = filt_b*asum3(i+1) - filt_a*avalue(i);
  aflute1(i+1) = avalue(i-bore_delay);
end

% OUTPUT SIGNAL
%Y = asum1;
Y = avalue;
Y = Y/max(Y);
%sound(Y, Fs);

figure(3)
plot(Y)

% WYKRES OBU SYNTEZ
% Najpierw odpaliæ flute_AR_model, potem ten skrypt, tylko bez cleara --> 2 sekundy dzwieku w tym skrypcie musza byc
figure(4)
subplot(2,1,1)
plot(Y(64000:66000-1))
title("Dzwiek wygenerowany za pomoc¹ syntezy falowodowej")
subplot(2,1,2)
plot(X(64000:66000-1))
title("Dzwiek wygenerowany za pomoc¹ modelu ARMA")

