# Racing Game
Racing Game is a game created by Darren Sweeney, Eric O' Toole and Liam Hickey.

![alt tag](https://dsweeneyblog.files.wordpress.com/2017/03/fuck_this_game.png)

[Team Journal](https://docs.google.com/document/d/1ya9ImQhMHPgdHWxiWK-YT1KFYHf9t-UB1zWHdFtD7b8/edit?usp=sharing)

## Installation
The code compiles out of the box.

## Suggested git Workflow 
1. Clone the remote repository (once-off operation).
2. Create your a branch for the feature you are working on: `git checkout -b feature-name`
3. Add/stage your files: `git add .`
4. Commit your changes: `git commit -m 'Add some feature'`
5. Submit a pull request to fetch the latest version of the remote master: `git pull origin master --rebase`

    This command undoes your commits, applies the commits in the master branch to your feature branch, then applies your commits back to the feature branch.
6. Resolve any merge conflicts.
7. Push to your remote feature branch: `git push origin feature-name`
8. When your feature is complete, merge it with the master branch in three steps:

8.1 Switch to master branch: `git checkout master` 
8.2 Merge the feature branch with the master branch: `git merge feature-name`
8.3 Push to the remote master branch: `git push origin master`

## Credits
 Darren Sweeney
 Eric O' Toole
 Liam Hickey.
