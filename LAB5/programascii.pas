const alpabetcodes=[ord('a')..ord('z'),ord('A')..ord('Z'),
                ord('А')..ord('Я'),ord('а')..ord('п'),ord('р')..ord('ё')];
type bytefile=file of byte;
function GetFiles(var fin:bytefile;var fout:text):boolean;
function GetSourceFile(var f:text):integer;
var ch:char;error:integer;
    fileName:string;
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
    if error=0 then
		Close(f);
	GetSourceFile:=error;
end;

function GetInputFile(var f:bytefile):integer;
var ch:char; error:integer;
    fileName:string;
begin
    repeat
        WriteLn('Введите имя временного файла');
        Write('Файл:');ReadLn(fileName);
        Assign(f,fileName);
        {$I-}
            ReWrite(f);
        {$I+}
        error:=ioresult;
        if error<>0 then begin
            WriteLn('Ошибка при создании файла! Повторить ввод? <Y>/<N>');
            ReadLn(ch);
        end;
    until (UpCase(ch)='N') or (error=0);
    if error=0 then begin
		Close(f);
	end;
	GetInputFile:=error;
end;

function GetOutputFile(var f:text):integer;
var ch:char; error:integer;
    fileName:string;
begin
    repeat
        WriteLn('Введите имя файла-результата.');
        Write('Файл:');ReadLn(fileName);
        Assign(f,fileName);
        {$I-}
            ReWrite(f);
        {$I+}
        error:=ioresult;
        if error<>0 then begin
            WriteLn('Ошибка при создании файла! Повторить ввод? <Y>/<N>');
            ReadLn(ch);
        end;
    until (UpCase(ch)='N') or (error=0);
	if error=0 then
		Close(f);
    GetOutputFile:=error;
end;
var error:integer; fsrc:text;i:byte; ch:char;
begin
    error:=GetSourceFile(fsrc);
    if error=0 then
        error:=GetInputFile(fin);
    if error=0 then
        error:=GetOutputFile(fout);
    if error=0 then begin
        Writeln('Считываю данные во временный файл...');
        Reset(fsrc);Rewrite(fin);
		while not EOF(fin) do begin
            Read(fsrc,ch);
            i:=ord(ch);
            Write(fin,i);
        end;
        WriteLn('Выполнено!');
		Close(fsrc);Close(fin);
	end;

    GetFiles:=error=0;
end;

function GetLetter(var f:bytefile;var ch:char;var chQuant:longint):boolean;
type symboltype=byte;const maxsymbolcode=255;
var  chars:array [symboltype] of longint; have_letters:boolean;i:symboltype;
begin
    for i:=0 to maxsymbolcode do
        chars[i]:=0;
    chQuant:=0;ch:=#0;have_letters:=false;
    WriteLn('Выполнено:');
    Write(0:3,'%');
	Reset(f);
    while not EOF(f) do begin
        Read(f,i);Write(#13,FilePos(f)/FileSize(f)*100:3:0,'%');
        if i in alpabetcodes then begin
            have_letters:=true;
            inc(chars[i]);
            if chars[i]>chQuant then begin
                ch:=chr(i);
                chQuant:=chars[i];
            end;
        end;
    end;
	Close(f);
    GetLetter:=have_letters; WriteLn;
end;

var log:boolean;ch:char; chQuant:LongInt; fin:bytefile; fout:text;
BEGIN
	WriteLn('Программа находит самую часто встречающююся букву в тексте следующим образом:');
	WriteLn('Программа считывает символы из текстового файла;');
	WriteLn('затем записывает их коды во временный типизированный файл;');
	WriteLn('далее открывает этот файл в режиме прямого доступа, считывает данные, и находит самую частую букву;');
	WriteLn('выодит результат на экран и в текстовый файл.');
    log:=GetFiles(fin,fout);
    if log then begin
		
        WriteLn('Выполняется поиск самой часто встречающейся буквы.');
        log:=GetLetter(fin,ch,chQuant);
        ReWrite(fout);
        if log then begin
            WriteLn('Наиболее часто всречается буква',#10#13,
                        ch,' в количестве ',chQuant,' шт.');
            WriteLn(fout,'Наиболее часто всречается буква',#10#13,
                        ch,' в количестве ',chQuant,' шт.');
        end else begin
            WriteLn('В тексте нет букв.');
            WriteLn(fout,'В тексте нет букв.');
        end;
        close(fout);
    end else
        WriteLn('Программа завершена пользователем.');
    WriteLn('Нажмите <Enter>...');
    ReadLn;
END.
