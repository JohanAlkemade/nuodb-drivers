Contribution Guidelines
-----------------------------

This guide covers ways in which you can contribute to the development
of our products. After reading this guide, you should be familiar with:

-   Using GitHub to report issues
-   Helping to resolve existing issues
-   Contributing to the code

Creation of our products occurred with significant contributions from
several people with changes ranging from a single character to massive
architectural contributions or significant documentation. All with the
goal of making our products better for everyone. Even if you don’t feel
up to writing code or documentation yet, there are a variety of other ways
that you can contribute, from reporting issues to testing patches. If
you want to participate in adding new features, or fixes, a good place
to start would be to look at the GitHub Issue Tracking to find issues
that may be of interest to you.

# 1 Reporting an Issue

We use GitHub Issue Tracking to track issues (primarily bugs and
contributions of new code). If you’ve found a bug, this is the place
to start. You’ll need to create a (free) GitHub account in order to
either submit an issue, comment on them or create pull requests.

Bugs in the most recent released versions are likely to get the most
attention. Also, the core engineering team is always interested in
feedback from those who can take the time to test recently committed
code that is currently under development.

## 1.1 Creating a Bug Report

If you’ve found a problem in which is not a security risk do a search
in GitHub Issues in case it was already reported. If you find no issue
addressing it you can add a new one.

At the minimum, your issue report needs a title and descriptive text.
But that’s only a minimum. You should include as much relevant
information as possible. You need to at least post the code sample that
has the issue. Even better is to include a unit test that shows how the
expected behavior is not occurring. Your goal should be to make it easy
for yourself – and others – to replicate the bug and figure out a fix.

Creating an issue like this is mostly to help yourself start on the path
of fixing the problem and for others to confirm it with a “I’m having
this problem too” comment.

# 2 Helping to Resolve Existing Issues

As a next step beyond reporting issues, you can help the core team
resolve existing issues. If you check the [Everyone’s Issues][] list in
GitHub Issues, you’ll find lots of issues already requiring attention.
What can you do for these? Quite a bit, actually:

## 2.1 Verifying Bug Reports

For starters, it helps to just verify bug reports. Can you reproduce the
reported issue on your own computer? If so, you can add a comment to the
issue saying that you’re seeing the same thing.

If something is very vague, can you help squish it down into something
specific? Maybe you can provide additional information to help reproduce
a bug, or eliminate needless steps that aren’t required to help
demonstrate the problem.

If you find a bug report without a test, it’s very useful to contribute
a failing test. This is also a great way to get started exploring the
source code: looking at the existing test files will teach you how to
write more tests. New tests are best contributed in the form of a patch,
as explained later on in the “Contributing to the Code” section.

Anything you can do to make bug reports more succinct or easier to
reproduce is a help to folks trying to write code to fix those bugs –
whether you end up writing the code yourself or not.

## 2.2 Testing Patches

You can also help out by examining pull requests that have been
submitted to via GitHub. To apply someone’s changes you need to
first create a dedicated branch:

````bash
$ git checkout -b testing_branch
````

Then you can use their remote branch to update your codebase. For
example, let’s say the GitHub user JohnSmith has forked and pushed to
the topic branch located at https://github.com/JohnSmith/widget.git

````bash
$ git remote add JohnSmith git://github.com/JohnSmith/widget.git
$ git pull JohnSmith topic
````

After applying their branch, test it out! Here are some things to think
about:

-   Does the change actually work?
-   Are you happy with the tests? Can you follow what they’re testing?
    Are there any tests missing?
-   Does it have proper documentation coverage? Should documentation
    elsewhere be updated?
-   Do you like the implementation? Can you think of a nicer or faster
    way to implement a part of their change?

Once you’re happy that the pull request contains a good change, comment
on the GitHub issue indicating your approval. Your comment should
indicate that you like the change and what you like about it. Something
like:

> I like the way you’ve restructured that code in generate\_finder\_sql,
> much nicer. The tests look good too.

If your comment simply says “+1”, then odds are that other reviewers
aren’t going to take it too seriously. Show that you took the time to
review the pull request.

# 3 Contributing to the Code

## 3.1 Sign the Contributor License Agreement
If you have not previously done so, please fill out and submit the CLA
form. You'll receive a token when this process is complete. Keep track
of this, you may be asked for it later! Note that emailing/postal
mailing a signed copy is not necessary. Submission of the web form is all
that is required.

## 3.1 Git Configuration

When contributing to this project, please verify these specific Git
settings are configured for your Git client, appropriately setting your
name and email:

```bash
git config --global user.name "First Last"
git config --global user.email name@server.com
git config --global rerere.enabled true
git config --global branch.autosetuprebase always
git config --global core.autocrlf false
git config --global log.date iso
git config --global merge.log true
git config --global color.diff auto
git config --global color.status auto
git config --global color.branch auto
```

## 3.2 Clone the Repository

The first thing you need to do to be able to contribute code is to clone
the repository:

````
$ git clone git://github.com/nuodb/widget.git
````

and create a dedicated branch:

````
$ cd widget
$ git checkout -b my_new_branch
````

It doesn’t really matter what name you use, because this branch will
only exist on your local computer and your personal repository on
Github. It won’t be part of our master git repository.

## 3.3 Write Your Code

Now get busy and add or edit code. You’re on your branch now, so you can
write whatever you want (you can check to make sure you’re on the right
branch with (`git branch -a`). But if you’re planning to submit your
change back for inclusion in the project, keep a few things in mind:

-   Get the code right
-   Use standard idioms and helpers
-   Include tests that fail without your code, and pass with it
-   Update the documentation, the surrounding one, examples elsewhere,
    guides, whatever is affected by your contribution

## 3.4 Follow the Coding Conventions

We follow a simple set of coding style conventions:

-   Four spaces, no tabs.
-   No trailing whitespace. Blank lines should not have any space.
-   Follow the conventions you see used in the source already.

Otherwise follow these guidelines for the language of use:

- [Google Style Guide](http://code.google.com/p/google-styleguide/)
- [Java Coding Guidelines](http://www.oracle.com/technetwork/java/codeconv-138413.html)

These are some guidelines and please use your best judgment in using
them.

## 3.5 Add BSD License to New Source Files

Add the following BSD license to all new source files:

````
Copyright (c) 2012, NuoDB, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of NuoDB, Inc. nor the names of its contributors may
      be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL NUODB, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
````

### 3.5.1 Update License Header Dates

Always check the date range in the license header updating the range as
necessary. Retaining the original date for the submission always update
the end date to the current calendar year. For example:

````
* Copyright (c) 2010 - 2012, NuoDB, Inc.
````

## 3.6 Sanity Check

You should not be the only person who looks at the code before you
submit it. You know at least one other developer, right? Show them
what you’re doing and ask for feedback. Doing this in private before you
push a patch out publicly is the “smoke test” for a patch: if you can’t
convince one other developer of the beauty of your code, you’re unlikely
to convince the core team either.

## 3.7 Commit Your Changes

When you’re happy with the code on your computer, you need to commit the
changes to git:

````
$ git commit -a -m "Here is a commit message on what I changed in this commit"
````

## 3.8 Update master

It’s pretty likely that other changes to master have happened while you
were working. Go get them:

````
$ git checkout master
$ git pull --rebase
````

Now reapply your patch on top of the latest changes:

````
$ git checkout my_new_branch
$ git rebase master
````

No conflicts? Tests still pass? Change still seems reasonable to you?
Then move on.

## 3.9 Fork

Navigate to the GitHub repository and press “Fork” in the upper right hand
corner [(More details of forking)](http://help.github.com/forking/).

Add the new remote to your local repository on your local machine:

````
$ git remote add mine git@github.com:<your user name>/<project>.git
````

Push to your remote:

````
$ git push mine my_new_branch
````

## 3.10 Issue a Pull Request

Navigate to the repository you just pushed to
(e.g. https://github.com/your-user-name/project) and press “Pull Request”
in the upper right hand corner to issue a [pull request](http://help.github.com/pull-requests/).

Write your branch name in branch field (is filled with master by
default) and press “Update Commit Range”

Ensure the changesets you introduced are included in the “Commits” tab
and that the “Files Changed” incorporate all of your changes.

Fill in some details about your potential patch including a meaningful
title. When finished, press “Send pull request.” Engineering will be
notified about your submission.

## 3.11 Get Some Feedback

Now you need to get other people to look at your patch, just as you’ve
looked at other people’s patches.

## 3.12 Iterate as Necessary

It’s entirely possible that the feedback you get will suggest changes.
Don’t get discouraged: the whole point of contributing to an active open
source project is to tap into community knowledge. If people are
encouraging you to tweak your code, then it’s worth making the tweaks
and resubmitting. If the feedback is that your code doesn’t belong in
the core, you might still think about releasing it on GitHub.

And then … think about your next contribution!
