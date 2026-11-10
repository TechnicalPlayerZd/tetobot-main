# Instruction manual

## When giving to AI
Submit files to AI(Intially): 

main.h
robot.hpp
main.cpp
robot.cpp

### What happens after
Then use use "pros upload" command in the PROS terminal. It would work when you see uploading.
Then also it's neccessary to check the terminal and output in the vs code app.



## How to colaberate with the other coder(s)
This is slightly more complex, probably ask for asistence.


Otherwise, this is the work in process instructions

git add .
git commit -m "<Insert commit message here>"
git push origin main


What happened is that you uploaded the changes to your fork of the project. From the project in github, you could create a pull request to change the main repositories code and keep everything synced.

In the case the original repository updates, use 

git fetch upstream
git merge upstream/main

