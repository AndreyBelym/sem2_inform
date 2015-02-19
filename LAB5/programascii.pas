const alpabetcodes=[ord('a')..ord('z'),ord('A')..ord('Z'),
                ord('�')..ord('�'),ord('�')..ord('�'),ord('�')..ord('�')];
type bytefile=file of byte;
function GetFiles(var fin:bytefile;var fout:text):boolean;
function GetSourceFile(var f:text):integer;
var ch:char;error:integer;
    fileName:string;
begin
    repeat
        WriteLn('������ ��� 䠩�� ��� �������');
        Write('����:');ReadLn(fileName);
        Assign(f,fileName);
        {$I-}
            Reset(f);
        {$I+}
        error:=ioresult;
        if error<>0 then begin
            WriteLn('���ࠢ��쭮� ��� 䠩��! ������� ����? <Y>/<N>');
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
        WriteLn('������ ��� �६������ 䠩��');
        Write('����:');ReadLn(fileName);
        Assign(f,fileName);
        {$I-}
            ReWrite(f);
        {$I+}
        error:=ioresult;
        if error<>0 then begin
            WriteLn('�訡�� �� ᮧ����� 䠩��! ������� ����? <Y>/<N>');
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
        WriteLn('������ ��� 䠩��-१����.');
        Write('����:');ReadLn(fileName);
        Assign(f,fileName);
        {$I-}
            ReWrite(f);
        {$I+}
        error:=ioresult;
        if error<>0 then begin
            WriteLn('�訡�� �� ᮧ����� 䠩��! ������� ����? <Y>/<N>');
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
        Writeln('���뢠� ����� �� �६���� 䠩�...');
        Reset(fsrc);Rewrite(fin);
		while not EOF(fin) do begin
            Read(fsrc,ch);
            i:=ord(ch);
            Write(fin,i);
        end;
        WriteLn('�믮�����!');
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
    WriteLn('�믮�����:');
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
	WriteLn('�ணࠬ�� ��室�� ᠬ�� ��� ����������� �㪢� � ⥪�� ᫥���騬 ��ࠧ��:');
	WriteLn('�ணࠬ�� ���뢠�� ᨬ���� �� ⥪�⮢��� 䠩��;');
	WriteLn('��⥬ �����뢠�� �� ���� �� �६���� ⨯���஢���� 䠩�;');
	WriteLn('����� ���뢠�� ��� 䠩� � ०��� ��אַ�� ����㯠, ���뢠�� �����, � ��室�� ᠬ�� ����� �㪢�;');
	WriteLn('�뮤�� १���� �� �࠭ � � ⥪�⮢� 䠩�.');
    log:=GetFiles(fin,fout);
    if log then begin
		
        WriteLn('�믮������ ���� ᠬ�� ��� ������饩�� �㪢�.');
        log:=GetLetter(fin,ch,chQuant);
        ReWrite(fout);
        if log then begin
            WriteLn('�������� ��� ���砥��� �㪢�',#10#13,
                        ch,' � ������⢥ ',chQuant,' ��.');
            WriteLn(fout,'�������� ��� ���砥��� �㪢�',#10#13,
                        ch,' � ������⢥ ',chQuant,' ��.');
        end else begin
            WriteLn('� ⥪�� ��� �㪢.');
            WriteLn(fout,'� ⥪�� ��� �㪢.');
        end;
        close(fout);
    end else
        WriteLn('�ணࠬ�� �����襭� ���짮��⥫��.');
    WriteLn('������ <Enter>...');
    ReadLn;
END.
