close all

Fs = 48000;
N = 1024;
tt = floor(Fs/N);
T = 3;
L = tt*T;
output = zeros(1, L);

nh = 13;
r1 = zeros(1, N);
r2 = zeros(1, nh);
x2 = zeros(1, nh);
%numer
h2 = [1	-11.43375376752887	60.31833674426191	-194.1394812807309	424.5937877928701	-664.769900430088	764.0300762539232	-649.5156931345342	405.3715864508815	-181.1511334347017	55.02415296193268	-10.20098698106399	0.8730088389019536];
%denom
h1 = [1	-11.59763215270097	61.97101071357208	-201.7393812534704	445.6198758436103	-703.6355440065329	814.3969626483859	-696.1747269288569	436.2403933464246	-195.4265157932021	59.4119294426669	-11.00594700485998	0.9395751465939362 0];

x(1:N) = rand(1, N) - 0.5;
% PODEJSCIE z jedna tablica R1
for k = 0:L
  % tworzymy pierwsze pol szumu i czyscimy pierwsze pol r1
  x(1:N/2) = rand(1, N/2) - 0.5;
  r1(1:N/2) = 0;
  % Tworzenie jednego bloku r1
  for i = 1:N
    if(i == N/4)
      x((N/2 + 1):N) = rand(1, N/2) - 0.5;
      r1((N/2 + 1):N) = 0;
    end
    for j = 1:nh
      if((i <= nh) && (i-j+N <= N))
        r1(i) = r1(i) + h2(j)*x(i-j-1+N) - h1(j+1)*r1(i-j+N);
      elseif(i-j-1 <= 0)
        r1(i) = r1(i) + h2(j)*x(i-j-1+N) - h1(j+1)*r1(i-j);
      else
        r1(i) = r1(i) + h2(j)*x(i-j-1) - h1(j+1)*r1(i-j);
      end
    end
    %przypisanie probek r1 do wyjscia output
    output(k*N + i) = r1(i);
  end
end

subplot(2,1,1)
plot(output(1:N))
subplot(2,1,2)
plot(output(N+1:2*N))

Y = output;
Y = Y/max(Y);
sound(Y*0.7, Fs);