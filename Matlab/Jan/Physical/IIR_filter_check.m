close all

Fs = 44100;
N = 1024;
tt = floor(Fs/N);
T = 1;
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

%{
% DZIALA!!
x = rand(1, N) - 0.5;
for i = nh+2:N
  for j = 1:nh
    r1(i) = r1(i) + h2(j)*x(i-j-1) - h1(j+1)*r1(i-j);
  end
end

figure(1)
plot(x)

figure(2)
r1 = r1/max(r1);
plot(r1)
%}
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

%{
% PODEJSCIE z R1 i R2
for k = 0:L
  % za kazdym razem nowy szum
  x = rand(1, N) - 0.5;
  % zaczyna sie od jedynki bo bierzemy tez z poprzednich blokow ( tablica r2)
  for i = 1:N
    for j = 1:nh
      if(i <= nh)
        r1(i) = r1(i) + h2(j)*x2(nh-j+1) - h1(j+1)*r2(nh-j+1);
      else
        r1(i) = r1(i) + h2(j)*x(i-j-1) - h1(j+1)*r1(i-j);
      end
    end
    if(i >= N-nh)
      r2(i) = r1(i);
      x2(i) = x(i);
    end
    output(k*N + i) = r1(i);
  end
  r1(1:N) = 0;
end
%}

%{
Y = output/max(output);
Y = Y/max(Y);
sound(Y*0.7, Fs);
%}