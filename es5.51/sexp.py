import sys

def parse_sexp(string):
    """
    >>> parse_sexp("(+ 5 (+ 3 5))")
    [['+', '5', ['+', '3', '5']]]
    
    """
    sexp = [[]]
    word = ''
    in_str = False
    for char in string:
        if char == '(' and not in_str:
            sexp.append([])
        elif char == ')' and not in_str:
            if word:
                sexp[-1].append(word)
                word = ''
            temp = sexp.pop()
            sexp[-1].append(temp)
        elif char in (' ', '\n', '\t') and not in_str:
            if word:
                sexp[-1].append(word)
                word = ''
        elif char == '\"':
            in_str = not in_str
        else:
            word += char
    return sexp[0]

if __name__ == '__main__':
    print parse_sexp(sys.argv[1]+"\n")
