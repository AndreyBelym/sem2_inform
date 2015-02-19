const alpabet=['a'..'z','A'..'Z','А'..'Я','а'..'п','р'..'ё'];
type charfile=file of char;
function Input(var f:charfile):boolean;
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
function GetLetter(var f:charfile;var ch:char;var chQuant:longint):boolean;
var chars:array [char] of longint; i:char; have_letters:boolean; 
begin
    for i:=#0 to #255 do
        chars[i]:=0;
    chQuant:=0;ch:=#0;have_letters:=false;
    while not EOF(f) do begin
        Read(f,i);
        if i in alpabet then begin
            have_letters:=true;
            inc(chars[i]);
            if chars[i]>chQuant then begin
                ch:=i;
                chQuant:=chars[i];
            end;
        end;
    end;
    GetLetter:=have_letters;            
end;        
var log:boolean;ch:char; chQuant:LongInt; f:charfile;
BEGIN
    log:=Input(f);
    if log then begin
        {WriteLn('Input <ok>');}
        Reset(f);
        log:=GetLetter(f,ch,chQuant);
        Close(f);
        if log then
            WriteLn('Наиболее часто всречается буква',#10#13,
                        ch,' в количестве ',chQuant,' шт.')
        else
            WriteLn('В тексте нет букв.');
    end else
        WriteLn('Программа завершена пользователем.');
    WriteLn('Нажмите <Enter>...');
    ReadLn;
END.
