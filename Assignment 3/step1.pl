% By Kumail Raza %

% WORDS %
word(prolog, [p,r,o,l,o,g], 6).
word(perl, [p,e,r,l], 4).
word(online, [o,n,l,i,n,e], 6).
word(web, [w,e,b], 3).
word(gnu, [g,n,u], 3).
word(nfs, [n,f,s], 3).
word(sql, [s,q,l], 3).
word(mac, [m,a,c], 3).
word(emacs, [e,m,a,c,s], 5).
word(xml, [x,m,l], 3).
word(linux, [l,i,n,u,x], 5).
word(java, [j,a,v,a], 4).
word(google, [g,o,o,g,l,e], 6).
word(python, [p,y,t,h,o,n], 6).
word(parser, [p,a,r,s,e,r], 6).
word(coop, [c,o,o,p], 4).
word(loop, [l,o,o,p], 4).
word(fork, [f,o,r,k], 4).
word(kernal, [k,e,r,n,a,l], 6).
word(api, [a,p,i], 3).
word(mouse, [m,o,u,s,e], 5).
word(fifo, [f,i,f,o], 4).
word(pipe, [p,i,p,e], 4).

% WORD INTERSECTIONS %
intersection(Word1, Word2, Index1, Index2):-
    dif(Word1, Word2),
    word(Word1, List1, Length1),
    nth0(Index1, List1, Letter),
    Index1 < Length1,
    word(Word2, List2, Length2),
    nth0(Index2, List2, Letter),
    Index2 < Length2.

% CROSSWARD DATA %
crossward(W1,W2,W3,W4,W5,W6,W7,W8,W9,W10,W11):-
    intersection(W1, W6, 0, 0),
    intersection(W1, W7, 2, 0),
    intersection(W1, W9, 5, 0),
    intersection(W2, W7, 0, 2),
    intersection(W2, W8, 2, 0),
    intersection(W2, W9, 3, 2),
    intersection(W2, W10, 4, 0),
    intersection(W3, W10, 0, 1),
    intersection(W3, W11, 2, 3),
    intersection(W4, W8, 0, 2),
    intersection(W4, W10, 2, 2),
    intersection(W5, W7, 1, 5),
    word(W1, _, 6),
    word(W2, _, 5),
    word(W3, _, 3),
    word(W4, _, 3),
    word(W5, _, 3),
    word(W6, _, 4),
    word(W7, _, 6),
    word(W8, _, 3),
    word(W9, _, 3),
    word(W10, _, 3),
    word(W11, _, 5).
