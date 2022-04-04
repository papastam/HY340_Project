%{

}%

%left "(", ")" 
%left "[", "]" 
%left ".",".."
%right "not", "++", "--", "-"
%left "*", "/", "\%"
%left "+"
%right "-"
%nonassoc ">", ">=", "<", "<="
%nonassoc "==", "!="
%left "and"
%left "or"
%left "="


%%

%%

