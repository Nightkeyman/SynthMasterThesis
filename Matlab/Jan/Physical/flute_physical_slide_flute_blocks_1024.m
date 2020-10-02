%https://courses.cs.washington.edu/courses/cse467/05wi/pdfs/lectures/15-waveguideInstruments.pdf
close all
clear

f_sin = 880;
% UNCHANGABLE PARAMS
Fs = 44100;
f = 0:0.1:round(Fs/2);
dt = 1/Fs;
time = 1/f_sin;
wave_period = floor(Fs/f_sin);
N = 1024;

% CHANGABLE PARAMS
att_time = 1/2;
amp_noise = 0.035; %0.035
emb_delay = floor(wave_period/6); % wave_period/2
bore_delay = floor(wave_period/3); % wave_period/1
fbk_scl1 = 0.2; %0.5
fbk_scl2 = 0.33; %0.55
filt_b = -0.1; %-0.3
filt_a = 0.7; %0.7
T = 3;
L = wave_period*T;
output = zeros(1, L);
env_del = 50000; % staly delay dla poczatkowych envelopów
kenvibr_del = 12*N;
kenv1_del = 24;

% TABLES
kenv1 = zeros(1, N);
wave = zeros(N, 1);
wave = zeros(N, 1);
kenvibr = zeros(N, 1);
% prepare signals for feedback loop
asum2 = zeros(N, 1);
asum2_del = zeros(emb_delay, 1);
ax = zeros(N, 1);
apoly = 0;
asum3 = 0;
avalue = zeros(N+1, 1);
avalue_del = zeros(bore_delay, 1);
aflute1 = zeros(N, 1);

% MAIN LOOP - k blocks
for k = 0:L
  % kenv1 creation
  for i = 1:N
    if(env_del > (i + k*N))
      kenv1(i) = (i + k*N)/(env_del);
    else
      kenv1(i) = 1;
    end
    output(k*N + i) = kenv1(i);
  end
  
  % AFLOW1 creation
  aflow1 = kenv1.*randn(N, 1);
  aflow1 = aflow1/10;
  
  % KVIBR creation
  for i = 1:N
    wave(i) = sin(2*pi*(i+k*N)*f_sin/Fs);
  end
  
  % KENVIBR creation
  for i = 1:N
    if(kenvibr_del > (i + k*N))
      kenvibr(i) = (i + k*N)/(kenvibr_del);
    else
      kenvibr(i) = 1;
    end
  end
  kvibr = wave.*kenvibr;
  aflow2 = aflow1.*kvibr;
  % ASUM1 creation
  asum1 = amp_noise*aflow2 + kvibr;
  avalue(1) = avalue(1025);
  
  % FEEDBACK LOOP
  for i = 1:N
    asum2(i+1) = asum1(i) + aflute1(i);
    asum2_del(emb_delay) = asum2(i+1);
    ax(i+1) = asum2_del(1);
    apoly = ax(i+1) - ax(i+1)^3;
    asum3 = aflute1(i) + apoly;
    avalue(i+1) = filt_b*asum3 - filt_a*avalue(i);
    avalue_del(bore_delay) = avalue(i+1);
    aflute1(i+1) = avalue_del(1);
    % REWRITE TO DELAYED TABLES
    for j = 1:emb_delay-1
      asum2_del(j) = asum2_del(j+1);
    end
    
    for j = 1:bore_delay-1
      avalue_del(j) = avalue_del(j+1);
    end
  end
  
  % CHECK
  for i = 1:N
    output(k*N + i) = avalue(i);
  end
end


% OUTPUT SIGNAL
%Y = asum1;
Y = output;
Y = Y/max(Y);
%sound(Y, Fs);

figure(3)
plot(Y)