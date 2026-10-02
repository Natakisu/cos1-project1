# Instructions

Update this document where indicated [look for the brackets!]. Replace text inside the brackets with your own information. For example: Course Name should be the name of this course, and not the generic words "Course Name".

<br>

## [ COS155-0 ]

- **[ Casey Johnson ]**
- **[ Sun, Oct 4, 2026 ]**

This paper addresses some of the topic matter covered in research and activity this week. Be sure to include reference links below to the research and information you used to complete this assignment.

## Topic: Terminal

Professional developers use Terminal daily. It's essential to understand some fundamental commands to use the application.

Update the information below to demonstrate your knowledge on this topic.

**1. Using Terminal, there are essential commands to know.**

List the correct Terminal commands to do the actions listed below. Replace **CMD** with the correct command sequence. You can keep or enhance the brief description.

**The last bullet provides an example**.

- [ cls ]: Clear the Screen
- [ cd ]: Print the "Working Directory"
- [ dir ]: List files and folders
- [ dir /a]: List files and folders, including invisible files
- [ dir ]: List all files and folders, in human readable form
- [ cd path\to\folder ]: Change directory
- [ cd \ ]: Change directory, go to root directory
- [ cd %USERPROFILE% ]: Change directory and go to user home directory
- [ cd . . ]: Change directory, go up one folder level
- [ cd . . \ . . ]: Change directory, go up two folder levels
- [ cd %USERPRROFILE%\Desktop ]: Change directory to my desktop!

**2. Using Terminal...**

**Folder Drop:** Try typing "cd" followed by a space, and then drag a folder into terminal and press return. Test this out and describe your results below.

[ When typing `cd` and dragging a folder into the terminal, the terminal automatically pastes the complete, absolute file path of the folder directly after the `cd` command (automatically adding quotes around paths with spaces). Pressing **Return** successfully changes the current working directory to the target folder, making navigation fast and eliminating path typing errors. ]

## Topic: Version Control & Git

Version control, also known as revision control, records changes to a file or set of files over time so that you can recall specific versions later. In this class, we are learning Git. Update the information below where indicated.

**1. There are three types of version control.**

[ Local Version Control Systems:]
[Keeps track of changes to files within a single local database or directory on a single computer.]

[Centralized Version Control Systems (CVCS):]
[Uses a single central server that stores the entire repository and history. Developers checkout files from the server, edit them locally, and commit changes back to the main server.]

[Distributed Version Control Systems (DVCS):]
[Clients don't just check out the latest snapshot of the files; every developer fully clones the entire repository, including its full version history, onto their local machine.]

**2. Using Terminal, there are also essential Git commands to know.**

List the correct Git commands to do the actions listed below in Terminal. Replace CMD with the correct command and keep or enhance the brief description.

- [git clone <repository_url>]: Clone a repository
- [git config --global user.name "Your Name" ]: Set-up a global user name
- [git config --global user.email "your_email@example.com"]: Set-up a global email address (to match my GitHub account email)
- [git status]: Shows the current state of your directory and staging area
- [git add <file_name>]: Add modified files to the next commit
- [git commit -m "Your commit message"]: Make a commit with a new message
- [git log]: Show my commit history
- [git --help]: Show Git's help screen

**3. Connecting to GitHub using Terminal.**
HTTPS is the the correct way to connect to GitHub in this course. Describe how you connect to GitHub from Terminal using this protocol. What steps do you take?

[ Describe the steps to connect Terminal to a GitHub repo here ]
**1. Copy the HTTPS Clone URL from GitHub:**

- Go to your repository page on GitHub
    
- Click the green **Code** button near the top right of the repository
    
- Make sure the **HTTPS** tab is selected, then copy the provided web URL

**2. Open Terminal & Navigate to Your Target Directory:**

- Launch your Terminal
    
- Use the `cd` command to navigate to the folder on your local machine where you want to store your project repository

**3. Clone the Repository:**

- Run the command `git clone <HTTPS_URL>`, replacing `<HTTPS_URL>` with the URL you copied from GitHub.
    
- Press **Enter**. Git will download the repository files and create a new local folder matching your repository name.

**4. Navigate into Your Cloned Directory:**

- Change directories into the newly created folder:
    
    - `cd repository-name`

**5. Authenticate with GitHub (Personal Access Token / Credentials):**

- When you perform your first write action (e.g., running `git push`), Terminal will prompt you for your GitHub credentials:

[ Describe the steps to connect Terminal to a GitHub repo here ]

**4. Using .gitignore and Why it's Important**  
Most repositories contain a .gitignore file.

- What is the purpose of this file?
  <br>
  [The `.gitignore` file tells Git which files, file types, or directories to intentionally track and exclude from your version control repository. This prevents unneeded, system-generated, or sensitive files from cluttering your repository history or being shared publicly.]

- What is the "**.DS_Store**" file and why would you want to ignore it?
  <br>
  [`.DS_Store` (Desktop Services Store) is an invisible system file automatically created by macOS Finder to store custom folder view attributes (such as icon positions, window sizes, and background settings). You want to ignore it because it contains user-specific desktop layout preferences that are irrelevant to your project code and can cause unnecessary file conflicts when collaborating with others across different operating systems.]

- What other file or folder would you want to add to a .gitignore file and why?
  <br>
  [- You would want to ignore build output directories (such as the `x64/`, `Debug/`, `Release/`, or `.vs/` folders in Visual Studio). These folders contain large, automatically generated binary and compiled files that can easily be rebuilt on any developer's machine; committing them increases the repository size and leads to merge conflicts.]

<br>

# Reference Links

Replace the example references below with your own links and recommended resources. It is acceptable to provide multiple links for a single topic and to use material provided to you in this class. You are encouraged to link to your own independent research as well.

[The official Git documentation and GitHub Docs were the most helpful resources this week. The Git documentation provided simple breakdowns of the command line interface and explained how local staging works. GitHub Docs made setting up personal access tokens and configuring the .gitignore file easy to follow for Windows environments.]

**Terminal Commands**  
[Windows Command Prompt Cheat Sheet - Git-Tower]
(https://www.git-tower.com/blog/command-line-cheat-sheet/)

**Three Types of Version Control**  
[About Version Control - Git Documentation]
(https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control)

**Git Commands**  
[Git Cheat Sheet - GitHub Education]
(https://education.github.com/git-cheat-sheet-education.pdf)

**Connecting to GitHub using Terminal**  
[About Remote Repositories - GitHub Docs]
(https://docs.github.com/en/get-started/getting-started-with-git/about-remote-repositories)

**Using .gitignore and Why it's Important**  
[Ignoring Files - GitHub Docs]
(https://docs.github.com/en/get-started/getting-started-with-git/ignoring-files)
