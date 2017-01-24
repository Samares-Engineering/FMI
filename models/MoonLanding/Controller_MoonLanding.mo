model Controller_MoonLanding
  output Real thrust;
algorithm
  if(time >= 0 and time < 81) then 
    thrust := 1440000;
  elseif(time>=81 and time < 100) then
    thrust := 116000;
  else
    thrust := 0;
  end if;
end Controller_MoonLanding;