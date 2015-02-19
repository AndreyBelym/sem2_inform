const alpabet=['a'..'z','A'..'Z'];
type filechar=file of char;
function Input(var f:filechar):boolean;
var fileName:string; error:integer; ch:char;
begin
    
    repeat
        WriteLn('Введите имя файла для анализа');
        Write('Файл:');ReadLn(fileName);
        Assign(f,fileName);
        {$I-}
            Reset(f);
        {$I+}
        error:=ioresult;
        if error<>0 then begin
            WriteLn('Неправильное имя файла! Повторить ввод? <Y>/<N>');
            ReadLn(ch);
        end;
    until (UpCase(ch)='N') or (error=0);
    Input:=error=0;
end;
function GetCount(var f:filechar;var pCount:longint):boolean;
var i:longint;ch:char;
begin
    reset(f); i:=0;
    while not EOF(f) do begin
        read(f,ch);
        inc(i);
    end;
    pCount:=i;
    if pCount<>0 then
        GetCount:=true
    else 
        GetCount:=false;
end;
function GetArray(var f:filechar;var p:array of char;const pCount:longint):boolean;
var i:longint;ch:char;
begin
    reset(f); i:=0;
    while not EOF(f) and (i<=pCount-1) do begin
        read(f,ch);
        p[i]:=ch;
        inc(i);
    end;
    GetArray:=EOF(f);
end;
function GetLetter(const p:array of char;pCount:longint;var ch:char;var chQuant:longint):boolean;
var chars:array [char] of longint; sym:char;i:longint; have_letters:boolean; 
begin
    for sym:=#0 to #255 do
        chars[sym]:=0;
    chQuant:=0;ch:=#0;have_letters:=false;
    for i:=0 to pCount-1 do begin
        sym:=p[i];
        if sym in alpabet then begin
            have_letters:=true;
            inc(chars[sym]);
            if chars[sym]>chQuant then begin
                ch:=sym;
                chQuant:=chars[sym];
            end;
        end;
    end;
    GetLetter:=have_letters;            
end;   
type arr=array[1..2] of char;     
var log:boolean;ch:char; chQuant:LongInt;p:^arr;pCount:longint;f:filechar;
BEGIN
    
    log:=Input(f);
    if log then begin
        log:=GetCount(f,pCount);
        if log then begin
            {log:=memavail>=(pCount*sizeof(char));}
            if log then begin
                getmem(p,pCount*sizeof(char));
                log:=GetArray(f,p^,pCount);
            end;
            if log then begin
                
                log:=GetLetter(p^,pCount,ch,chQuant);
                freemem(p,pCount*sizeof(char));
                if log then
                    WriteLn('Наиболее часто всречается буква',#10#13,
                                ch,' в количестве ',chQuant,' шт.')
                else
                    WriteLn('В тексте нет букв.');
            end else
                WriteLn('Ошибка выделения памяти!')
         end else
            WriteLn('Файл пустой!');
    end else
        WriteLn('Программа завершена пользователем.');
    WriteLn('Нажмите <Enter>...');
    ReadLn;
END.
