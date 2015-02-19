{R+}
Program ArrayAnalyze;

{----------------ПРОЦЕДУРА ВВОДА ДАННЫХ------------------}
{Параметры: кол-во элементов массива; массив для анализа; число для анализа; переменная состояния}
procedure InputData(var N:integer;var A:array of Real; var K: real; var log:boolean);
var i:integer; buf:string; code:integer; ch:char;
begin
    ch:='Y';   {на случай, если пользователь ни разу не ошибётся}
    repeat   
        WriteLn('Введите N. N-целое, N>=1 и N<=',High(A)+1);
        Write('N:');ReadLn(buf); Val(buf,N,code);
        if code<>0 then begin   {n-целое?}
            WriteLn('Недопустимое значение N.');
            WriteLn('Повторить ввод?(y/n)');
            ReadLn(ch);
        end
        else
    	    if (N<1) or (N>High(A)+1) then begin {n-в диапазоне индексов массива?}
    	        code:=-1; 
                WriteLn('N<1 или N>',High(A)+1,'!');
                WriteLn('Повторить ввод?(y/n)');
                ReadLn(ch);
            end;
    until (Upcase(ch)='N') or (code=0); {закончить, когда правильно, или пользователь отказался}
    
    if UpCase(ch)<>'N' then begin {если не отказался, то}
        i:=1;
        repeat
            WriteLn('Ввод вектора A. Введите элемент А[',i,'] - вещественное число');
            Write('A[',i,']:');ReadLn(buf); Val(buf,A[i-1],code);
            if code<>0 then begin {A[i] - вещественное?}
                WriteLn('Недопустимое значение элемента.');
                WriteLn('Повторить ввод?(y/n)');
                ReadLn(ch);
            end else 
                inc(i); code:=1;
        until (Upcase(ch)='N') or (i>N);{закончить, когда все правильные, или пользователь отказался}
    end;
    
    if UpCase(ch)<>'N' then begin {если не отказался, то}
        
        repeat
            WriteLn('Введите K - вещественное число.');
            Write('K:');ReadLn(buf); Val(buf,K,code);
            if code<>0 then begin {A[i] - вещественное?}
                WriteLn('Недопустимое значение K.');
                WriteLn('Повторить ввод?(y/n)');
                ReadLn(ch);
            end;
        until (Upcase(ch)='N') or (code=0); {закончить, когда правильно, или пользователь отказался}
    end;
    log:=UpCase(ch)<>'N'; {не отказался ли пользователь?}
end;

{----------------ПРОЦЕДУРА ПРОВЕРКИ ДАННЫХ------------------}
{Параметры: кол-во элементов массива; массив для анализа; число для анализа; переменная состояния}
procedure CheckData(const N:integer;const A:array of Real; const K: real; var log:boolean);
var i:integer; ch:char;
begin
    WriteLn('Вектор A:');
    for i:=0 to N-1 do
        Write(A[i]:1:4,' ');
    WriteLn;
    WriteLn('Элементы A сравниваются с ',K:1:4);
    WriteLn('OK?(y/n)');
    ReadLn(ch);
    log:=UpCase(ch)='Y';{пользователь решил продолжить...}
end;

{----------------ПРОЦЕДУРА АНАЛИЗА МАССИВА------------------}
{Параметры: кол-во элементов массива; массив для анализа; число для анализа; переменная состояния;
                кол-во элементов равных К; меньших К; больших К}
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

{----------------ПРОЦЕДУРА ВЫВОДА РЕЗУЛЬТАТОВ НА ЭКРАН------------------}
{Параметры: кол-во элементов равных К; меньших К; больших К; K - число для анализа}
procedure PrintData(const eq,und,ov:integer;const K:real);
begin
    WriteLn('В векторе А ',eq,' элементов, равных ',K:1:4);
    WriteLn('В векторе А ',ov,' элементов, больших ',K:1:4);
    WriteLn('В векторе А ',und,' элементов, меньших ',K:1:4);
end;

{----------------ОСНОВНАЯ ЧАСТЬ------------------}
const nn=5; {макс. размер массива}
var N,eq,und,ov:integer; 
{общее кол-во элементов; кол-во элементов равных К; меньших К; больших К}
    A:array [1..nn] of real; K:real; 
{анализируемый массив; число для анализа}
    log:boolean;
{состояние программы(есть ошибки/нет ошибок}
BEGIN
WriteLn('Программа находит в векторе A длины N'); 
WriteLn('количество элементов A[i]>K, A[i]<K и A[i]=K.');
InputData(N,A,K,log); {вводим данные}
if log then {если все хорошо,то...}
    CheckData(N,A,K,log); {пусть пользователь их ещё проверит.}
if log then begin {и если опять всё хорошо}
    WriteLn;
    eq:=0;ov:=0;und:=0;
    Analyze(N,A,K,eq,ov,und); {анализируем массив}
    PrintData(eq,ov,und,K); {выводим везультаты}
end else
    WriteLn('Программа завершена'); 
WriteLn('Нажмите <Enter>...');
ReadLn;
END.
