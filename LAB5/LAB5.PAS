const
	alpabet:string='qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'+
            'ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ';
const highcode=255;
type bytefile=file of byte;
type freqarray=array [0..highcode] of longint;
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
    GetOutputFile:=error;
end;
var error:integer; fsrc:text;i:byte; ch:char;
begin
    error:=GetSourceFile(fsrc);
    if error=0 then
        error:=GetInputFile(fin);
    if error=0 then
        error:=GetOutputFile(fout);
    GetFiles:=error=0;
    if error=0 then begin
        Writeln('Считываю данные во временный файл...');
        {$I-}
        while not EOF(fsrc) and (ioresult=0) do begin

            Read(fsrc,ch);
            i:=ord(ch);
            Write(fin,i);

        end;
        {$I+}
        Close(fin);
        if EOF(fsrc) then begin
            WriteLn('Выполнено!');
		    Reset(fin);
		end else begin
		    GetFiles:=false;
		end;
        Close(fsrc);
	end;
end;

procedure GetCharsFreq(var f:bytefile;var CharsFreq:freqarray);
var  i:byte;
begin
    for i:=0 to highcode do
        CharsFreq[i]:=0;

    WriteLn('Выполнено:');
    Write(0:3,'%');
    while not EOF(f) do begin
        Read(f,i);Write(#13,FilePos(f)/FileSize(f)*100:3:0,'%');
        inc(CharsFreq[i]);

    end;

    WriteLn;
end;

procedure GetMostFreq(const CharsFreq:freqarray;
                            var HighestFreq:longint;var ChCount:byte; var MostFreqChars:array of char);
var k,i:byte; AlpabetSize,lettercode:byte;
begin
    AlpabetSize:=length(alpabet);
	k:=0;
    HighestFreq:=0;
	for i:=1 to AlpabetSize do begin
        lettercode:=ord(Alpabet[i]);
        if (CharsFreq[lettercode]>0)  then begin

            if (CharsFreq[lettercode]>HighestFreq) then begin
                HighestFreq:=CharsFreq[lettercode];
                k:=0;
                MostFreqChars[k]:=Alpabet[i]; inc(k);
			end else
                if CharsFreq[lettercode]=HighestFreq then begin

                   MostFreqChars[k]:=Alpabet[i]; inc(k);
                end;
        end;
	end;
	ChCount:=k;
end;

procedure PrintResult(var f:text;const HighestFq:LongInt;const Count:byte;
                            const Chars:array of char);
var i:byte;
begin
    if Count>1 then begin
		WriteLn(f,'Наиболее часто всречаются буквы');
		for i:=0 to Count-1 do begin
			Write(f,i+1,'.''',Chars[i],''' ');
		end;
	    WriteLn(f,#13#10,'в количестве ',HighestFq,' шт.');
		
	end else begin
		WriteLn(f,'Наиболее часто всречается буква',#10#13,
        '''',Chars[0],''' в количестве ',HighestFq,' шт.');
    end;
end;
var log:boolean;MostFqCount:byte; HighestFq:LongInt; fin:bytefile; fout:text;
    CharsFq:freqarray;MostFqChars:array[byte] of char;
BEGIN
	WriteLn('Программа находит самую часто встречающююся букву в тексте следующим образом:');
	WriteLn('Программа считывает символы из текстового файла-источника;');
	WriteLn('затем записывает их коды во входной типизированный файл;');
	WriteLn('далее открывает этот файл, считывает данные, и находит самую частую букву;');
	WriteLn('выводит результат на экран и в текстовый файл.');
    log:=GetFiles(fin,fout);
    if log then begin

        WriteLn('Выполняется поиск самой часто встречающейся буквы.');
        GetCharsFreq(fin,CharsFq);
		Close(fin);
        GetMostFreq(CharsFq,HighestFq,MostFqCount,MostFqChars);
		if MostFqCount<>0 then begin
        {$I-}
            PrintResult(output,HighestFq,MostFqCount,MostFqChars);
            PrintResult(fout,HighestFq,MostFqCount,MostFqChars);
        {$I+}
        end else begin
        {$I-}
            WriteLn('В тексте нет букв.');
            WriteLn(fout,'В тексте нет букв.');
        {$I+}
        end;
        Close(fout);
    end else
        WriteLn('Программа завершена пользователем.');
    WriteLn('Нажмите <Enter>...');
    ReadLn;
END.
