const
	alpabet='qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'+
            'ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ';
const maxmemalloc=65521;
const highcode=255;
type bytearray=array [1..1] of byte;
type pbytearray=^bytearray;
type freqarray=array [0..highcode] of longint;
function GetData(var parray:pbytearray; var pCount:longint;var fout:text):boolean;
function GetSourceFile(var f:text;var size:longint):integer;
var ch:char;error:integer;
    fileName:string;tempf:file of char;
begin
    repeat
        WriteLn('Введите имя файла для анализа');
        Write('Файл:');ReadLn(fileName);
        Assign(f,fileName);Assign(tempf,fileName);
        {$I-}
            Reset(f);
        {$I+}
        error:=ioresult;
        if error<>0 then begin
            WriteLn('Неправильное имя файла! Повторить ввод? <Y>/<N>');
            ReadLn(ch);
        end else begin
            Close(f);
			ReSet(tempf); size:=FileSize(tempf);
            close(tempf); Reset(f);
			if size>maxmemalloc then begin
				error:=1;
				WriteLn('Файл слишком большой! Повторить ввод? <Y>/<N>');
				ReadLn(ch);
            end;
		end;
    until (UpCase(ch)='N') or (error=0);
	GetSourceFile:=error;
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
var error:integer; fsrc:text; ch:char;Size:longint;var i:longint;
begin
    error:=GetSourceFile(fsrc,Size);
    if error=0 then

        GetMem(parray,Size);
        if parray=NIL then error:=-1;
    if error=0 then
        error:=GetOutputFile(fout);
    if error=0 then begin
        Writeln('Считываются данные в оперативную память...');
		Write(0:3,'%');i:=0;
		while not EOF(fsrc) do begin
            Read(fsrc,ch);inc(i);
            parray^[i]:=ord(ch);Write(#13,i/size*100:3:0,'%');
        end;

		Close(fsrc);
		pCount:=i;
	end;
    writeln;
    GetData:=error=0;
end;

function GetCharsFreq(var parray:pbytearray; var pCount:longint;var CharsFreq:freqarray):boolean;
var  k:longint;
begin
    for k:=0 to highcode do
        CharsFreq[k]:=0;

    WriteLn('Выполнено:');
    Write(0:3,'%');
    for k:=1 to pCount do begin
        Write(#13,k/pCount*100:3:0,'%');
        inc(CharsFreq[parray^[k]]);
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
var log:boolean;MostFqCount:byte; HighestFq:LongInt; parray:pbytearray; fout:text;
    CharsFq:freqarray;MostFqChars:array[byte] of char;pCount:longint;
	i:byte;
BEGIN
	WriteLn('Программа находит самую часто встречающююся букву в тексте следующим образом:');
	WriteLn('Программа считывает символы из текстового файла;');
	WriteLn('затем записывает их коды во временный типизированный файл;');
	WriteLn('далее открывает этот файл в режиме прямого доступа, считывает данные, и находит самую частую букву;');
	WriteLn('выодит результат на экран и в текстовый файл.');
    log:=GetData(parray,pCount,fout);
    if log then begin

        WriteLn('Выполняется поиск самой часто встречающейся буквы.');
        GetCharsFreq(parray,pCount,CharsFq);
        FreeMem(parray,pCount);
        GetMostFreq(CharsFq,HighestFq,MostFqCount,MostFqChars);
        if MostFqCount>0 then begin
            PrintResult(output,HighestFq,MostFqCount,MostFqChars);
            PrintResult(fout,HighestFq,MostFqCount,MostFqChars);
        end else begin
            WriteLn('В тексте нет букв.');
            WriteLn(fout,'В тексте нет букв.');
        end;
        Close(fout);
    end else
        WriteLn('Программа завершена пользователем.');
    WriteLn('Нажмите <Enter>...');
    ReadLn;
END.
