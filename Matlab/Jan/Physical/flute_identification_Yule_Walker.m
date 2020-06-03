clear
clc
close all
L = 2048;
y = audioread('Samples/flute_A_2.wav');

y = y(1:L, 1);

T = L;
N = 20;
r = zeros(1, T);
for thet = -T/2:T/2-1
    for t = 1:T
        if (t - thet > 0) && (t - thet < T)
            r(thet + T/2 + 1) = y(t)*y(t - thet) + r(thet + T/2 + 1);
        end
    end
    r(thet + T/2 + 1) = r(thet + T/2 + 1)/T;
end

% wypelnienie macierzy korelacji
% r(T+1) to tak naprawde r(0) bo ujemne sa ponizej r(T+1)
R_mat = zeros(N, N);
for i = 1:N
    R_mat(i, 1:N) = r(1, (T/2+i):-1:(T/2-N+i+1));
end
a_coef = linsolve(R_mat, r((T/2+2):(T/2+N+1))');

% Obliczenie wariancji szumu
noise_var = 0;
for i = 1:N
    noise_var = a_coef(i)*r(T/2-i+1) + noise_var;
end
noise_var = r(T/2+1) - noise_var;

% Utworzenie sygnalu y_est z wyestymowanym szumem
y_est = [zeros(1, N+1) zeros(1, L)];
v = sqrt(noise_var)*randn(1, length(y_est));
for i=N+1:L+N+1
  suma = 0;
  for k = 1:N
    suma = suma + a_coef(k)*y_est(i-k);
  end
  y_est(i) = v(i) - suma;
end
y_est = y_est(6:end);

T2 = T/2;
omega = 0:pi/T2:pi-pi/T2; % wektor zawierajacy pulsacje, dla ktorych obliczone zostanie widmo gestosci mocy
S = zeros(size(omega));
for j=1:length(omega)
  suma = 0;
  for k = 1:N
    suma = suma + a_coef(k)*exp(-1i*omega(j)*k);
  end
  S(j) = noise_var / (abs (1 - suma));
end
figure(3)
hold on;
plot(10*log10(S/max(S)))