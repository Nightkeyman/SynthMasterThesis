function [ y ] = ADSR(sig, att, dec, sus, rel)
  % att - time (0 - 10)
  % start amplitude is sus*1.5 or smth like that
  max_att_time = length(sig)/5;
  att_time = max_att_time*(att/10);
  att_amp = sus*2;
  
  % dec - time (0 - 10)
  max_dec_time = length(sig)/5;
  dec_time = max_dec_time*(dec/10);
  
  % sus - amplitude (0 - 10)
  sus_amp = sus*mean(abs(sig));
  
  % rel - time (0 - 10)
  max_rel_time = length(sig)/5;
  rel_time = max_rel_time*(rel/10);
  
  % Attack - narastanie od 0 do att_amp
  for i = 1:att_time
    dx = (i/att_time)*att_amp;
    sig(i) = sig(i)*dx;
  end
  
  % Decay - opadanie od att_amp do sus_amp
  for i = (att_time + 1):(att_time + dec_time)
    dx = ((i - att_time + 1)/(dec_time))*sus_amp;
    sig(i) = sig(i)*dx;
  end

  % Sus - przemnozenie sygnalu przez sus_amp
  
  % Rel - opadanie od sus_amp do 0 w czasie rel_time
  for i = (length(sig) - rel_time):length(sig)
    dx = (i - (length(sig) - rel_time))/(rel_time);
    sig(i) = sig(i)*dx;
  end
  %}
  y = sig;
end