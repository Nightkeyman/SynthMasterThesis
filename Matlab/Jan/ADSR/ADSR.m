function [ y ] = ADSR(sig, att, dec, sus, rel)
  % att - time (0 - 10)
  max_att_time = length(sig)/10;
  att_time = max_att_time*(att/10);
  
  % dec - time (0 - 10)
  max_dec_time = length(sig)/10;
  dec_time = max_dec_time*(dec/10);
  
  % sus - amplitude (0 - 10)
  % rel - time (0 - 10)
  % start amplitude is sus*1.3 or smth like that
  
  % Attack
  %for i = 1:
    
  %end
  
  
  
endfunction