{R+}
Program ArrayAnalyze;

{----------------��������� ����� ������------------------}
{��ࠬ����: ���-�� ����⮢ ���ᨢ�; ���ᨢ ��� �������; �᫮ ��� �������; ��६����� ���ﭨ�}
procedure InputData(var N:integer;var A:array of Real; var K: real; var log:boolean);
var i:integer; buf:string; code:integer; ch:char;
begin
    ch:='Y';   {�� ��砩, �᫨ ���짮��⥫� �� ࠧ� �� �訡����}
    repeat   
        WriteLn('������ N. N-楫��, N>=1 � N<=',High(A)+1);
        Write('N:');ReadLn(buf); Val(buf,N,code);
        if code<>0 then begin   {n-楫��?}
            WriteLn('�������⨬�� ���祭�� N.');
            WriteLn('������� ����?(y/n)');
            ReadLn(ch);
        end
        else
    	    if (N<1) or (N>High(A)+1) then begin {n-� ��������� �����ᮢ ���ᨢ�?}
    	        code:=-1; 
                WriteLn('N<1 ��� N>',High(A)+1,'!');
                WriteLn('������� ����?(y/n)');
                ReadLn(ch);
            end;
    until (Upcase(ch)='N') or (code=0); {��������, ����� �ࠢ��쭮, ��� ���짮��⥫� �⪠�����}
    
    if UpCase(ch)<>'N' then begin {�᫨ �� �⪠�����, �}
        i:=1;
        repeat
            WriteLn('���� ����� A. ������ ����� �[',i,'] - ����⢥���� �᫮');
            Write('A[',i,']:');ReadLn(buf); Val(buf,A[i-1],code);
            if code<>0 then begin {A[i] - ����⢥����?}
                WriteLn('�������⨬�� ���祭�� �����.');
                WriteLn('������� ����?(y/n)');
                ReadLn(ch);
            end else 
                inc(i); code:=1;
        until (Upcase(ch)='N') or (i>N);{��������, ����� �� �ࠢ����, ��� ���짮��⥫� �⪠�����}
    end;
    
    if UpCase(ch)<>'N' then begin {�᫨ �� �⪠�����, �}
        
        repeat
            WriteLn('������ K - ����⢥���� �᫮.');
            Write('K:');ReadLn(buf); Val(buf,K,code);
            if code<>0 then begin {A[i] - ����⢥����?}
                WriteLn('�������⨬�� ���祭�� K.');
                WriteLn('������� ����?(y/n)');
                ReadLn(ch);
            end;
        until (Upcase(ch)='N') or (code=0); {��������, ����� �ࠢ��쭮, ��� ���짮��⥫� �⪠�����}
    end;
    log:=UpCase(ch)<>'N'; {�� �⪠����� �� ���짮��⥫�?}
end;

{----------------��������� �������� ������------------------}
{��ࠬ����: ���-�� ����⮢ ���ᨢ�; ���ᨢ ��� �������; �᫮ ��� �������; ��६����� ���ﭨ�}
procedure CheckData(const N:integer;const A:array of Real; const K: real; var log:boolean);
var i:integer; ch:char;
begin
    WriteLn('����� A:');
    for i:=0 to N-1 do
        Write(A[i]:1:4,' ');
    WriteLn;
    WriteLn('�������� A �ࠢ�������� � ',K:1:4);
    WriteLn('OK?(y/n)');
    ReadLn(ch);
    log:=UpCase(ch)='Y';{���짮��⥫� �訫 �த������...}
end;

{----------------��������� ������� �������------------------}
{��ࠬ����: ���-�� ����⮢ ���ᨢ�; ���ᨢ ��� �������; �᫮ ��� �������; ��६����� ���ﭨ�;
                ���-�� ����⮢ ࠢ��� �; ������ �; ������ �}
procedure Analyze(const N:integer;const A: array of Real;const K: real; var eq,und,ov:integer);
var i:integer;
begin
    eq:=0;ov:=0;und:=0;
    for i:=0 to N-1 do
        if A[i]=K then
            inc(eq)
        else
            if A[i]>K then
                inc(ov)
            else
                inc(und);
end;

{----------------��������� ������ ����������� �� �����------------------}
{��ࠬ����: ���-�� ����⮢ ࠢ��� �; ������ �; ������ �; K - �᫮ ��� �������}
procedure PrintData(const eq,und,ov:integer;const K:real);
begin
    WriteLn('� ����� � ',eq,' ����⮢, ࠢ��� ',K:1:4);
    WriteLn('� ����� � ',ov,' ����⮢, ������ ',K:1:4);
    WriteLn('� ����� � ',und,' ����⮢, ������ ',K:1:4);
end;

{----------------�������� �����------------------}
const nn=5; {����. ࠧ��� ���ᨢ�}
var N,eq,und,ov:integer; 
{��饥 ���-�� ����⮢; ���-�� ����⮢ ࠢ��� �; ������ �; ������ �}
    A:array [1..nn] of real; K:real; 
{��������㥬� ���ᨢ; �᫮ ��� �������}
    log:boolean;
{���ﭨ� �ணࠬ��(���� �訡��/��� �訡��}
BEGIN
WriteLn('�ணࠬ�� ��室�� � ����� A ����� N'); 
WriteLn('������⢮ ����⮢ A[i]>K, A[i]<K � A[i]=K.');
InputData(N,A,K,log); {������ �����}
if log then {�᫨ �� ���,�...}
    CheckData(N,A,K,log); {����� ���짮��⥫� �� ��� �஢���.}
if log then begin {� �᫨ ����� ��� ���}
    WriteLn;
    eq:=0;ov:=0;und:=0;
    Analyze(N,A,K,eq,ov,und); {��������㥬 ���ᨢ}
    PrintData(eq,ov,und,K); {�뢮��� ��������}
end else
    WriteLn('�ணࠬ�� �����襭�'); 
WriteLn('������ <Enter>...');
ReadLn;
END.
