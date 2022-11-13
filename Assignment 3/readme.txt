Step 1:
Step 1.pl's query is in the following form:
?- crossward(W1,W2,W3,W4,W5,W6,W7,W8,W9,W10,W11).

This returns an output int the following way:
W1 = prolog,
W10 = xml,
W11 = emacs,
W2 = linux,
W3 = mac,
W4 = sql,
W5 = web,
W6 = perl,
W7 = online,
W8 = nfs,
W9 = gnu

W(number) represents each word in the crossward. They are counted from left to right top down. That means that it counts the words on teh first row going left from right first, then second row, then third row, etc. until all of the across words are done. It then starts counting from top left down for the acrosses.

selectedwords.txt:

This file will just hold a list of all the accepted words with a newline in between each one.
It uses the same priority as explained above: left to right starting from the top row going down. Once all the across words are done, it does the down words in a priority from top down starting from the leftmost column


When using prolog on step2.pl, the query used should be:
?- crossward.
This should write to selectedwords.txt.

