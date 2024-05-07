HOMEWORK 6: INVERSE WORD SEARCH


NAME:  Mark Evans


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Submitty

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  15 hours


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?


O(8^(rwh) * l^2 * whfs * 8^l) 
r = number of words to be placed on board
w = width of board
h = height of board
l = length of word
f = number of fobiden words
s = number of solutions

Since we try to place each word in all 8 directions around on each spot of the board we initally get 8^(rwh). Then when we try to confrim if a word can fit in that spot we get l^2. Then when we check for a negative word on the board during the placement we get whf * 8^l. Then after printing the words we have to also then multiply it by s. After multiplying all the time complexities together you get O(8^(rwh) * l^2 * whfs * 8^l).


MISC. COMMENTS TO GRADER:  
Optional, please be concise!




## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

It was hard to figure out the steps needed to creat a single board in a timely matter with recursion. After figuring out how the normal word search that was recommended to review it helped me come up with a way to how to get to one solution. After that it hard to implement a way to remove boards that had the negative words in them somewhat effiecently. I there were also a case where a space was added at the end of a line so I needed to remove the space in code. Then I needed a way to fill the board with letters if all the words fit on the board without filling all the space which hurt my code a lot. There was also a case where negative words where still showing even though I was checking as I was placing the words so I added a function to check for the bad words after the board was complete. A lot of niche cases came up and had to find ways to solve them which slowed down the program a lot
