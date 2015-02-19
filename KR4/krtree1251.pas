
var count:longint;
CONST  WordLen = 31;
CONST  Alphabet = ['a'..'z','A'..'Z','�'..'�','�'..'�'];
       Capitals = ['A'..'Z','�'..'�'];
TYPE  Word = string[WordLen];
    Node = ^TNode;
    TNode= RECORD
            key: Word;
            count:INTEGER;  (*������*)
            left, right: Node  (*������*)
    END;

VAR  line: INTEGER;  WF: Text;
    function cap(const ch:char):char;
    begin
         case ch of
         'a'..'z':cap:=UpCase(ch);
         '�'..'�':cap:=chr(ord(ch)-32);
         '�'..'�':cap:=chr(ord(ch)-80);
         '�':cap:='�';
         else cap:=ch;
         end;
    end;

    function Compare(const a,b:string):shortint;
    var lena,lenb,len:byte;
       i:byte;equal:boolean;
    begin
         lena:=length(a); lenb:=length(b);
         if lena > lenb then len:=lenb else len:=lena;
         i:=1;
         equal:=true;Compare:=0;
         while (i<=len) and (a[i]=b[i]) do begin
               inc(i);
         end;

         if i>len then begin
            if lena=lenb then
               Compare:=-1
            else Compare:=ord(lena<lenb);
         end else begin
             if cap(a[i]) <>'�' then
                Compare:=ord(a[i]<b[i])
             else
                 if b[i]<='�' then
                    Compare:=0
                 else
                     Compare:=1
         end;

    end;


    PROCEDURE search ( VAR w: Node;  VAR a: Word );
    BEGIN
        IF  w = NIL  THEN BEGIN (* ����� � ������ ���; �������� ����� ���� *)
            NEW( w );inc(count);
            w^.key := a;  w^.count:=1;  w^.left := NIL;  w^.right := NIL
        end
        ELSE Case Compare(w^.key,a)  of
             1:  search( w^.right, a);
             0: search( w^.left, a );
             -1: inc(w^.count);
        END;

    END {search};

    PROCEDURE Tabulate ( w: Node );
    BEGIN
        IF  w <> NIL  THEN BEGIN
            Tabulate( w^.left );
            Write( WF, w^.key,' ',w^.count);
            WriteLn(WF);
            Tabulate( w^.right )
        END
    END {Tabulate};

    PROCEDURE CrossRef ( VAR R: text );
        VAR  root: Node;  (* ������������ ���������� ������ ������ WF *)
            i: INTEGER;  ch: CHAR;  w: Word;
    BEGIN
        {write( WF, 0); Write(WF,'':6);}

        root:=NIL;  line := 0;
        Read( R, ch );
        WHILE  not eof(R)  DO begin
            IF  ch = #13  THEN BEGIN (*����� ������*)
                {WriteLn( WF );}
                INC( line );
                {Write (WF, line);  Write(WF,'':6-trunc(ln(line)/ln(10)));}
                Read( R, ch )
            end ELSE IF ch in Alphabet THEN BEGIN
                i := 1;
                REPEAT
                    IF  i < WordLen  THEN BEGIN  w[ i ] := cap(ch);  INC( i )  END;
                    {Write( WF, ch );}
                    Read( R, ch )
                UNTIL (i = WordLen) OR not(ch in Alphabet);

                w[0] := chr(i-1); (* ����� ������� ����� *)
                search( root, w )
            END ELSE BEGIN
                {Write( WF, ch );}
                Read( R, ch )
            END;
        END;
        {WriteLn( WF );  WriteLn( WF );}
        Tabulate( root )
    END {CrossRef};
    (* ����� ���������. ****************************************************************)


VAR  R: text;
BEGIN
    Assign(R,'voina.txt'); Assign(WF,'testtree.txt');
    Reset(R); Rewrite(WF);
    CrossRef(R);WriteLn('OK!');Readln;close(wf);
END.
