# The Git Command Line Lab: The Multi-Feature Release Nightmare

This is a self-contained, highly practical command-line laboratory designed to take you from knowing only `git add/commit/push` to mastering advanced Git operations (Stashing, Rebasing, Interactive Squashing, Hard Resets, and Reflog Recovery).

You will run this entire lab locally on your computer.

## Lab Setup: Create Your Testing Sandbox

Open your terminal, copy the following block, paste it into your terminal, and hit Enter. This will create a fresh directory, initialize a Git repository, and write a base program file to start with.

```
# Copy and run this setup block in your terminal
mkdir -p git_nightmare_sandbox
cd git_nightmare_sandbox
git init
git config user.name "CS Student"
git config user.email "student@buet.ac.bd"

cat << 'EOF' > app.cpp
#include <iostream>

void runApplication() {
    std::cout << "Starting core application engine..." << std::endl;
}

int main() {
    runApplication();
    return 0;
}
EOF

git add app.cpp
git commit -m "Initial commit: Core engine structure"
```

Verify your setup succeeded by running:

```
git log --oneline
```

_Expected Output:_ `[some-hash] Initial commit: Core engine structure`

## Step 1: The Interrupted Feature (Stashing & Context Switching)

### The Setup (Create the Disaster)

Imagine you are writing a complex feature in a separate branch. You have written broken, non-compiling code. Suddenly, production crashes and you must fix a critical bug on `main` immediately, but you aren't ready to commit your broken work.

Run these commands to simulate this state:

```
# Create and switch to the analytics branch
git checkout -b feature-analytics

# Inject half-written, broken analytics code
cat << 'EOF' >> app.cpp

void runHeavyAnalytics() {
    // TODO: Finish this tomorrow. It currently crashes.
    int* ptr = nullptr;
    *ptr = 100; 
EOF
```

If you type `git status`, you will see `app.cpp` has modified changes. If you try to switch to `main`, your uncommitted work might block you, or get carried over messily.

### The Challenge

1. Save your uncommitted analytics code to Git's hidden temporary shelf (the stash) without creating a commit.
    
2. Verify that your working directory is completely clean and the broken analytics code has vanished.
    
3. Switch back to `main`.
    
4. Create a hotfix branch named `hotfix-typo`.
    
5. Fix a critical "typo" in `app.cpp` (e.g., change `"Starting core application engine..."` to `"Starting Core Engine v1.0..."`).
    
6. Commit the fix and merge it back into `main`.
    
7. Switch back to your `feature-analytics` branch.
    
8. Retrieve your half-written work from the stash so you can continue working on it.
    

### Your Cheat Sheet & Solution Commands

- **To stash your changes safely:**
    
    ```
    git stash -u
    ```
    
    _(The `-u` ensures any untracked files you created are also safely hidden)._
    
- **To verify your stash list:**
    
    ```
    git stash list
    ```
    
- **To perform the hotfix on main:**
    
    ```
    git checkout main
    git checkout -b hotfix-typo
    # (Make edit to app.cpp to change the console message)
    git add app.cpp
    git commit -m "fix: updated startup console message text"
    git checkout main
    git merge hotfix-typo
    git branch -d hotfix-typo
    ```
    
- **To restore your stashed analytics code:**
    
    ```
    git checkout feature-analytics
    git stash pop
    ```
    

### What to Google when stuck on this step:

- `"How to check what is inside git stash without popping"`
    
- `"Difference between git stash pop and git stash apply"`
    

## Step 2: The Linear History Mandate (Rebasing)

### The Setup (Create the Disaster)

Your team lead has a strict rule: **No merge commits on main.** The project history must be a single, straight linear line.

Right now, you are on `feature-analytics` with your stashed changes restored. You are going to write some analytics code and commit it. But while you were doing that, another developer pushed changes to `main`.

Run these commands to set up this scenario:

```
# Make sure you are on the analytics branch
git checkout feature-analytics

# Clean up the broken app.cpp from Step 1 so it compiles
cat << 'EOF' > app.cpp
#include <iostream>

void runApplication() {
    std::cout << "Starting Core Engine v1.0..." << std::endl;
}

void runAnalytics() {
    std::cout << "Processing analytical models..." << std::endl;
}

int main() {
    runApplication();
    runAnalytics();
    return 0;
}
EOF

# Commit this analytics work locally
git add app.cpp
git commit -m "feat: added basic analytical modules"

# Simulate another developer making changes to main in the background
git checkout main
cat << 'EOF' > app.cpp
#include <iostream>

void runApplication() {
    std::cout << "Starting Core Engine v1.0..." << std::endl;
}

void checkSystemSecurity() {
    std::cout << "Checking system vulnerabilities... OK" << std::endl;
}

int main() {
    runApplication();
    checkSystemSecurity();
    return 0;
}
EOF
git add app.cpp
git commit -m "security: added system vulnerability scan checks"
```

If you merge `feature-analytics` into `main` using a standard `git merge`, Git will force a "Merge Commit" because the history has branched. You must avoid this.

### The Challenge

1. Ensure your local `feature-analytics` commits are re-played _on top_ of the new security commits that happened on `main`.
    
2. This will cause a conflict because both branches modified `app.cpp`.
    
3. Open `app.cpp` in your text editor. Manually resolve the conflict: combine both functions (`checkSystemSecurity` and `runAnalytics`) in `main()`. Remove the `<<<<<<<`, `=======`, and `>>>>>>>` conflict markers.
    
4. Complete the rebase process.
    
5. Verify that your Git log is a perfectly straight line with no splits.
    

### Your Cheat Sheet & Solution Commands

- **To begin the rebase:**
    
    ```
    git checkout feature-analytics
    git rebase main
    ```
    
    _(Git will pause and complain about conflict in `app.cpp`)_
    
- **To resolve the conflict:** Open `app.cpp` in your text editor. It will look like this:
    
    ```
    <<<<<<< HEAD
    void checkSystemSecurity() { ... }
    =======
    void runAnalytics() { ... }
    >>>>>>> feat: added basic analytical modules
    ```
    
    Edit the file so it cleanly includes both features:
    
    ```
    #include <iostream>
    
    void runApplication() {
        std::cout << "Starting Core Engine v1.0..." << std::endl;
    }
    
    void checkSystemSecurity() {
        std::cout << "Checking system vulnerabilities... OK" << std::endl;
    }
    
    void runAnalytics() {
        std::cout << "Processing analytical models..." << std::endl;
    }
    
    int main() {
        runApplication();
        checkSystemSecurity();
        runAnalytics();
        return 0;
    }
    ```
    
- **To continue the rebase once edited:**
    
    ```
    git add app.cpp
    git rebase --continue
    ```
    

### Verification (Must look like this!)

Run: `git log --oneline --graph --all` Your history tree should be a completely straight line, like this:

```
* (HEAD -> feature-analytics) feat: added basic analytical modules
* (main) security: added system vulnerability scan checks
* fix: updated startup console message text
* Initial commit: Core engine structure
```

## Step 3: Cleaning Up the Mess (Interactive Rebasing & Squashing)

### The Setup (Create the Disaster)

You spent the last three hours trying to write a basic Authentication file. Because you kept getting stuck, you made a ton of garbage micro-commits with terrible messages.

Run these commands to simulate this bad history on a new branch:

```
git checkout main
git checkout -b feature-auth

echo "// Auth structure" >> auth.cpp
git add auth.cpp
git commit -m "start auth"

echo "void init() {}" >> auth.cpp
git add auth.cpp
git commit -m "added function"

echo "void init() { // fixed typo }" >> auth.cpp
git add auth.cpp
git commit -m "fix typo"

echo "void init() { // actually works now }" >> auth.cpp
git add auth.cpp
git commit -m "fixed typo again grrr"
```

If you run `git log --oneline`, you have 4 ugly commits. If you send this to your team lead, they will reject your Pull Request.

### The Challenge

Combine (squash) all 4 of these messy commits into **one single, clean architectural commit** named: `"feat(auth): implement core authentication structure"`.

### Your Cheat Sheet & Solution Commands

- **To start interactive rebase on the last 4 commits:**
    
    ```
    git rebase -i HEAD~4
    ```
    
- **Inside the interactive text editor that pops up:** You will see a list of your commits in chronological order (oldest at the top):
    
    ```
    pick a1b2c3d start auth
    pick e5f6g7h added function
    pick i9j0k1l fix typo
    pick m3n4o5p fixed typo again grrr
    ```
    
    Change `pick` to `squash` (or just `s`) for the bottom three commits:
    
    ```
    pick a1b2c3d start auth
    squash e5f6g7h added function
    squash i9j0k1l fix typo
    squash m3n4o5p fixed typo again grrr
    ```
    
    Save and close the editor (if using Vim, press `Esc`, type `:wq`, and hit `Enter`).
    
- **In the second text editor that pops up:** Delete all the old, messy commit messages and type your final clean message:
    
    ```
    feat(auth): implement core authentication structure
    ```
    
    Save and close the editor.
    

### Verification

Run: `git log --oneline` You should now see only **one** clean commit for your authentication feature.

## Step 4: The Production Disaster (Reset vs. Revert)

### The Setup (Create the Disaster)

You have accidentally pushed a breaking change directly to your `main` branch. It is already live in production.

Run these commands to simulate this:

```
git checkout main
echo "CRITICAL SYSTEM EXPLOIT CODE" >> app.cpp
git add app.cpp
git commit -m "update: minor performance improvements"
```

Because this is on `main` and has theoretically been pushed to a remote server, **you cannot rewrite history** using `git reset --hard` because it will break other developers' local repositories when they pull. You must neutralize it safely.

On the other hand, you also have a local experiment branch where you wrote garbage, and you want to completely destroy those commits and erase them from existence locally.

```
git checkout -b local-garbage-experiment
echo "GARBAGE CODE" >> app.cpp
git add app.cpp
git commit -m "useless test 1"
echo "MORE GARBAGE" >> app.cpp
git add app.cpp
git commit -m "useless test 2"
```

### The Challenge

1. On the `main` branch, neutralize the "exploit code" commit safely using a public-safe commit that undoes the changes _without_ erasing the commit history.
    
2. On your `local-garbage-experiment` branch, violently delete the last 2 commits and reset your files to exactly how they looked before you started experimenting.
    

### Your Cheat Sheet & Solution Commands

- **To safely neutralize the commit on `main` (Public Safe):**
    
    ```
    git checkout main
    git revert HEAD
    ```
    
    _(This creates a brand new commit that mathematically negates the changes of the last commit)._
    
- **To violently delete local commits (Local Only):**
    
    ```
    git checkout local-garbage-experiment
    git reset --hard HEAD~2
    ```
    
    _(This rewinds your branch pointer 2 steps back and completely wipes your working directory clean)._
    

## Step 5: Resurrecting the Dead (The Reflog Rescue)

### The Setup (Create the Disaster)

You are working on a highly valuable feature branch named `lost-treasure`. In a moment of panic or confusion, you switch to `main` and force-delete the branch.

Run these commands to simulate this catastrophic mistake:

```
# Create the branch and add a crucial commit
git checkout main
git checkout -b lost-treasure
echo "VALUABLE INTELLECTUAL PROPERTY" > treasure.txt
git add treasure.txt
git commit -m "feat: core value engine secret logic"

# Switch back to main and violently delete the branch
git checkout main
git branch -D lost-treasure
```

If you type `git branch`, the branch is completely gone. If you run `git log`, the commit is nowhere to be seen. Your terminal tells you it is destroyed.

### The Challenge

Find the raw commit hash of your deleted work and restore the branch exactly as it was before you deleted it.

### Your Cheat Sheet & Solution Commands

- **Open Git's underlying transaction ledger (the reflog):**
    
    ```
    git reflog
    ```
    
    _(This prints a sequential list of every single action you have taken in this repo, regardless of what branch you were on, even if commits were deleted)._
    
- **Locate the line where you committed the treasure:** Look for a line that looks like this: `abc1234 HEAD@{1}: commit: feat: core value engine secret logic`
    
- **Restore the branch using that raw hash:**
    
    ```
    # Re-create the branch pointing directly at that lost commit hash
    git checkout -b recovered-treasure abc1234
    ```
    
    _(Replace `abc1234` with the actual hash you found in your reflog output)._
    

### Verification

Run `ls` or `cat treasure.txt`. Your lost work is back from the dead!