begin
    readln(stud_count);
    for i:=1 to stud_count do begin
        with stud[i] do
        Read(lastname,groupnum,tests_passed);
    end;
    loosers_cnt:=0;
    repeat
        founded:=false;
        for i:=1 to stud_count do begin
        with stud[i] do begin
            if not checked[i] and (min_passed>tests_passed) then
                founded:=true;
                looser_num:=i;
                min_passed:=tests_passed;
        end;
        if founded and (10-min_pass>5) then
            checked[i]:=true;
            inc(loosers_cnt);
            loosers[i]:=stud[i];
    until (10-min_pass<5) and not founded;
    for i:=1 to loosers_cnt do begin
        with loosers[i] do
        Write(lastname,groupnum,tests_passed);
end.